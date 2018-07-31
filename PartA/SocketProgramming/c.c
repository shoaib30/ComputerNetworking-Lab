#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char * argv[])  {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET,argv[1],&address.sin_addr);
    int s = socket(AF_INET,SOCK_STREAM,0);
    connect(s,(struct sockaddr*)&address,sizeof(address));
    printf("Enter Filename: ");
    char filename[256];
    scanf("%s",filename);
    send(s,filename,255,0);
    int bufsiz=2048;
    char buffer[bufsiz];
    while(recv(s,buffer,bufsiz,0)>0)  {
        printf("%s",buffer);
    }
    close(s);
    return 0;
}
