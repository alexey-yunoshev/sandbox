#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

// not synched

typedef struct __counter_t
{
    int value;
} counter_t;

void init(counter_t *c)
{
    c->value = 0;
}

void increment(counter_t *c)
{
    c->value++;
}

void decrement(counter_t *c)
{
    c->value--;
}

int get(counter_t *c)
{
    return c->value;
}

typedef struct __sync_counter_t
{
    int value;
    pthread_mutex_t lock;
} __sync_counter_t;

void s_init(__sync_counter_t *c)
{
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void s_increment(__sync_counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void s_decrement(__sync_counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}

int s_get(__sync_counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}

long int get_nanosecs(struct timeval *tv)
{
    return (tv->tv_sec * 1000000000) + tv->tv_usec;
}

struct __sync_counter_t c2;

void *incr(void *arg)
{
    for (int i = 0; i < 250000000; i++)
    {
        s_increment(&c2);
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{

    struct timeval tv;

    printf("not sync. single threaded: ");
    struct __counter_t c;
    init(&c);
    gettimeofday(&tv, NULL);
    long int t1 = get_nanosecs(&tv);

    for (int i = 0; i < 1000000000; i++)
    {
        increment(&c);
    }

    gettimeofday(&tv, NULL);
    long int t2 = get_nanosecs(&tv);

    printf("%f ms\n", (double)(t2 - t1) / (double)1000000);

    printf("sync. single threaded: ");
    struct __sync_counter_t c1;
    s_init(&c1);
    gettimeofday(&tv, NULL);
    long int t3 = get_nanosecs(&tv);

    for (int i = 0; i < 1000000000; i++)
    {
        s_increment(&c1);
    }

    gettimeofday(&tv, NULL);
    long int t4 = get_nanosecs(&tv);
    printf("%f ms\n", (double)(t4 - t3) / (double)1000000);

    printf("sync. multi threaded: ");
    pthread_t threads[4];
    // pthread_t th1;
    // pthread_create(&th1, NULL, incr, NULL);
    gettimeofday(&tv, NULL);
    for (int p = 0; p < 4; p++)
    {
        pthread_create(&threads[p], NULL, incr, NULL);
    }
    long int t5 = get_nanosecs(&tv);

    for (int p = 0; p < 4; p++)
    {
        pthread_join(threads[p], NULL);
    }
    gettimeofday(&tv, NULL);
    long int t6 = get_nanosecs(&tv);
    printf("%f ms\n", (double)(t6 - t5) / (double)1000000);

    return 0;
}

// not sync. single threaded: 2999.128225 ms
// sync. single threaded: 15000.816368 ms
// sync. multi threaded: 65999.758279 ms