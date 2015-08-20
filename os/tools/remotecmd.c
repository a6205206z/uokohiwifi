#include "remotecmd.h"
#include "uoko_tcpclient.h"


static uint         select_option;
static uint         exc_pull_command;
static char         *usignal;
static const char   *uoko_command_server = "127.0.0.1";
static const int    uoko_command_server_port = 80;
static char   *uoko_command_server_location = "/index";
static char   *uoko_command_server_parms = "i=1";

static int get_options(int argc, char *const *argv);
static int pull_command();



int http_post(uoko_tcpclient *pclient,char *page,char *request,char **response){

    char post[300],host[100],content_len[100];
    char *lpbuf,*ptmp;
    int len=0;

    lpbuf = NULL;
    const char *header2="User-Agent: UokoHiwifi Http 0.1\r\nCache-Control: no-cache\r\nContent-Type: application/x-www-form-urlencoded\r\nAccept: */*\r\n";

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
printf("接收响应:\n%s\n",lpbuf);

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

static int pull_command(){

    uoko_tcpclient client;

    char *response = NULL;
    printf("开始组包\n");
    uoko_tcpclient_create(&client,uoko_command_server,uoko_command_server_port);

    if(http_post(&client, uoko_command_server_location,uoko_command_server_parms,&response)){
        printf("失败!\n");
        exit(2);
    }
    printf("响应:\n%d:%s\n",strlen(response),response);

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