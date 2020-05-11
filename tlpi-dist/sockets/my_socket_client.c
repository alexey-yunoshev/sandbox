#include "us_xfr.h"

int
main(int argc, char *argv[]) {
    struct sockaddr_un addr;
    int server_fd;
    ssize_t numBytesRead;
    char buf[BUF_SIZE];

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&addr, 0, SOCKET_ADDR_SIZE);
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, UNIX_SOCKET_PATH_SIZE);

    connect(server_fd, (struct sockaddr *) &addr, SOCKET_ADDR_SIZE - 1);
    while ((numBytesRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
        write(server_fd, buf, numBytesRead);
    }
    exit(EXIT_SUCCESS);
}
