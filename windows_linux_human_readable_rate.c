/*********************************************************************
*
* ����: KaoYa
*
* ����: 2017-11-22
*
* ����: ������ɶ��Ը�ǿ���ٶ�ֵ�����в�ͬ��λ
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*****************************************************
**����: calc_rate
**����: �����ٶȣ���ת��Ϊ�ʺϵĵ�λ
**����: 
        [in] bytes - ���ֽ�Ϊ��λ���ֽ�����
        [in] secs  - ʱ��(��)
        [ut] units - ���� 0 for B/s, 1 for KB/s, 2 for MB/s, 3 for GB/s.
**����:
        �ɶ��Ը�ǿ�����֣���λͨ������units����
**��ע:
*****************************************************/
static double calc_rate(double bytes, double secs, int *units)
{
    double dlrate;
    double bibyte = 1024.0;

    assert(secs > 0);
    dlrate = bytes / secs;

    if (dlrate < bibyte) {
        *units = 0;
    } else if (dlrate < (bibyte * bibyte)) {
        *units = 1;
        dlrate /= bibyte;
    } else if (dlrate < (bibyte * bibyte * bibyte)) {
        *units = 2;
        dlrate /= (bibyte * bibyte);
    } else {
        *units = 3;
        dlrate /= (bibyte * bibyte * bibyte);
    }
    return dlrate;
}

/*****************************************************
**����: human_readable_rate
**����: �����ٶȣ������ؿɶ��Ը�ǿ���ַ�����������λ
**����: 
        [in] bytes    - ���ֽ�Ϊ��λ���ֽ�����
        [in] secs     - ʱ��(��)
        [out] buf     - ת������ַ���
        [in] bufsize  - buf�����С
**����:
        �ɶ��Ը�ǿ���ٶ��ַ��������е�λ
**��ע:
*****************************************************/
static char *human_readable_rate(double bytes, double secs, char *buf, int bufsize)
{
    int         units;
    double      dlrate;
    const char *rate_names[] = {"B/s", "KB/s", "MB/s", "GB/s"};

    memset(buf, 0x00, bufsize);

    dlrate = calc_rate (bytes, secs, &units);
    snprintf (buf, bufsize - 1, "%.*f %s",
        dlrate >= 99.95 ? 0 : dlrate >= 9.995 ? 1 : 2,
        dlrate, rate_names[units]);

    return buf;
} 

int main(int argc, char *argv[])
{
    int  i;
    char buf[50];
	struct {
        double bytes;
        double secs;
	} sample[] = {
        {1024.0 * 1024.0 * 1024.0 * 1024.0 * 2, 1},
        {1024.0 * 1024.0 * 1024.0 * 1024.0 * 2, 5},
        {1024.0 * 1024.0 * 1024.0 * 2,          1},
        {1024.0 * 1024.0 * 1024.0 * 2,          5},
        {1024.0 * 1024.0 * 2,                   1},
        {1024.0 * 1024.0 * 2,                   5},
        {1024.0 * 2,                            1},
        {1024.0 * 2,                            5},
	};

    for(i = 0; i < sizeof(sample)/sizeof(sample[0]); ++i) {
        printf("[%.2f in %.0f] -> [%s]\n", sample[i].bytes, sample[i].secs, human_readable_rate(sample[i].bytes, sample[i].secs, buf, sizeof(buf)));
    }

	/* The test prints the following:
	[2199023255552.00 in 1] -> [2048 GB/s]
	[2199023255552.00 in 5] -> [410 GB/s]
	[2147483648.00 in 1] -> [2.00 GB/s]
	[2147483648.00 in 5] -> [410 MB/s]
	[2097152.00 in 1] -> [2.00 MB/s]
	[2097152.00 in 5] -> [410 KB/s]
	[2048.00 in 1] -> [2.00 KB/s]
	[2048.00 in 5] -> [410 B/s]
	*/

	

    return 0;
}