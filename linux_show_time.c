#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    time_t    t;
    struct tm tm;

    t = time(NULL);
	printf("time() is:                      %ld\n\n", t);
	
	gmtime_r(&t, &tm);
	printf("gmtime_r() of time() is:        %04d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	//printf("mktime() of gmtime_r() is:      %ld, after - timezone is: %ld\n\n",  mktime(&tm), mktime(&tm) - timezone);
	printf("mktime() of gmtime_r() is:      %ld\n\n",  mktime(&tm));

	localtime_r(&t, &tm);
	printf("localtime_r() of time() is:     %04d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("mktime() of localtime_r() is: 	%ld\n", mktime(&tm));
	
	return 0;
}
