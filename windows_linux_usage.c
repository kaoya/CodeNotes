/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2017-06-29
*
* 描述: 演示usage的使用方法
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

static void usageError(char *progName, char *msg, int shortUsage)
{
    if (msg != NULL)
        fprintf(stderr, "%s\n", msg);

    if (shortUsage) {
        fprintf(stderr, "Type '%s -h' for usage information\n", progName);
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Usage: %s [-h] [-x Addr] [-u Username:Password] [-s StreamNo]\n\n", progName);
#define fpe(msg) fprintf(stderr, "      " msg);
    fpe("-h  Show usage information.\n\n");
    fpe("-x  Specifies one device services address.\n");
    fpe("    By default, the address is obtained by searching, and may search for multiple devices.\n\n");
    fpe("-u  Specifies username and password.\n\n");
    fpe("    By default, username is 'admin', password is 'admin'.\n\n");
    fpe("-s  Specifies media stream number, 0 for the main stream, 1 for the sub stream, and so on..\n");
    fpe("    By default, stream number is 0.\n\n");

    fprintf(stderr, "Examples: %s -h\n", progName);
    fprintf(stderr, "      or: %s -x \"http://100.100.100.31:80/onvif/device_service\" -s 1 -u admin:admin1234\n\n", progName);

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int opt;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        usageError(argv[0], NULL, 0);
    }

    while ((opt = getopt(argc, argv, "hx:u:s:")) != -1) {
        switch (opt) {
        case 'h':
            usageError(argv[0], NULL, 0);
            break;

        case 'x':
            break;

        case 'u':
            break;

        case 's':
            printf("optarg = %s\n", optarg);
            break;

        default:
            usageError(argv[0], "Bad option\n", 1);
            break;
        }
    }
    
    /* ... */
    
    return 0;
}