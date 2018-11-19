#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>


pthread_mutex_t mutex;
pthread_mutexattr_t mutex_attr;  
pthread_t thread_1, thread_2, thread_3; 
int policy = SCHED_RR; //assigns round robin to declared policy variable
int priority;



void *handler_1()
{
    printf("thread 1 waiting for mutex \n");
    pthread_mutex_lock(&mutex); //locks while in use
    printf("thread 1 has mutex \n"); //can the "work" just be printing that the thread has the mutex?
    //print priorities in thread 1
    sleep(2);
    //int priority = pthread_getschedparam(thread_1,&policy,&param_1);
    //printf("thread 1 has priority %d \n", priority);
    //int priority2 = pthread_getschedparam(thread_2,&policy,&param_2);
    //printf("in thread 1 thread 2 has priority %d \n", priority2);
    //int priority3 = pthread_getschedparam(thread_3,&policy,&param_3);
    //printf("in thread 1 thread 3 has priority %d \n", priority3);    
    pthread_mutex_unlock(&mutex); //unlocked when done
    printf("thread 1 done\n");
    return NULL;
}

void *handler_2()
{
    printf("thread 2 started \n");
    //int priority = pthread_getschedparam(thread_2,&policy,&param_2);
    //printf("thread 2 has priority %d \n", priority);
    //pthread_mutex_lock(&mutex); //locks while in use
    sleep(0.5);
    //printf("thread 2 has mutex \n");
    //pthread_mutex_unlock(&mutex); //unlocked when done
    printf("thread 2 done\n");
    return NULL;
}

void *handler_3()
{
    printf("thread 3 waiting for mutex \n");
    //int priority = pthread_getschedparam(thread_3,&policy,&param_3);
    //printf("thread 3 has priority %d \n", priority);
    pthread_mutex_lock(&mutex); //locks while in use
    printf("thread 3 has mutex \n");
    pthread_mutex_unlock(&mutex); //unlocked when done
    printf("thread 3 done\n");
    return NULL;
}

void main()
{

    // create mutex, set protocol, and initialize it
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_setprotocol(&mutex_attr, PTHREAD_PRIO_INHERIT);
    pthread_mutex_init(&mutex, &mutex_attr);

    
    // set & get different priority for threads 1, 2, and 3
    int priority_1 = sched_get_priority_min(policy);
    int priority_2 = priority_1+1;
    int priority_3 = priority_1+2;

    
    struct sched_param param_1 = {
        .sched_priority=priority_1
    };
        
    struct sched_param param_2 = {
        .sched_priority=priority_2
    };
        
    struct sched_param param_3 = {
        .sched_priority=priority_3
    };
    
    
    printf("original priorities:\npriority 1: %d\npriority 2: %d\npriority 3: %d\n", priority_1, priority_2, priority_3);

    

    // create threads 1, 2, 3

    pthread_setschedparam(thread_1,policy,&param_1);
    pthread_create(&thread_1, NULL, handler_1, NULL);

    
    pthread_setschedparam(thread_2,policy,&param_2);
    pthread_create(&thread_2, NULL, handler_2, NULL);
        

    pthread_setschedparam(thread_3,policy,&param_3);
    pthread_create(&thread_3, NULL, handler_3, NULL);
 
    // check that all threads are finished before main can exit
    pthread_join(thread_1, NULL);    
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);



}