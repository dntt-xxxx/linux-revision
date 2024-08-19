# if 1
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *mqname="/new";
    mqd_t mqd;
    struct mq_attr mqatt;


    mqd= mq_open(mqname, O_RDONLY | O_CREAT,  S_IRUSR | S_IWUSR, NULL);
    if (mqd == (mqd_t) -1)
    {
        perror("mq_open\n");
        exit(EXIT_FAILURE);
    }
    if (mq_getattr(mqd,&mqatt) == -1) {

        perror("mq_getattr\n");
        mq_close(mqd);
        exit(EXIT_FAILURE);

    }
    printf("MQ attribute default: flag:%ld  curmsg:%ld masmsg:%ld msgsize: %ld\n",mqatt.mq_flags,mqatt.mq_curmsgs,mqatt.mq_maxmsg,mqatt.mq_msgsize);
    
    char mes[100];

    if (mq_receive(mqd,mes,mqatt.mq_msgsize,0) == -1) {

        perror("mq_send\n");
        mq_close(mqd);
        exit(EXIT_FAILURE);
    }
    printf("read mes:%s\n",mes);

    char mes2[100];
    if (mq_receive(mqd,mes2,mqatt.mq_msgsize,2) == -1) {

        perror("mq_send\n");
        mq_close(mqd);
        exit(EXIT_FAILURE);
    }
    printf("read mes:%s\n",mes2);

    char mes3[100];
    if (mq_receive(mqd,mes3,mqatt.mq_msgsize,3) == -1) {

        perror("mq_send\n");
        mq_close(mqd);
        exit(EXIT_FAILURE);
    }
    printf("read mes:%s\n",mes3);
    mq_unlink(mqname);
    return 0;
}

#endif
