/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2013-1-24
*
* 描述: linux时间格式化以及变长函数的实现
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

/************************************************************************
**函数：PrtLog
**功能：linux时间格式化以及变长函数的实现
**参数：略
**返回：none
**作者：KaoYa, 2013-1-24
**备注：
    1). asctime(), ctime(), gmtime() and localtime() return a pointer to 
    static data and hence are not thread-safe, Thread-safe versions asctime_r(), 
    ctime_r(), gmtime_r() and localtime_r().
************************************************************************/
void PrtLog(const char *format, ...)
{
    char buf[1024];
    char szTime[30];
    time_t t;
    struct tm tmp;
    
    va_list ap;
    va_start(ap, format);
    vsnprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    t = time(NULL);
    localtime_r(&t, &tmp);
    strftime(szTime, sizeof(szTime), "%G-%m-%d %H:%M:%S", &tmp);
    
    printf("[%s] %s\n", szTime, buf);
}


int main(int argc, char *argv[])
{
    PrtLog("something error!");

    return 0;
}
