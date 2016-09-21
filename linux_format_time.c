#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/************************************************************************
**函数：format__DATE__TIME__
**功能：格式化标准预定义宏__DATE__和__TIME__，转化为yyyy-mm-dd HH:MM:SS格式
**参数：无
**返回：none
**作者：KaoYa, 2016-09-21
**备注：
    1). __DATE__的格式为（举例）：Sep 21 2016
        __TIME__的格式为（举例）：09:56:54
************************************************************************/
void format__DATE__TIME__(void)
{
    char *ret;
    char des[50];
    struct tm tm;
    static const char *src = __DATE__" "__TIME__;

    memset(&tm, 0, sizeof(struct tm));
    ret = strptime(src, "%b %d %Y %H:%M:%S", &tm);
    assert(ret);
    
    strftime(des, sizeof(des), "%G-%m-%d %H:%M:%S", &tm);
    printf("[%s] >>> [%s]\n", src, des);
}

int main(void)
{
    struct tm tm;
    char buf[255];
    
    // print now time in str
    time_t t;
    t = time(NULL);
    localtime_r(&t, &tm);
    strftime(buf, sizeof(buf), "%G-%m-%d %H:%M:%S", &tm);
    puts(buf);
    
    // convert str to tm
    memset(&tm, 0, sizeof(struct tm));
    strptime("2013-07-01 15:57:49", "%Y-%m-%d %H:%M:%S", &tm);
    
    strftime(buf, sizeof(buf), "%G-%m-%d %H:%M:%S", &tm);
    puts(buf);
    
    format__DATE__TIME__();
    
    exit(EXIT_SUCCESS);
}