#include "us_xfr.h"
#define BACKLOG 5

int
main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int server_fd;
    int client_fd;
    ssize_t numBytesRead;
    char buf[BUF_SIZE];
   
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    remove(SV_SOCK_PATH);
    
    memset(&addr, 0, SOCKET_ADDR_SIZE);
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, UNIX_SOCKET_PATH_SIZE);

    bind(server_fd, (struct sockaddr *) &addr, SOCKET_ADDR_SIZE);
    listen(server_fd, BACKLOG);

    for (;;) {
        client_fd = accept(server_fd, NULL, NULL);
        while ((numBytesRead = read(client_fd, buf, BUF_SIZE)) > 0) {
            write(STDOUT_FILENO, buf, numBytesRead);
        }
        close(client_fd);
    }
}
