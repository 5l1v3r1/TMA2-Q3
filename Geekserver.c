//***********************************
//Author: Maurice Robert
//Program: TMA2 Q3, Server program for udp connection 
//***********************************

#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

#define PORT 5000 
#define MAXLINE 1000 

/*******************************************************************
  Create two terminal and run the following for server first: 

    1)  gcc -o Geekserver Geekserver.c
    2)  ./Geekserver
     
  Then run the following for client second on another terminal:  
 
    1)  gcc -o Geekclient Geekclient.c
    2)  ./Geekclient
*******************************************************************/
  
int main() 
{    
    char buffer[100]; 
    char *message = "Hi Client! I am your Server, Huhu"; 
    
    // Declare listenfd as integer variables to handle the socket 
    int listenfd, len; 
    
    // Declare servaddr as sockaddr_in structure
    // to store info about Internet domain socket address 
    struct sockaddr_in servaddr, cliaddr; 
    
    // Declare of servaddr as integer
    // to store the address length in internet domain
    bzero(&servaddr, sizeof(servaddr)); 
     
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);     // Create a UDP Socket  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Store the values in the address structure 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET;  
   
    /* Bind server address to socket descriptor 
    To indentify (name) a socket, we must assign a transport address to the socket
    this operation is called binding an address and the bind system call is used
    
    bind (int socket, const struct sockaddr *address, socklen_t address_len);
      1) listenfd, is the socket that was created with the socket system call.
      2) struct sockaddr_in, which is defined in the header netinet/in.h.
      3) socket address length */
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
       
    //receive the datagram 
    len = sizeof(cliaddr); 
    int n = recvfrom(listenfd, buffer, sizeof(buffer), 
            0, (struct sockaddr*)&cliaddr,&len); //receive message from client 
    buffer[n] = '\0'; 
    puts(buffer); 
           
    /*With TCP sockets, we must establish a connection before we could communicate. 
    With UDP, our sockets are connectionless. Hence, we can send messages 
    immediately. Since we do not have a connection, the messages have to be 
    addressed to their destination. Instead of using a write system call, 
    we will use "sendto", which allows us to specify the destination. The address 
    is identified through the sockaddr structure. */

    sendto(listenfd, message, MAXLINE, 0, 
          (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
          
    /* sendto(int socket, const void *buffer, size_t length, int flags, 
    const struct sockaddr *dest_addr, socklen_t dest_len)      
        1) listenfd - socket that was created with the socket system call and named via bind.
        2) The "message" to send 
        3) length is the number of bytes that we want to send, here is 1000 bytes (#define MAXLINE 1000)
        4) flags parameter is 0 
        5) dest_addr defines the destination address and port number for the message.
        6) As with bind, the final parameter is length of the address 
        structure: sizeof(struct sockaddr_in).*/
} 
