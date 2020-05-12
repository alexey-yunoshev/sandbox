#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define MAX 10
int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int get() {
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}


pthread_cond_t empty, fill;
pthread_mutex_t mutex;

const int loops = 1000;
void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        while (count == MAX) {
            pthread_cond_wait(&empty, &mutex);
        }
        put(i);
        printf("put %d\n", i);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&fill, &mutex);
        }
        int tmp = get();
        printf("%ld : get %d\n", pthread_self(), tmp);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

int main (int argc, char *argv[]) {
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&fill, NULL);
    pthread_mutex_init(&mutex,  NULL);

    pthread_t p1, p2, p3;
    pthread_create(&p1, NULL, consumer, NULL);
    pthread_create(&p3, NULL, consumer, NULL);
    pthread_create(&p2, NULL, producer, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);

    exit(0);
}