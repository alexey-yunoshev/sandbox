#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>

#define SERVERPORT 8989
#define BUFSIZE 4096
#define SOCKET_ERROR (-1)
#define SERVER_BACKLOG 100
#define THREAD_POOL_SIZE 20

pthread_t thread_pool[THREAD_POOL_SIZE];

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

typedef struct node {
    struct node* next;
    int *client_socket;
} node_t;


node_t* head = NULL;
node_t* tail = NULL;

void enqueue(int *client_socket) {
    node_t *newnode = malloc(sizeof(node_t));
    newnode->client_socket = client_socket;
    newnode->next = NULL;

    if (tail == NULL) {
        head = newnode;
    } else {
        tail->next = newnode;
    }
    tail = newnode;
}


int* dequeue() {
    if (head == NULL) {
        return NULL;
    } else {
        int* result = head->client_socket;
        node_t* temp = head;
        head = head->next;
        if (head == NULL) {
            tail = NULL;
        }
        free(temp);
        return result;
    }
}

void check(int exp, const char *msg) {
    if (exp == SOCKET_ERROR) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

void* thread_function(void* arg) {
    while (true) {
        int *pclient = dequeue();
        if (pclient != NULL) {
            handle_connection(pclient);
        }
    }
}

void* handle_connection(void* p_client_socket) {
    printf("Handling connected\n");
    printf("fd addr %p\n", p_client_socket);
    int client_socket = *((int*)p_client_socket);

    printf("fd %d\n", client_socket);


    free(p_client_socket);
    char buffer[BUFSIZE];
    size_t bytes_read;
    int msgsize = 0;
    char resolved_path[PATH_MAX + 1];

    // while((bytes_read = read(client_socket, buffer+msgsize, sizeof(buffer)-msgsize-1)) > 0) {
    //     printf("bytes_read : %ld\n", bytes_read);

    //     printf("message : %s\n", buffer);
    //     msgsize += bytes_read;
    //     printf("msgsize : %d\n", msgsize);
    //     printf("buffer[msgsize-1] : %d\n", buffer[msgsize-1] == '\n');
    //     if (msgsize > BUFSIZE - 1 || buffer[msgsize-1] == '\n') {
    //         printf("in here");
    //         break;
    //     }
    //     printf("in here 2");
    // }
    bytes_read = read(client_socket, buffer+msgsize, sizeof(buffer)-msgsize-1);
    printf("------\n");
    printf("message : %s\n", buffer);
    check(bytes_read, "recv error");
    fflush(stdout);

    if (realpath(buffer, resolved_path) == NULL) {
        printf("ERROR(bad path): %s\n", buffer);
        close(client_socket);
        return NULL;
    }

    FILE *fp = fopen(resolved_path, "r");
    if (fp == NULL) {
        printf("ERROR(open): %s\n", buffer);
        close(client_socket);
        return NULL;
    }

    while((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0) {
        printf("sending %zu bytes\n", bytes_read);
        write(client_socket, buffer, bytes_read);
    }
    close(client_socket);
    fclose(fp);
    printf("closing connection\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    int server_socket;
    int client_socket;
    int addr_size;
    SA_IN server_addr;
    SA_IN client_addr;

    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, thread_function, NULL);
    }

    check(
        (server_socket = socket(AF_INET, SOCK_STREAM, 0)),
        "failed to create socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVERPORT);

    int reuse = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    check(bind(server_socket, (SA*)&server_addr, sizeof(server_addr)),
         "bind failed");
    check(listen(server_socket, SERVER_BACKLOG),
         "Listen failed");

    while (true) {
        printf("waiting for connections...\n");
        addr_size = sizeof(SA_IN);
        check(client_socket = accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size),
             "accept failed");
        printf("Connected: fd %d!\n", client_socket);
        // pthread_t t;
        int *pclient = malloc(sizeof(int));
        *pclient = client_socket;
        enqueue(pclient);
        // pthread_create(&t, NULL, handle_connection, pclient);
        

    }

    exit(EXIT_SUCCESS);
}
