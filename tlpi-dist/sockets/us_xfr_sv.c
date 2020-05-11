/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 57-3 */

/* us_xfr_sv.c

   An example UNIX stream socket server. Accepts incoming connections
   and copies data sent from clients to stdout.

   See also us_xfr_cl.c.
*/
#include "us_xfr.h"
#define BACKLOG 5

// int
// main(int argc, char *argv[])
// {
//     struct sockaddr_un addr;
//     int server_fd, client_fd;
//     ssize_t numRead;
//     char buf[BUF_SIZE];

//     server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
//     if (server_fd == -1)
//         errExit("socket");

//     /* Construct server socket address, bind socket to it,
//        and make this a listening socket */

//     /* For an explanation of the following check, see the errata notes for
//        pages 1168 and 1172 at http://www.man7.org/tlpi/errata/. */

//     if (strlen(SV_SOCK_PATH) > sizeof(addr.sun_path) - 1)
//         fatal("Server socket path too long: %s", SV_SOCK_PATH);

//     if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
//         errExit("remove-%s", SV_SOCK_PATH);

//     memset(&addr, 0, sizeof(struct sockaddr_un));
//     addr.sun_family = AF_UNIX;
//     strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

//     if (bind(server_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
//         errExit("bind");

//     if (listen(server_fd, BACKLOG) == -1)
//         errExit("listen");

//     for (;;) {          /* Handle client connections iteratively */

//         /* Accept a connection. The connection is returned on a new
//            socket, 'client_fd'; the listening socket ('sfd') remains open
//            and can be used to accept further connections. */

//         client_fd = accept(server_fd, NULL, NULL);
//         if (client_fd == -1)
//             errExit("accept");

//         /* Transfer data from connected socket to stdout until EOF */

//         while ((numRead = read(client_fd, buf, BUF_SIZE)) > 0)
//             if (write(STDOUT_FILENO, buf, numRead) != numRead)
//                 fatal("partial/failed write");

//         if (numRead == -1)
//             errExit("read");

//         if (close(client_fd) == -1)
//             errMsg("close");
//     }
// }

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
