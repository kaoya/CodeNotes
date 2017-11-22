/*********************************************************************
*
* ����: KaoYa
*
* ����: 2017-11-22
*
* ����: ������ת��Ϊ�ɶ��Ը�ǿ��ʱ���ַ���
*
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************
**����: human_readable_secs
**����: ������ת��Ϊ�ɶ��Ը�ǿ��ʱ���ַ���
**����: 
        [in] secs      - ����
        [in] separator - ʱ����֮��ķָ���
        [out] buf      - ת������ַ���
        [in] bufsize   - buf�����С
**����:
        �ɶ��Ը�ǿ��ʱ���ַ���
**��ע:
*****************************************************/
static char *human_readable_secs(int secs, char separator, char *buf, int bufsize)
{
  if (secs < 100)
    snprintf (buf, bufsize, "%ds", secs);
  else if (secs < 100 * 60)
    snprintf (buf, bufsize, "%dm%c%ds", secs / 60, separator, secs % 60);
  else if (secs < 48 * 3600)
    snprintf (buf, bufsize, "%dh%c%dm", secs / 3600, separator, (secs / 60) % 60);
  else if (secs < 100 * 86400)
    snprintf (buf, bufsize, "%dd%c%dh", secs / 86400, separator, (secs / 3600) % 24);
  else
    snprintf (buf, bufsize, "%dd", secs / 86400);

  return buf;
}

int main(int argc, char *argv[])
{
    int  i;
    char buf[50];
    int  sample_secs[] = {
        0,
        5,
        60,
        100,
        60*5,
        60*60,
        60*60 + 1,
        60*60*24,
        60*60*25 + 60 +1,
	};

    for(i = 0; i < sizeof(sample_secs)/sizeof(sample_secs[0]); ++i) {
        printf("[%d] -> [%s]\n", sample_secs[i], human_readable_secs(sample_secs[i], ':', buf, sizeof(buf)));
    }

    /* The test prints the following:
    [0] -> [0s]
    [5] -> [5s]
    [60] -> [60s]
    [100] -> [1m:40s]
    [300] -> [5m:0s]
    [3600] -> [60m:0s]
    [3601] -> [60m:1s]
    [86400] -> [24h:0m]
    [90061] -> [25h:1m]
    */

    return 0;
}