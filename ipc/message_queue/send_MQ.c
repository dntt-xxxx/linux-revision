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


    mqd= mq_open(mqname, O_WRONLY | O_CREAT, 0660, NULL);
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
    
    char* mes="DONGOCTHANHTU";
    if (mq_send(mqd,mes,strlen(mes),0) == -1) {

        perror("mq_send\n");
        mq_close(mqd);
        exit(EXIT_FAILURE);
    }
    char* mes2="DONGOCTHANHTU2";
    if (mq_send(mqd,mes2,strlen(mes2),2) == -1) {

        perror("mq_send\n");
        mq_close(mqd);
        exit(EXIT_FAILURE);
    }
        char* mes3="DONGOCTHANHTU3";
    if (mq_send(mqd,mes3,strlen(mes3),5) == -1) {

        perror("mq_send\n");
        mq_close(mqd);
        exit(EXIT_FAILURE);
    }
    printf("send mes:%s\n",mes);
    
    if (mq_getattr(mqd,&mqatt) == -1) {

        perror("mq_getattr\n");
        mq_close(mqd);
        exit(EXIT_FAILURE);

    }
    printf("MQ attribute default: flag:%ld  curmsg:%ld masmsg:%ld msgsize: %ld\n",mqatt.mq_flags,mqatt.mq_curmsgs,mqatt.mq_maxmsg,mqatt.mq_msgsize);
    
    return 0;
}

#endif

#if 0
/* message queue sender*/
/* usage : <executable file> </msgqueue name> <message>*/

#include <fcntl.h>
#include <limits.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    mqd_t queue;
    struct mq_attr attrs;
    size_t msg_len;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <queuename> <message>\n", argv[0]);
        return 1;
    }

    queue = mq_open(argv[1], O_WRONLY | O_CREAT, 0660, NULL); // Open message queue with default attributes
    if (queue == (mqd_t)-1)
    {
        perror("mq_open");
        return 1;
    }

    if (mq_getattr(queue, &attrs) == -1)
    {
        perror("mq_getattr");
        mq_close(queue);
        return 1;
    }
    // print the attribute values
    printf("\n message queue mq_maxmsg = (%d), mq_msgsize is (%d)\n",(int)attrs.mq_maxmsg, (int)attrs.mq_msgsize);

    msg_len = strlen(argv[2]);
    if ( (long)msg_len > attrs.mq_msgsize)
    {
        fprintf(stderr, "Your message is too long for the queue.\n");
        mq_close(queue);
        return 1;
    }

    if (mq_send(queue, argv[2], strlen(argv[2]), 0) == -1) // 0 is the priority that can be set based on message priority 0 is least priority
    {
        perror("mq_send");
        mq_close(queue);
        return 1;
    }

    return 0;
}


#endif