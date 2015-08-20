#ifndef _UOKO_TCP_CLIENT_ 
#define _UOKO_TCP_CLIENT_

#include <netinet/in.h>  
#include <sys/socket.h>

typedef struct _uoko_tcpclient{ 
    int socket;
    int remote_port;     
    char remote_ip[16];  
    struct sockaddr_in _addr; 
    int connected;       
} uoko_tcpclient;

int uoko_tcpclient_create(uoko_tcpclient *,const char *host, int port);
int uoko_tcpclient_conn(uoko_tcpclient *);
int uoko_tcpclient_recv(uoko_tcpclient *,char **lpbuff,int size);
int uoko_tcpclient_send(uoko_tcpclient *,char *buff,int size);
int uoko_tcpclient_close(uoko_tcpclient *);

#endif