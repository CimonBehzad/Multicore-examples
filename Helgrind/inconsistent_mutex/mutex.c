#include <stdio.h>
#include <pthread.h>
#include <unistd.h>   // for usleep

pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;

void* thread1_func(void* arg) {
    pthread_mutex_lock(&mutexA);
    usleep(100);
    pthread_mutex_lock(&mutexB);
    printf("Thread 1 acquired both mutexes\n");
    pthread_mutex_unlock(&mutexB);
    pthread_mutex_unlock(&mutexA);
    return NULL;
}

void* thread2_func(void* arg) {
    pthread_mutex_lock(&mutexB);
    usleep(100);
    pthread_mutex_lock(&mutexA);
    printf("Thread 2 acquired both mutexes\n");
    pthread_mutex_unlock(&mutexA);
    pthread_mutex_unlock(&mutexB);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
