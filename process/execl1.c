#include<stdio.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("Main process pid: %d\n",getpid());
    execl("./execl2","do","ngoc","thanh","tu",NULL);
    
    printf("this line will not be printed.");

    return 0;
}
