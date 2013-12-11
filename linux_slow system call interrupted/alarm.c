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

    // ��׽������Ϣ��
    struct sigaction action;
    action.sa_handler = ding;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    // �汾1:������SA_RESTART����
    // �汾2:����SA_RESTART����
    action.sa_flags |= SA_RESTART;
    sigaction(SIGALRM, &action, NULL);
    
    alarm(3);
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
