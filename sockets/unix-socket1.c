#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const char *SOCKNAME = "/tmp/mysock";
    int sfd;
    struct sockaddr_un addr;

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1 ) {
        printf("socket");
        exit(1);
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKNAME, sizeof(addr.sun_path) - 1);
    
    if (bind(sfd, (struct sockaddr * ) &addr, sizeof(struct sockaddr_un)) == -1) {
        printf("bind");
        exit(1);
    }
}