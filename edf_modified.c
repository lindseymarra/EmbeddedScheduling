#include<stdio.h>                      // A execution time 10, period: 20
									   // B execution time 25, period: 50
int main()
{
 int A,B;                           //arrival time of process A and B
 int cycA,cycB,serveA,serveB;         //period and execution for A and B processes
 float m;
 int i,j,a=0,b=0,ka=0,kb=0;                 /*ka,kb is a switch and 
 											i, j, a, b, to record status of each process*/
 int numa=0,numb=0;                         //accumulated execution time
 int T;
 printf("\t\t\t------------------------------------------------\n");
 printf("\t\t\tRMS modified to be EDF by Lindsey Marra\n");
 printf("\t\t\t------------------------------------------------\n");
 printf("please input period and execution for A process\n");
 scanf("%d%d",&cycA,&serveA);
 printf("please input period and execution for B process\n");
 scanf("%d%d",&cycB,&serveB);
 m=(float)serveA/cycA+(float)serveB/cycB;
 
 int nextA=0, nextB=0;
 
 for(T=0;T<=100;T++)
 {
  
  // this block is to check if CPU can schedule	
  if(m>1)
  {
   printf("utilization will be greater than 1. can't schedule");
   break; //exit the program if the processes can't be scheduled
  }
 

  /* this block is to say that process A has been done*/
  /* but process B has not been done yet*/
  if(numa==serveA)                                        //process A is done
  {
   numa=serveA+1;
   printf("when T=%d, ",T);
   printf("process A%d is done\n",a);
   if(numb<serveB)
   {
    printf("run process B%d\n",b);
    kb=1;
   }
   ka=0;
  }

  /* this block is to say that process B has been done*/
  /* but process A has not been done yet*/
  if(numb==serveB)
  {
   numb=serveB+1;
   printf("when T=%d, ",T);
   printf("process B%d is done\n",b);
   if(numa<serveA)
   {
    printf("run process A%d\n",a);
    ka=1;
   }
   kb=0;
  }

  /* this block start running the process*/
  if(T%cycA==0 && T%cycB==0)
  {
   A=B=T;
   j=++a;
   i=++b;
   printf("when T=%d, process A%d and process B%d are generated together\n",T,j,i);
   if(cycA<=cycB) // deadline is cycle
   {
       printf("run process A%d and suspend process B%d\n",j,i);
       printf("---------------------------------------\n");
       ka=1;
       kb=0;
	  
   }
   else
   {
    printf("run process B%d and suspend process A%d\n",i,j);
    ka=0;
    kb=1;
   }
   numa=numb=0;
   nextA = cycA; //sets next period or deadline for both processes
   nextB = cycB;
  }
  

  /* this block initializes A another new period*/ 
  if(T%cycA==0&&T%cycB!=0)
  {
   A=T;
   
   nextA = T+cycA; //also sets the next period for A
  
   
   printf("when T=%d, ",T);
   printf("process A%d is generated\n",++a);   //impossible to compete with A
   numa=0;
   if(numb<serveB)                //process B is unfinished yet
	if(nextB>nextA)         
    {
     printf("run process A%d\n",a);
        ka=1;
        kb=0;
    }
    else                     //period of B is earlier than period of A
     printf("process B%d is moving forward\n",b);
   else                                   //process B is done, just run A
    {
     printf("process A%d is run\n",a);
     ka=1;
    }
  }
  

  /* this block initializes B another new period*/
  if(T%cycA!=0&&T%cycB==0)
  {
   B=T;
   
   nextB = T+cycB; //also sets the next period for A
   printf("when T=%d, ",T);
   printf("process B%d is generated\n",++b);            //impossible to compete with B
   numb=0;
   if(numa<serveA)                         //process A is undone yet
    if(nextA<nextB)               
     printf("process A%d is on run\n",a);
    else
    {
        printf("process B%d is to run\n",b);
        kb=1;
        ka=0;
    }
   else                                //process A is done
    {
        printf("process B%d is on run\n",b);
        kb=1;
    }
  }
  

  /* this block is to accumulate running time*/
  if(ka)
    numa++;
  if(kb)
   numb++;
  

 }
 return 1;
}
