#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void ding(int sig)
{
    printf("Ding!\n");
}

struct msgst
{
    long int msg_type;
    char buf[1];
};

int main()
{
    int nMsgID = -1;

    // 捕捉闹钟信息号
    struct sigaction action;
    action.sa_handler = ding;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    // 版本1:不设置SA_RESTART属性
    // 版本2:设置SA_RESTART属性
    action.sa_flags |= SA_RESTART;
    sigaction(SIGALRM, &action, NULL);
    
    alarm(3);
    printf("waiting for alarm to go off\n");

    // 新建消息队列
    nMsgID = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if( nMsgID < 0 )
    {
        perror("msgget fail" );
        return;
    }
    printf("msgget success.\n");

    // 阻塞 等待消息队列
    // 
    // msgrcv会因为进程收到了信号而中断。返回-1，errno被设置为EINTR。
    // 即使在插入信号时设置了SA_RESTART,也无效。man msgrcv就有说明。
    // 
    struct msgst msg_st;
    if( -1 == msgrcv( nMsgID, (void*)&msg_st, 1, 0, 0 ) )
    {
        perror("msgrcv fail");
    }

    printf("done\n");

    exit(0);
}
