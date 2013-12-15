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
    // clockid--ֵ��CLOCK_REALTIME,CLOCK_MONOTONIC��CLOCK_PROCESS_CPUTIME_ID,CLOCK_THREAD_CPUTIME_ID
    // evp--��Ż���ֵ�ĵ�ַ,�ṹ��Ա˵���˶�ʱ�����ڵ�֪ͨ��ʽ�ʹ���ʽ��
    // timerid--��ʱ����ʶ��
    timer_t timerid;
    struct sigevent evp;
    memset(&evp, 0, sizeof(struct sigevent));

    evp.sigev_value.sival_int = 111;                  // Ҳ�Ǳ�ʶ��ʱ���ģ����timerid��ʲô���𣿻ص��������Ի��
    evp.sigev_notify          = SIGEV_THREAD;         // �߳�֪ͨ�ķ�ʽ����פ���߳�
    evp.sigev_notify_function = timer_thread;         // �̺߳�����ַ

    if (timer_create(CLOCK_MONOTONIC, &evp, &timerid) == -1)
    {
        perror("fail to timer_create");
        exit(-1);
    }

    // XXX int timer_settime(timer_t timerid, int flags, const struct itimerspec *new_value,struct itimerspec *old_value);
    // timerid--��ʱ����ʶ
    // flags--0��ʾ���ʱ�䣬1��ʾ����ʱ��
    // new_value--��ʱ�����³�ʼֵ�ͼ�����������it
    // old_value--ȡֵͨ��Ϊ0�������ĸ�������ΪNULL,����ΪNULL���򷵻ض�ʱ����ǰһ��ֵ

    //��һ�μ��it.it_value��ô��,�Ժ�ÿ�ζ���it.it_interval��ô��,����˵it.it_value��0��ʱ���װ��it.it_interval��ֵ
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

    // �½���Ϣ����
    nMsgID = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if( nMsgID < 0 )
    {
        perror("msgget fail" );
        return;
    }
    printf("msgget success.\n");

    // ���� �ȴ���Ϣ����
    // 
    // msgrcv����Ϊ�����յ����źŶ��жϡ�����-1��errno������ΪEINTR��
    // ��ʹ�ڲ����ź�ʱ������SA_RESTART,Ҳ��Ч��man msgrcv����˵����
    // 
    struct msgst msg_st;
    if( -1 == msgrcv( nMsgID, (void*)&msg_st, 1, 0, 0 ) )
    {
        perror("msgrcv fail");
    }

    printf("done\n");

    exit(0);
}
