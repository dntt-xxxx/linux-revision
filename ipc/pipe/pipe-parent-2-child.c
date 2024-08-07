#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int g_data=111;

int main(int argc, char const *argv[])
{
    int s_data=222;
    pid_t pid=getpid();
    pid_t cid;
    pid_t child_id;
    printf("Parent PID: %d\n",getpid());
    int status;
    int fd[2];
    int byte_r=0;
    int byte_w=0;
    char read_buf[100];
     char write_buf[]="dotudafjaskjfds;f";
    status = pipe(fd);
    if (status == -1)
    {
        perror("create pipe fails\n");
        exit(EXIT_FAILURE);
    }
    

    switch (child_id=fork())
    {
    case -1 /*create fails */:
        printf("create process fails\n");
        exit(-1);
    case 0 /* child process */:
        /* code */
        cid=getpid();
        // close write fd of child process
        close(fd[1]);

        // wait parent write data to pipe
        while (1)
        {
            byte_r=read(fd[0],read_buf,50);
            
            if (byte_r == -1)
            {
                exit(EXIT_FAILURE);
            }
            else if (byte_r == 0)
            {
                printf("Parent close write end -EOF \n");
                break;
            }
            
            printf("Read: %d: %s\n",byte_r,read_buf);
            
        }
        close(fd[0]);
        printf("child PID exit\n");
        break;
    default /* parent process */:
        close(fd[0]);
        byte_w = write(fd[1],write_buf,sizeof(write_buf));
        sleep(2);
        close(fd[1]);
        waitpid(child_id,NULL,0);
        
        printf("parent exit\n");
        break;
    }
    
    return 0;
}
// output
// Parent PID: 10943
// Parent PID after fork(): 10943 g:111 s:222 
// child PID: 10944 g:112 s:223 
// End PID: 10944 g:112 s:223 