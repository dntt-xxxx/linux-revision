/* Program to demonstrate wait and exit*/

#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 
  
int main() 
{ 
    pid_t cpid1; 
    pid_t cpid2; 
    int status = 0;
    cpid1 = fork();
    if(cpid1 == -1)
        exit(-1);           /* terminate child */

    if(cpid1 == 0){
        printf("\nchild 1 executing its pid = (%d)\n",getpid());
        sleep(5);
        printf("Child1 exit pid = %d\n", getpid()); 
        exit(1);
    } 
    else{
        cpid2=fork();
        if (cpid2 == -1)
        {
            exit(-1);
        }
        else if (cpid2 == 0)
        {
            /* child */
            printf("\nchild 2 executing its pid = (%d)\n",getpid());
            sleep(10);
            printf("Child 2 exit pid = %d\n", getpid()); 
            exit(1);
        }
        else {
            printf("\n Parent waiting()\n");
            // cpid = wait(NULL); 
            cpid2 = waitpid(cpid2,&status,0); 
            printf("\n wait() in parent done\nParent pid = %d\n", getpid()); 
            printf("\n cpid returned is (%d)\n",cpid2);
            printf("\n status is (%d)\n",status);

            // cpid1 = waitpid(cpid1,&status,0); 
            // printf("\n wait() in parent done\nParent pid = %d\n", getpid()); 
            // printf("\n cpid returned is (%d)\n",cpid2);
            // printf("\n status is (%d)\n",status);
        }
        
    }
  
    return 0; 
} 



