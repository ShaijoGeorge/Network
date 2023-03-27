#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <arpa/inet.h>
int main()
{
    int welcomeSocket,newSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    time_t tick;
    
    //create the server socket
    welcomeSocket = socket(PF_INET,SOCK_STREAM,0);
    
    //configure the server address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr =inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
    
    //bind the server socket to the specified address and port
    bind(welcomeSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if(listen(welcomeSocket,5)==0)
        printf("Listening...\n");
    else
    printf("Error!\n");
    
    //accept a new client connection
    addr_size = sizeof serverStorage;
    newSocket = accept(welcomeSocket,(struct sockaddr*)&serverStorage, &addr_size);
    
    //get the current system time and send it to the client
    tick= time(NULL);
    snprintf(buffer, sizeof(buffer),"%s",ctime(&tick));
    send(newSocket,buffer,34,0);
    return 0;
}
