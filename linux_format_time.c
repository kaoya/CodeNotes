#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    
    exit(EXIT_SUCCESS);
}