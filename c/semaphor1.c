#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 10
int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value)  {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
}

int get() {
    int tmp = buffer[use];
    use = (use + 1) % MAX;
    return tmp;
}

sem_t mutex;
sem_t empty;
sem_t full;
int loops = 10;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(0);
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        get(i);
        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(0);
}

int main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, MAX);
    return 0;
}