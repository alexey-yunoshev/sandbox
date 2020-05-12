// author https://www.youtube.com/watch?v=ZYIsrWeG3mc

#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>


void printSockType (int socktype){
    switch(socktype){
        case SOCK_STREAM:   printf("SOCK_STREAM");   break;
        case SOCK_DGRAM:    printf("SOCK_DGRAM");    break;
        case SOCK_RAW:      printf("SOCK_RAW");      break;
        case SOCK_RDM:      printf("SOCK_RDM");      break;
        case SOCK_SEQPACKET:printf("SOCK_SEQPACKET");break;
        case SOCK_DCCP:     printf("SOCK_DCCP");     break;
    }

    // default
    printf(" (%d)\n", socktype);
}

// ---------------------------------------------------------------------------------
// @brief: simply convert defines to strings
void printProtocol (int protocol){
    switch(protocol){
        // numbers are taken from /etc/protocols
        case 0:  printf("IP");  break;
        case 6:  printf("TCP"); break;
        case 17: printf("UDP"); break;
        case 41: printf("IPv6");break;        
    }

    // default
    printf(" (%d)\n", protocol);
}

// ---------------------------------------------------------------------------------

// @brief: simply prints various information on the screen.
void printAddrInfo (struct addrinfo * res,
                    const char * host,
                    const char * service){
    printf("------------------------------------\n");
    printf("| host:        %s\n",  host);
    printf("| service:     %s\n",  service);
    printf("|                \n");
    printf("| cannonname:  %s\n",  res->ai_canonname);    
    printf("| socket type: "    ); printSockType(res->ai_socktype);
    printf("| protocol:    "    ); printProtocol(res->ai_protocol);
    printf("| address len: %d\n",  res->ai_addrlen  );    
    printf("------------------------------------\n");
}

// ---------------------------------------------------------------------------------

// @brief: resolve a given IP address to a hostname
int main() {

    // IP address to resolve
    const char * GOOGLE = "172.217.25.206";
    const char * SERVICE = NULL; 

    // only get us addresses, that match the filter critiera 
    struct addrinfo filter = {0}; 
    filter.ai_socktype = SOCK_DGRAM;    // = UDP
    filter.ai_family = AF_INET;         // = IPv4
        
    struct addrinfo * result;

    getaddrinfo(GOOGLE,SERVICE, &filter, &result) == 1 ? printf("getaddrinfo FAILED\n") :
                                                         printf("getaddrinfo OK\n");       
    
    char host   [HOST_NAME_MAX];
    char service[HOST_NAME_MAX];

    // ------------ get name info ----------------
    // `result` could be a linked list. go through all
    for (struct addrinfo * aip = result;   aip != NULL;    aip = aip->ai_next)
    {
        getnameinfo(aip->ai_addr, aip->ai_addrlen, 
                    host,         sizeof(host), 
                    service,      sizeof(service), 0);
        printAddrInfo(aip, host, service);
    }
    freeaddrinfo(result);

    return 0;
}