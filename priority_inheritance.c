#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void *handler_1()
{
    sleep(1);
    printf("thread 1 used shared resource \n");
    return NULL;
}

void main()
{
    pthread_mutex_t mutex;
    //pthread_mutexattr_t attr; //TODO:USE 
    pthread_t thread_1; 
    //struct sched_param param; //TODO:USE 
    
    
    //create mutex and initialize it
    pthread_mutex_init(&mutex, NULL);

    //set different priority for threads 1, 2, and 3

    //set handler for threads 1, 2, 3
    printf("before thread \n");
    pthread_mutex_lock(&mutex);
    pthread_create(&thread_1, NULL, handler_1, NULL);
    pthread_join(thread_1, NULL);
    pthread_mutex_unlock(&mutex); //should unlock be before or after join?
    sleep(1);
    printf("after thread\n");

    //should check that all threads are finished before main can exit


}