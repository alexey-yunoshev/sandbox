/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 59-6 */

/* is_seqnum_sv.c

   A simple Internet stream socket server. Our service is to provide
   unique sequence numbers to clients.

   Usage:  is_seqnum_sv [init-seq-num]
                        (default = 0)

   See also is_seqnum_cl.c.
*/
#define _DEFAULT_SOURCE             /* To get definitions of NI_MAXHOST and
                                   NI_MAXSERV from <netdb.h> */
#include <netdb.h>
#include "is_seqnum.h"


#define BACKLOG 50

ssize_t
readLine(int fd, void *buffer, size_t n)
{
    ssize_t numRead;                    /* # of bytes fetched by last read() */
    size_t totRead;                     /* Total bytes read so far */
    char *buf;
    char ch;

    if (n <= 0 || buffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    buf = buffer;                       /* No pointer arithmetic on "void *" */

    totRead = 0;
    for (;;) {
        numRead = read(fd, &ch, 1);

        if (numRead == -1) {
            if (errno == EINTR)         /* Interrupted --> restart read() */
                continue;
            else
                return -1;              /* Some other error */

        } else if (numRead == 0) {      /* EOF */
            if (totRead == 0)           /* No bytes read; return 0 */
                return 0;
            else                        /* Some bytes read; add '\0' */
                break;

        } else {                        /* 'numRead' must be 1 if we get here */
            if (totRead < n - 1) {      /* Discard > (n - 1) bytes */
                totRead++;
                *buf++ = ch;
            }

            if (ch == '\n')
                break;
        }
    }

    *buf = '\0';
    return totRead;
}


// int
// main(int argc, char *argv[])
// {
//     uint32_t seqNum;
//     char reqLenStr[INT_LEN];            /* Length of requested sequence */
//     char seqNumStr[INT_LEN];            /* Start of granted sequence */
//     struct sockaddr_storage claddr;
//     int lfd, cfd, optval, reqLen;
//     socklen_t addrlen;
//     struct addrinfo hints;
//     struct addrinfo *result, *rp;
// #define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)
//     char addrStr[ADDRSTRLEN];
//     char host[NI_MAXHOST];
//     char service[NI_MAXSERV];

//     if (argc > 1 && strcmp(argv[1], "--help") == 0)
//         usageErr("%s [init-seq-num]\n", argv[0]);

//     seqNum = (argc > 1) ? getInt(argv[1], 0, "init-seq-num") : 0;

//     /* Ignore the SIGPIPE signal, so that we find out about broken connection
//        errors via a failure from write(). */

//     if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)    errExit("signal");

//     /* Call getaddrinfo() to obtain a list of addresses that
//        we can try binding to */

//     memset(&hints, 0, sizeof(struct addrinfo));
//     hints.ai_canonname = NULL;
//     hints.ai_addr = NULL;
//     hints.ai_next = NULL;
//     hints.ai_socktype = SOCK_STREAM;
//     hints.ai_family = AF_UNSPEC;        /* Allows IPv4 or IPv6 */
//     hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
//                         /* Wildcard IP address; service name is numeric */

//     if (getaddrinfo(NULL, PORT_NUM, &hints, &result) != 0)
//         errExit("getaddrinfo");

//     /* Walk through returned list until we find an address structure
//        that can be used to successfully create and bind a socket */

//     optval = 1;
//     for (rp = result; rp != NULL; rp = rp->ai_next) {
//         lfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
//         if (lfd == -1)
//             continue;                   /* On error, try next address */

//         if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))
//                 == -1)
//              errExit("setsockopt");

//         if (bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
//             break;                      /* Success */

//         /* bind() failed: close this socket and try next address */

//         close(lfd);
//     }

//     if (rp == NULL)
//         fatal("Could not bind socket to any address");

//     if (listen(lfd, BACKLOG) == -1)
//         errExit("listen");

//     freeaddrinfo(result);

//     for (;;) {                  /* Handle clients iteratively */

//         /* Accept a client connection, obtaining client's address */

//         addrlen = sizeof(struct sockaddr_storage);
//         cfd = accept(lfd, (struct sockaddr *) &claddr, &addrlen);
//         if (cfd == -1) {
//             errMsg("accept");
//             continue;
//         }

//         if (getnameinfo((struct sockaddr *) &claddr, addrlen,
//                     host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
//             snprintf(addrStr, ADDRSTRLEN, "(%s, %s)", host, service);
//         else
//             snprintf(addrStr, ADDRSTRLEN, "(?UNKNOWN?)");
//         printf("Connection from %s\n", addrStr);

//         /* Read client request, send sequence number back */

//         if (readLine(cfd, reqLenStr, INT_LEN) <= 0) {
//             close(cfd);
//             continue;                   /* Failed read; skip request */
//         }

//         reqLen = atoi(reqLenStr);
//         if (reqLen <= 0) {              /* Watch for misbehaving clients */
//             close(cfd);
//             continue;                   /* Bad request; skip it */
//         }

//         snprintf(seqNumStr, INT_LEN, "%d\n", seqNum);
//         if (write(cfd, seqNumStr, strlen(seqNumStr)) != strlen(seqNumStr))
//             fprintf(stderr, "Error on write");

//         seqNum += reqLen;               /* Update sequence number */

//         if (close(cfd) == -1)           /* Close connection */
//             errMsg("close");
//     }
// }


int
main(int argc, char *argv[]) {
    #define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)
    
    signal(SIGPIPE, SIG_IGN);

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

    struct addrinfo *first_addr;
    getaddrinfo(NULL, PORT_NUM, &hints, &first_addr);

    int server_fd;
    struct addrinfo * addr = first_addr;
    int true_optval = true;
    while (addr != NULL) {
        server_fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (server_fd == -1) {
            addr = addr->ai_next;
            continue;
        }

        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &true_optval, sizeof(true_optval));

        if (bind(server_fd, addr->ai_addr, addr->ai_addrlen) == 0) {
            break;
        };

        close(server_fd);
    }

    if (addr == NULL) {
        printf("Coud not bind socket to any address");
        exit(EXIT_FAILURE);
    }

    listen(server_fd, BACKLOG);

    freeaddrinfo(first_addr);

    socklen_t addrlen;
    char addrStr[ADDRSTRLEN];
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    int incrementBy;
    uint32_t seqNum = 0;
    char message[INT_LEN];
    char seqNumStr[INT_LEN];
    int client_fd;
    struct sockaddr_storage client_addr;

    while (true) {
        addrlen = sizeof(struct sockaddr_storage);
        client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &addrlen);

        getnameinfo(
            (struct sockaddr *) &client_addr, addrlen,
            host, NI_MAXHOST,
            service, NI_MAXSERV,
            0
            );
        
        snprintf(addrStr, ADDRSTRLEN, "(%s, %s)", host, service);
        printf("Connection from %s\n", addrStr);

        readLine(client_fd, message, INT_LEN);
        incrementBy = atoi(message);

        snprintf(seqNumStr, INT_LEN, "%d\n", seqNum);
        write(client_fd, seqNumStr, strlen(seqNumStr));

        seqNum += incrementBy;
        close(client_fd);
    }
}  