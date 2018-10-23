//***********************************
//Author: Maurice Robert
//Program: TMA2 Q3, Client program for udp connection 
//***********************************
#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h> 
#include <stdlib.h> 

#define PORT 5000 
#define MAXLINE 1000 
  
int main() 
{    
    char buffer[100]; 
    char *message = "Hey there Mr.Server, I am the client!, Hehe"; 
    int sockfd, n; 
    struct sockaddr_in servaddr; 
      
    // clear servaddr 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET; 
      
    /* A socket, sockfd, is created with the socket system call
    int sockfd = socket(domain, type, protocol)
      1) domain, or address family — communication domain in which the socket should be created
         AF_INET (IP), AF_INET6 (IPv6), AF_UNIX (local channel, similar to pipes), 
         AF_ISO (ISO protocols), and AF_NS (Xerox Network Systems protocols)
      2) type of service - SOCK_STREAM (virtual circuit service), SOCK_DGRAM (datagram service), SOCK_RAW (direct IP service). 
      3) protocol to use in supporting the sockets operation. For UDP is 0 (zero)
    For UDP/IP sockets, the IP address family is (AF_INET) and 
    datagram service is (SOCK_DGRAM). */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
      
    // Connect to server 
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        printf("\n Error : Connect Failed \n"); 
        exit(0); 
    } 
  
    // Request to send datagram 
    sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
      
    /* To receive message from server
    int recvfrom(int socket, void *restrict buffer, size_t length, 
    int flags, struct sockaddr *restrict src_addr, socklen_t *restrict *src_len)
        1) socket that we created ahead of time, sockfd */
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
    puts(buffer); 
  
    // Close the socket
    close(sockfd); 
} 
