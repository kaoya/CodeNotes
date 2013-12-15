#include <stdio.h>
#include <time.h>
#include <signal.h>
 
#define DIAPAUSE 30    //sleep time 30s
#define TIMEOUT 5

void sigalrm(int signo);


/*
 * sleep() makes the current process sleep until seconds seconds have elapsed or a signal arrives which is not ignored.
 * 即使信号处理设置了SA_RESTART也没用
 */
int main()
{
     struct sigaction sa;

     sa.sa_handler = sigalrm;
     sigemptyset(&sa.sa_mask);
     sa.sa_flags = 0;
     sa.sa_flags |= SA_RESTART;
     if(sigaction(SIGALRM, &sa, NULL) < 0)
     {
             printf("sigaction error!\n");
             return;
     }

     while(1)
     {
             printf("alarm(TIMEOUT)...\n");
             alarm(TIMEOUT);
             printf("...\n");
             printf("sleep(DIAPAUSE) == %d\n", sleep(DIAPAUSE));
     }

     return 0;
}

void sigalrm(int signo)
{
     printf("timeout...\n");
     return;
}

