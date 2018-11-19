#include<stdio.h>                      


int periodA, periodB; // periods of each process (deadline for each process is that it must complete within its period)
int executionA, executionB; // execution time for each process
int deadline, deadlineA, deadlineB; // calculated deadline for the task at a given time slice
int t; // units of time are schedulable time slices
int task_finish; // time a task is complete
int task, taskA, taskB; // integer for current task for each process
char current_task; // current task identifier
int nextA, nextB; // sets the next time the process should generate a task

int calculate_deadline(int t, int period)
{
    return t+period;
}

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

    taskA = 0;
    taskB = 0;
    nextA = 0;
    nextB = 0;
    
    for(t=0; t<=100; t++) // the scheduler is run once every time slice to choose which is the next process to run
    {
        
        if(t==nextA)
        {
            printf("task %c%d released at time %d\n", 'A', taskA, t);
            nextA = t+periodA;
        }
        if(t==nextB)
        {
            printf("task %c%d released at time %d\n", 'B', taskB, t);
            nextB = t+periodB;
        }
            

        
        if(t==0) // skip checking if the running task is complete since neither have started yet
        {
            // calculate and then compare deadlines 
            printf("generate A and B together at time 0\n");
            deadlineA = calculate_deadline(t, periodA);
            deadlineB = calculate_deadline(t, periodB);
            if (deadlineA < deadlineB)
            {
                current_task = 'A';
                taskA = taskA+1;
                task = taskA;
                deadline = deadlineA;
                task_finish = start_task(t,executionA);
                printf("task %c%d started at time %d with deadline %d\n", current_task, task, t, nextA); 
                deadlineA = calculate_deadline((t+executionA), periodA);
                

            }
            else
            {
                current_task = 'B';
                taskB = taskB+1;
                task = taskB;
                deadline = deadlineB;
                task_finish = start_task(t,executionB);
                printf("task %c%d started at time %d with deadline %d\n", current_task, task, t, nextB);
                deadlineB = calculate_deadline((t+executionB), periodB);


            }
        
                nextA = t + periodA; // calculate the next time A will be generated
                nextB = t + periodB; // calculate the next time B will be generated
        }
        
        

        if(t==task_finish) // checks if the running task has finished
        {
            printf("task %c%d completed at time %d\n", current_task, task, t);  
            if (current_task == 'A')
            {
                current_task = 'B';
                taskB = taskB+1;
                task = taskB;
                deadline = deadlineB;
                task_finish = start_task(t,executionB);
                printf("task %c%d started at time %d with deadline %d\n", current_task, task, t, nextB);
                deadlineB = calculate_deadline((t+executionB), periodB);
            }
            else
            {
                current_task = 'A';
                taskA = taskA+1;
                task = taskA;
                deadline = deadlineA;
                task_finish = start_task(t,executionA);
                printf("task %c%d started at time %d with deadline %d\n", current_task, task, t, nextA);
                deadlineA = calculate_deadline((t+executionA), periodA);
            }

        }

    }

}

