#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <stdlib.h>

#define SERVER_PORT 80

#define MAXLINE 4096
#define SA struct sockaddr


void err_n_die(const char *fmt, ...) {
    int errno_save;
    va_list ap;

    errno_save = errno;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);

    if (errno_save != 0) {
        fprintf(stdout, "(errno = %d) : %s\n\n", errno_save, strerror(errno_save));
        fflush(stdout);
    }
    va_end(ap);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    int sockfd, n;
    int message_length;
    struct sockaddr_in servaddr;
    char message[MAXLINE];
    char response[MAXLINE];

    if (argc != 2) {
        err_n_die("usage: %s <server addr>", argv[0]);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_n_die("Error creating socket");
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_port = htons(8989);

    // if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
    //     err_n_die("inet_pton error for %s", argv[1]);
    // }

    if (inet_pton(AF_INET,"127.0.0.1", &servaddr.sin_addr) <= 0) {
        err_n_die("inet_pton error for %s", argv[1]);
    }

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
        err_n_die("connect failed");
    }

    // sprintf(message, "GET / HTTP/1.1\r\n\r\n");
    sprintf(message, "%s", argv[1]);
    message_length = strlen(message);

    if (write(sockfd, message, message_length) != message_length) {
        err_n_die("write error");
    }

    memset(response, 0, MAXLINE);

    while ((n = read(sockfd, response, MAXLINE-1)) > 0) {
        printf("%s", response);
        memset(response, 0, MAXLINE);
    }

    if (n < 0) {
        err_n_die("read error");
    }

    exit(EXIT_SUCCESS);
}
