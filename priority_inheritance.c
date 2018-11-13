#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>


pthread_mutex_t mutex;
pthread_mutexattr_t mutex_attr; //TODO:USE 
pthread_t thread_1; 
struct sched_param param; //TODO:USE 
int priority = 10; // why am I defining this as 10 initially before setting it equal to sched_get_priority_max(policy)?
int policy = SCHED_RR; //assigns round robin to declared policy variable

void *handler_1()
{
    pthread_mutex_lock(&mutex); //locks while in use
    sleep(1);
    printf("thread 1 used shared resource \n");
    pthread_mutex_unlock(&mutex); //unlocked when done
    return NULL;
}

void main()
{
    
    //create mutex, set protocol, and initialize it
    pthread_mutexattr_setprotocol(&mutex_attr, PTHREAD_PRIO_INHERIT);
    pthread_mutex_init(&mutex, &mutex_attr);

    //set & get different priority for threads 1, 2, and 3
    printf("%d \n",priority);
    priority=sched_get_priority_max(policy);
    printf("%d \n",priority);
    param.sched_priority = priority;



    //set create threads 1, 2, 3
    printf("before thread \n");

    pthread_create(&thread_1, NULL, handler_1, NULL);
    pthread_setschedparam(thread_1,policy,&param); //I moved this from before pthread_create to after and it didn't make a difference that I can currently see
    pthread_join(thread_1, NULL);

    sleep(1);
    printf("after thread\n");

    //should check that all threads are finished before main can exit


}