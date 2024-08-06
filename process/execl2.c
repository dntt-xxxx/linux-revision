#include<stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("New program loaded by execl in main program: %d\n",getpid());
   for(int i=0; i<= argc;i++) {
    printf("%d: %s\n",i,argv[i]);
   }
    
    printf("this line will be printed.");

    exit(1);
}
