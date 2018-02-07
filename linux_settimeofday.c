/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2018-2-7
*
* 描述: linux下设置系统时间（不受时区影响），
*       函数 strptime 和 mktime 内部已经根据时区做了调整，不需要我们操心。
*
*********************************************************************/
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define TIME_STR    "2018-02-07 10:00:00"

int main()
{
    struct tm tm;
    struct timeval tv;

    // convert str to tm
    memset(&tm, 0, sizeof(struct tm));
    strptime(TIME_STR, "%Y-%m-%d %H:%M:%S", &tm);

    // set time
    tv.tv_sec = mktime(&tm);
    tv.tv_usec = 0;
    settimeofday(&tv, NULL);

    return 0;
}
