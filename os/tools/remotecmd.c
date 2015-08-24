#include "remotecmd.h"
#include "uoko_tcpclient.h"
#include <sys/ioctl.h>
#include <net/if.h>   


static uint         select_option;
static uint         exc_pull_command;
static char         *usignal;
static const char   *uoko_command_server = "192.168.200.22";
static const int    uoko_command_server_port = 8988;
static char         *uoko_command_server_location = "/login";
static char         push_server_data[REQUEST_BUFFER_COUNT];

static int get_options(int argc, char *const *argv);
static int pull_command();
static int get_mac(char *mac, int len_limit);



int http_post(uoko_tcpclient *pclient,char *page,char *request,char **response){

    char post[300],host[100],content_len[100];
    char *lpbuf,*ptmp;
    int len=0;

    lpbuf = NULL;
    const char *header2="User-Agent: UokoHiwifi \r\nCache-Control: no-cache\r\nContent-Type: application/x-www-form-urlencoded\r\nAccept: */*\r\n";

    sprintf(post,"POST %s HTTP/1.0\r\n",page);
    sprintf(host,"HOST: %s:%d\r\n",pclient->remote_ip,pclient->remote_port);
    sprintf(content_len,"Content-Length: %d\r\n\r\n",strlen(request));

    len = strlen(post)+strlen(host)+strlen(header2)+strlen(content_len)+strlen(request)+1;
    lpbuf = (char*)malloc(len);
    if(lpbuf==NULL){
        return -1;
    }

    strcpy(lpbuf,post);
    strcat(lpbuf,host);
    strcat(lpbuf,header2);
    strcat(lpbuf,content_len);
    strcat(lpbuf,request);

    if(!pclient->connected){
        uoko_tcpclient_conn(pclient);
    }

    if(uoko_tcpclient_send(pclient,lpbuf,len)<0){
        return -1;
    }

    printf("发送请求:\n%s\n",lpbuf);

    /*释放内存*/
    if(lpbuf != NULL) free(lpbuf);
    lpbuf = NULL;

    /*it's time to recv from server*/
    if(uoko_tcpclient_recv(pclient,&lpbuf,0) <= 0){
        if(lpbuf) free(lpbuf);
        return -2;
    }
    //printf("接收响应:\n%s\n",lpbuf);

    /*响应代码,|HTTP/1.0 200 OK|
     *从第10个字符开始,第3位
     * */
    memset(post,0,sizeof(post));
    strncpy(post,lpbuf+9,3);
    if(atoi(post)!=200){
        if(lpbuf) free(lpbuf);
        return atoi(post);
    }


    ptmp = (char*)strstr(lpbuf,"\r\n\r\n");
    if(ptmp == NULL){
        free(lpbuf);
        return -3;
    }
    ptmp += 4;/*跳过\r\n*/

    len = strlen(ptmp)+1;
    *response=(char*)malloc(len);
    if(*response == NULL){
        if(lpbuf) free(lpbuf);
        return -1;
    }
    memset(*response,0,len);
    memcpy(*response,ptmp,len-1);

    /*从头域找到内容长度,如果没有找到则不处理*/
    ptmp = (char*)strstr(lpbuf,"Content-Length:");
    if(ptmp != NULL){
        char *ptmp2;
        ptmp += 15;
        ptmp2 = (char*)strstr(ptmp,"\r\n");
        if(ptmp2 != NULL){
            memset(post,0,sizeof(post));
            strncpy(post,ptmp,ptmp2-ptmp);
            if(atoi(post)<len)
                (*response)[atoi(post)] = '\0';
        }
    }

    if(lpbuf) free(lpbuf);

    return 0;
}

static int 
get_mac(char *mac, int len_limit){
    struct  ifreq ifreq;
    int     sock;
    int     res;

    if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0){
        perror ("socket");
        return -1;
    }
    strcpy (ifreq.ifr_name, "eth0");

    if (ioctl (sock, SIOCGIFHWADDR, &ifreq) < 0){
        res = -1;
    }


    if(res == -1){
        res = 0;
        strcpy (ifreq.ifr_name, "eth1");

        if (ioctl (sock, SIOCGIFHWADDR, &ifreq) < 0){
            res = -1;
        }
    }

    if(res == -1){
        res = 0;
        strcpy (ifreq.ifr_name, "eth2");

        if (ioctl (sock, SIOCGIFHWADDR, &ifreq) < 0){
            perror ("ioctl");
            return -1;
        }
    }


    
    return snprintf (mac, len_limit, "%X:%X:%X:%X:%X:%X", 
        (unsigned char) ifreq.ifr_hwaddr.sa_data[0], 
        (unsigned char) ifreq.ifr_hwaddr.sa_data[1], 
        (unsigned char) ifreq.ifr_hwaddr.sa_data[2], 
        (unsigned char) ifreq.ifr_hwaddr.sa_data[3], 
        (unsigned char) ifreq.ifr_hwaddr.sa_data[4], 
        (unsigned char) ifreq.ifr_hwaddr.sa_data[5]);
}

static int 
pull_command(){

    uoko_tcpclient  client;
    char            mac[18];

    char            *response = NULL;
    uoko_tcpclient_create(&client,uoko_command_server,uoko_command_server_port);

    if(get_mac(mac,sizeof(mac)) < 0){
        return ERROR;
    }

    memset(push_server_data,0,sizeof(push_server_data));
    sprintf(push_server_data,"mac=%s",mac);

    if(http_post(&client, uoko_command_server_location,push_server_data,&response)){
        printf("ERROR\n");
        return ERROR;
    }

    printf("%s\n",response);

    free(response);
    return OK;
}



static int
get_options(int argc, char *const *argv){
    u_char     *p;
    uint   		i;

    for (i = 1; i < argc; i++) {

        p = (u_char *) argv[i];

        if (*p++ != '-') {
            printf("invalid option: \"%s\"\n", argv[i]);
            return ERROR;
        }

        while (*p) {

            switch (*p++) {
            case 's':
                if (*p) {
                    usignal = (char *) p;
                }
                else if (argv[++i]) {
                    usignal = argv[i];
                } 
                else {
                    printf(0, "option \"-s\" requires parameter\n");
                    return ERROR;
                }


                if (uoko_strcmp(usignal, "--pull-command") == 0){
                    exc_pull_command = 1;
                    goto next;
                }

                printf(0, "invalid option: \"-s %s\"", usignal);
                return ERROR;
                break;

            default:
                printf(0, "invalid option: \"%c\"\n", *(p - 1));
                return ERROR;
            }
        }

    next:

        continue;
    }

    return OK;
}

int main(int argc, char *const *argv)
{
    if(get_options(argc, argv) != OK){
       return 1;        
    }

    if(exc_pull_command){
        return pull_command();
    }
}