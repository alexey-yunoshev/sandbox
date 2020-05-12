#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 10
#define SOCKET_ADDRESS_SIZE sizeof(struct sockaddr_un)

#define SERVER_SOCKET_PATH "/tmp/datagram_socket_uppercase"