#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void timer_thread(union sigval v)
{
    printf("timer_thread function! %d\n", v.sival_int);
}

struct msgst
{
    long int msg_type;
    char buf[1];
};

int main()
{
    int nMsgID = -1;

    // XXX int timer_create(clockid_t clockid, struct sigevent *evp, timer_t *timerid);
    // clockid--值：CLOCK_REALTIME,CLOCK_MONOTONIC，CLOCK_PROCESS_CPUTIME_ID,CLOCK_THREAD_CPUTIME_ID
    // evp--存放环境值的地址,结构成员说明了定时器到期的通知方式和处理方式等
    // timerid--定时器标识符
    timer_t timerid;
    struct sigevent evp;
    memset(&evp, 0, sizeof(struct sigevent));

    evp.sigev_value.sival_int = 111;                  // 也是标识定时器的，这和timerid有什么区别？回调函数可以获得
    evp.sigev_notify          = SIGEV_THREAD;         // 线程通知的方式，派驻新线程
    evp.sigev_notify_function = timer_thread;         // 线程函数地址

    if (timer_create(CLOCK_MONOTONIC, &evp, &timerid) == -1)
    {
        perror("fail to timer_create");
        exit(-1);
    }

    // XXX int timer_settime(timer_t timerid, int flags, const struct itimerspec *new_value,struct itimerspec *old_value);
    // timerid--定时器标识
    // flags--0表示相对时间，1表示绝对时间
    // new_value--定时器的新初始值和间隔，如下面的it
    // old_value--取值通常为0，即第四个参数常为NULL,若不为NULL，则返回定时器的前一个值

    //第一次间隔it.it_value这么长,以后每次都是it.it_interval这么长,就是说it.it_value变0的时候会装载it.it_interval的值
    struct itimerspec it;
    it.it_interval.tv_sec  = 2;
    it.it_interval.tv_nsec = 0;
    it.it_value.tv_sec     = 5;
    it.it_value.tv_nsec    = 0;

    if (timer_settime(timerid, 0, &it, NULL) == -1)
    {
        perror("fail to timer_settime");
        exit(-1);
    }

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
