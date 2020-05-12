#include "datagram-header.h"

int main(int argc, char const *argv[])
{
    struct sockaddr_un server_addr, client_addr;
    int socket_fd;
    int j;
    size_t msg_lenght;
    ssize_t numberOfBytes;
    char response[BUFFER_SIZE];

    socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    memset(&client_addr, 0, SOCKET_ADDRESS_SIZE);
    client_addr.sun_family = AF_UNIX;
    snprintf(
        client_addr.sun_path,
        sizeof(client_addr.sun_path),
        "/tmp/ud_ucase_cl.%ld",
        (long) getpid()
        );
    bind(socket_fd, (struct sockaddr *) &client_addr, sizeof(struct sockaddr_un));

    memset(&server_addr, 0, SOCKET_ADDRESS_SIZE);
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    for (j = 1; j < argc; j++) {
     msg_lenght = strlen(argv[j]);
     sendto(socket_fd, argv[j], msg_lenght, 0, (struct sockaddr *) &server_addr, SOCKET_ADDRESS_SIZE);
     numberOfBytes = recvfrom(socket_fd, response, BUFFER_SIZE, 0, NULL, NULL);
     printf("Response %d: %.*s\n", j, (int) numberOfBytes, response);
    }


    remove(client_addr.sun_path);
    return 0;
}
