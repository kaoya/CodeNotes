/*********************************************************************
*
* ����: KaoYa
*
* ����: 2018-2-7
*
* ����: linux������ϵͳʱ�䣨����ʱ��Ӱ�죩��
*       ���� strptime �� mktime �ڲ��Ѿ�����ʱ�����˵���������Ҫ���ǲ��ġ�
*
*********************************************************************/
#define _XOPEN_SOURCE       // for strptime
#define _BSD_SOURCE         // for settimeofday
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define TIME_STR    "2018-02-07 10:00:00"

int main()
{
    struct tm tm;

    memset(&tm, 0, sizeof(struct tm));
    if (NULL != strptime(TIME_STR, "%Y-%m-%d %H:%M:%S", &tm)) {                 // convert str to tm
        struct timeval tv;
        tv.tv_sec = mktime(&tm);                                                // convert tm to sec
        tv.tv_usec = 0;
        settimeofday(&tv, NULL);                                                // set time
    }

    return 0;
}
