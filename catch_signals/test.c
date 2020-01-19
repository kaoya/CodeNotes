#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

static void handler(int sig)
{
    printf("PID=%ld: caught signal %d (%s)\n", (long) getpid(), sig, strsignal(sig));
}

static void catch_signals(void)
{
    int n = 0;
    struct sigaction sa;

    for (n = 1; n < NSIG; n++) {
        sigemptyset(&sa.sa_mask);
        sa.sa_handler = handler;
        sa.sa_flags   = 0;
        sigaction(n, &sa, NULL);
    }
}

static void ignore_signals(void)
{
    signal(SIGINT, SIG_IGN);
}

static void write_udisk(void)
{
#define WRITE_BUF_SIZE      (512)
#define WRITE_BUF_MAX       (1024 * 1024 * 64)

    int     i;
    int     fd = -1;
    int     writebytes = 0;
    int     totalwritebytes = 0;
    char    writebuf[WRITE_BUF_SIZE + 1];
    char    filename[] = "/mnt/usb_storage/test.data";

    fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd < 0) {
        printf("fail to open %s, errno = %d (%s)\n", filename, errno, strerror(errno));
        goto EXIT;
    }
    printf("suss to open %s\n", filename);

    do {
        writebytes = write(fd, writebuf, WRITE_BUF_SIZE);
        if (writebytes < 0) {
            printf("fail to write, errno=%d (%s)\n", errno, strerror(errno));
            goto EXIT;
        }
        totalwritebytes += writebytes;
    } while (totalwritebytes < WRITE_BUF_MAX);

    for (i=10; i>0; i--) {
        printf("Pull out UDISK in %d seconds...\n", i);
        sleep(1);
    }

EXIT:
    
    if(fd > 0) {
        close(fd);
        fd = -1;
    }
    return;
}

int main (int argc, char *argv[])
{
    catch_signals();
    ignore_signals();
    write_udisk();

    printf("exit programe....\n");
    return 0;
}
