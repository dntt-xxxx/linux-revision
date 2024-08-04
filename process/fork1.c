#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int g_data=111;

int main(int argc, char const *argv[])
{
    int s_data=222;
    pid_t pid=getpid();
    pid_t cid;
    pid_t child_id;
    printf("Parent PID: %d\n",getpid());
    switch (child_id=fork())
    {
    case -1 /*create fails */:
        printf("create process fails\n");
        exit(-1);
    case 0 /* child process */:
        /* code */
        cid=getpid();
        g_data++;
        s_data++;
        printf("child PID: %d g:%d s:%d \n",getpid(),g_data, s_data);
        sleep(5);
        break;
    default /* parent process */:
        printf("Parent PID after fork(): %d g:%d s:%d \n",getpid(),g_data, s_data);
        sleep(5);
        break;
    }
    // dost
    if (getpid() == cid){
        printf("End PID: %d g:%d s:%d \n",getpid(),g_data, s_data);
    }
    
    return 0;
}
// output
// Parent PID: 10943
// Parent PID after fork(): 10943 g:111 s:222 
// child PID: 10944 g:112 s:223 
// End PID: 10944 g:112 s:223 