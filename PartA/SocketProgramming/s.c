#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char * argv[])  {
    int bufsiz=2048;
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[1]));
    address.sin_addr.s_addr = INADDR_ANY;
    char buffer[bufsiz];
    int s = socket(AF_INET,SOCK_STREAM,0);
    bind(s,(struct sockaddr*)&address,sizeof(address));
    listen(s,3);
    int ns = accept(s,(struct sockaddr*)NULL, NULL);
    char filename[256];
    recv(ns,filename,255,0);
    int file = open(filename, O_RDONLY);
    int n = read(file,buffer,bufsiz);
    send(ns,buffer,n,0);
    close(ns);
    close(s);
    return 0;

}
