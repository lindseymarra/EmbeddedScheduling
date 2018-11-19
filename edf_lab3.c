#include<stdio.h>                      


int periodA, periodB; // periods of each process (deadline for each process is that it must complete within its period)
int executionA, executionB; // execution time for each process
int deadline, deadlineA, deadlineB; // calculated deadline for the task at a given time slice
int t; // units of time are schedulable time slices
int task_finish; // time a task is complete
int task, taskA, taskB; // integer for current task for each process
char current_task; // current task identifier
int nextA, nextB; // sets the next time the process should generate a task
int leftoverB, leftoverA; // keeps track of how much of a task is left if it's interrupted


int start_task(int t, int execution_time)
{
    
    return t+execution_time;
}


void main()
{

    printf("\t\t\tearliest deadline first schedule algorithm\n");
    printf("\t\t\t------------------------------------------------\n");
    printf("Input period for process A:\n");
    scanf("%d", &periodA);
    printf("Input execution time for process A:\n");
    scanf("%d", &executionA);
    printf("Input period for process B:\n");
    scanf("%d", &periodB);
    printf("Input execution time for process B:\n");
    scanf("%d", &executionB);

    taskA = 1;
    taskB = 1;
    nextA = 0;
    nextB = 0;
    
    for(t=0; t<=100; t++) // the scheduler is run once every time slice to choose which is the next process to run
    {
                
        
        if(t==nextA)
        {
            printf("task %c%d released at time %d\n", 'A', taskA, t);

        }
        if(t==nextB)
        {
            printf("task %c%d released at time %d\n", 'B', taskB, t);

        }

        
        if(t==0) // skip checking if the running task is complete since neither have started yet
        {
            // calculate and then compare deadlines 
            deadlineA = t+periodA;
            deadlineB = t+periodB;
            if (deadlineA < deadlineB)
            {
                current_task = 'A';
                task = taskA;
                deadline = deadlineA;
                deadlineA = nextA+periodA;
                task_finish = start_task(t,executionA);
                if(task_finish>deadline)
                {
                    printf("task %c%d will miss deadline %d due to overload\n", current_task, task, deadline);
                    break;
                }
                printf("task %c%d started at time %d with deadline %d\n", current_task, task, t, deadlineA); 
                taskA = taskA+1;
                nextA = nextA+periodA;
            }
            else
            {
                current_task = 'B';

                task = taskB;
                deadline = deadlineB;
                deadlineB = nextB+periodB;
                task_finish = start_task(t,executionB);
                if(task_finish>deadline)
                {
                    printf("task %c%d will miss deadline %d due to overload\n", current_task, task, deadline);
                    break;
                }
                printf("task %c%d started at time %d with deadline %d\n", current_task, task, t, deadlineB);
                taskB = taskB+1;
                nextB = nextB+periodB;

            }


        }
        
        

        if(t==task_finish) // checks if the running task has finished
        {
            printf("task %c%d completed at time %d\n", current_task, task, t);  
            // calculate and then compare deadlines 
            deadlineA = nextA;
            deadlineB = nextB;
            if (deadlineA < deadlineB)
            {
                current_task = 'A';
                task = taskA;
                deadline = deadlineA;
                task_finish = start_task(t,executionA);
                if(task_finish>deadlineA)
                {
                    printf("task %c%d will miss deadline %d due to overload\n", current_task, task, deadline);
                    break;
                }
                printf("task %c%d started at time %d with deadline %d\n", current_task, task, t, deadlineA); 
                taskA = taskA+1;
                nextA = nextA+periodA;


            }
            else
            {
                current_task = 'B';

                task = taskB;
                deadline = deadlineB;
                deadlineB = nextB+periodB;
                task_finish = start_task(t,executionB);
                if(task_finish>deadlineB)
                {
                    printf("task %c%d will miss deadline %d due to overload\n", current_task, task, deadline);
                    break;
                }
                printf("task %c%d started at time %d with deadline %d\n", current_task, task, t, deadlineB);
                taskB = taskB+1;
                nextB = nextB+periodB;

            }

        }

    }

}

