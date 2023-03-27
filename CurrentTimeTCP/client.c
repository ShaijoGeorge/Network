#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
int main()
{
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    
    //Create the cient socket
    clientSocket = socket(PF_INET,SOCK_STREAM,0);
    
    //Configure the server address and port 
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
    
    //Connect to the server
    addr_size = sizeof serverAddr;
    connect(clientSocket,(struct sockaddr*)&serverAddr,addr_size);
    
    //Receive the current time from the sever 
    recv(clientSocket,buffer,1024,0);
    
    //print the received time
    printf("Data Recived! \n Current Time: %s",buffer);
    return 0;
}