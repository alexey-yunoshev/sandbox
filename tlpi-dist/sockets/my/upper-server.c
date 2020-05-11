#include "datagram-header.h"

int
main(int argc, char *argv[])
{
    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    int server_fd;
    int j;
    ssize_t numberOfBytesRead;
    socklen_t length;
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    remove(SERVER_SOCKET_PATH);
    memset(&server_addr, 0, SOCKET_ADDRESS_SIZE);
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path));

    bind(server_fd, (struct sockaddr *) &server_addr, SOCKET_ADDRESS_SIZE - 1);

    for (;;) {
        length = SOCKET_ADDRESS_SIZE;
        numberOfBytesRead = recvfrom(
            server_fd,
            buffer,
            BUFFER_SIZE,
            0,
            (struct sockaddr *) &client_addr,
            &length
            );
        printf("Server received %ld bytes from %s\n", (long) numberOfBytesRead, client_addr.sun_path);

        for (j = 0; j < numberOfBytesRead; j++) {
            buffer[j] = toupper((unsigned char) buffer[j]);
        }

        sendto(server_fd, buffer, numberOfBytesRead, 0, (struct sockaddr *) &client_addr, length);
    }
}