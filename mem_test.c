#include <string.h>
#include <stdlib.h>
#include <stdio.h> 
#include <fcntl.h> 
#include <malloc.h>
#include <unistd.h>
    const char a ='c';
int main(){

    char *buf="wellcome";
    char b='b';
    char array[]="dotu";
    printf("Addr of const a: %x\n",&a);
    printf("Addr of buf:\n");
    printf("&buf[0]=%x\n",&buf[0]);
    printf("&buf[1]=%x\n",&buf[1]);
    printf("&buf[2]=%x\n",&buf[2]);
    printf("&buf[3]=%x\n",&buf[3]);

    printf("Addr of const b: %x\n",&b);
    printf("Addr of array:\n");
    printf("&array[0]=%x\n",&array[0]);
    printf("&array[1]=%x\n",&array[1]);
    printf("&array[2]=%x\n",&array[2]);
    printf("&array[3]=%x\n",&array[3]);

    // buf[1] = 'b';
    array[1] = 'b';
    return 0;
}