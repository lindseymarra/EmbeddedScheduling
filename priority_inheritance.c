#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>


pthread_mutex_t mutex;
pthread_mutexattr_t mutex_attr; //TODO:USE 
pthread_t thread_1, thread_2, thread_3; 
struct sched_param param_1, param_2, param_3; //TODO:USE 
int priority_1, priority_2, priority_3;
int policy = SCHED_RR; //assigns round robin to declared policy variable
int priority;

void *handler_1()
{
    printf("thread 1 waiting for mutex \n");
    pthread_mutex_lock(&mutex); //locks while in use
    printf("thread 1 has mutex \n"); //can the "work" just be printing that the thread has the mutex?
    priority = pthread_getschedparam(thread_1,&policy,&param_1);
    printf("thread 1 has priority %d \n", priority);
    
    sleep(1);
    pthread_mutex_unlock(&mutex); //unlocked when done
    return NULL;
}

void *handler_2()
{
    printf("thread 2 waiting for mutex \n");
    pthread_mutex_lock(&mutex); //locks while in use
    printf("thread 2 has mutex \n");
    int priority = pthread_getschedparam(thread_2,&policy,&param_2);
    printf("thread 2 has priority %d \n", priority);
    pthread_mutex_unlock(&mutex); //unlocked when done
    return NULL;
}

void *handler_3()
{
    printf("thread 3 waiting for mutex \n");
    pthread_mutex_lock(&mutex); //locks while in use
    printf("thread 3 has mutex \n");
    pthread_mutex_unlock(&mutex); //unlocked when done
    return NULL;
}

void main()
{
    
    //create mutex, set protocol, and initialize it
    pthread_mutexattr_setprotocol(&mutex_attr, PTHREAD_PRIO_INHERIT);
    pthread_mutex_init(&mutex, &mutex_attr);

    //set & get different priority for threads 1, 2, and 3
    priority_1 = 3;
    priority_2 = 7;
    priority_3 = 13;

    printf("original priorities: \n priority 1: %d \n priority 2: %d \n priority 3: %d\n", priority_1, priority_2, priority_3);
    param_1.sched_priority = priority_1;
    param_2.sched_priority = priority_2;
    param_3.sched_priority = priority_3;

    //set create threads 1, 2, 3

    pthread_setschedparam(thread_1,policy,&param_1); //I moved this from before pthread_create to after and it didn't make a difference that I can currently see
    pthread_create(&thread_1, NULL, handler_1, NULL);
    
    pthread_setschedparam(thread_2,policy,&param_2);
    pthread_create(&thread_2, NULL, handler_2, NULL);
        

    pthread_setschedparam(thread_3,policy,&param_3);
    pthread_create(&thread_3, NULL, handler_3, NULL);
 
    
    pthread_join(thread_1, NULL);    
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);

    //should check that all threads are finished before main can exit


}