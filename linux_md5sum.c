#include <stdio.h>
#include <time.h>
#include <unistd.h>

int md5sum(const char *file, char *md5, unsigned int md5size)
{
    FILE *fp;
    char cmd[50];

#define MD5_STR_LEN 32

    if (md5size <= MD5_STR_LEN) {
        return -1;
    }

    if (0 != access(file, F_OK)) {
        return -1;
    }

    snprintf(cmd, sizeof(cmd), "md5sum %s | awk '{print $1}'", file);
    fp = popen(cmd, "r");
    fread(md5, md5size, 1, fp);
    pclose(fp);

    md5[MD5_STR_LEN] = 0x00;

    return 0;
}

int main()
{
    char md5[50];

    if (0 == md5sum("/share/git-prompt.sh", md5, sizeof(md5))) {
        printf("md5 = [%s]\n", md5);
    }

    return 0;
}

