/*********************************************************************
*
* ����: KaoYa
*
* ����: 2017-11-22
*
* ����: ���ֽ�Ϊ��λ������ת��Ϊ�ɶ��Ը�ǿ�ĵ�λ(KB/MB/GB��)
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************
**����: human_readable_bytes
**����: ���ֽ�Ϊ��λ������ת��Ϊ�ɶ��Ը�ǿ�ĵ�λ(KB/MB/GB��)������
**����: 
        [in] bytes    - ��ת�������ֽ�Ϊ��λ������
        [in] acc      - ת����Ľ�����ڵ���acc���Ͳ���ʾС��λ��С��acc��ʾС�����decimalsλ
        [in] decimals - ���accһ��ʹ�ã����ڿ�����ʾС������λ��
        [out] buf     - ת������ַ���
        [in] bufsize  - buf�����С
**����:
        �ɶ��Ը�ǿ�������ַ��������е�λ
**��ע:
*****************************************************/
static char *human_readable_bytes(double bytes, int acc, int decimals, char *buf, int bufsize)
{
    size_t  i;
	char    powers[] = {'K', 'M', 'G', 'T', 'P', 'E'};

	memset(buf, 0x00, bufsize);

	if (bytes < 1024) {
		snprintf(buf, bufsize - 1, "%d", (int)bytes);
		return buf;
	}
	for (i = 0; i < sizeof(powers); i++) {
		if ((bytes / 1024) < 1024 || i == sizeof(powers) - 1) {
			double val = bytes / 1024.0;
			snprintf(buf, bufsize-1, "%.*f%c", val < acc ? decimals : 0, val, powers[i]);
			return buf;
		}
		bytes /= 1024;
	}
	return buf;
}

int main(int argc, char *argv[])
{
    int  i;
    char buf[50];
    double sample_bytes[] = {
        0,

        1024.0 - 1,
        1024.0,
        1024.0 + 1,
        1024.0 * 11,

        1024.0 * 1024.0 - 1,
        1024.0 * 1024.0,
        1024.0 * 1024.0 + 1,
        1024.0 * 1024.0 * 12,

        1024.0 * 1024.0 * 1024.0 - 1,
        1024.0 * 1024.0 * 1024.0,
        1024.0 * 1024.0 * 1024.0 + 1,
        1024.0 * 1024.0 * 1024.0 * 13,

        1024.0 * 1024.0 * 1024.0 *1024.0 - 1,
        1024.0 * 1024.0 * 1024.0 *1024.0,
        1024.0 * 1024.0 * 1024.0 *1024.0 + 1,
        1024.0 * 1024.0 * 1024.0 *1024.0 * 14,
	};

    for(i = 0; i < sizeof(sample_bytes)/sizeof(sample_bytes[0]); ++i) {
        printf("[%.2f] -> [%s]\n", sample_bytes[i], human_readable_bytes(sample_bytes[i], 10, 1, buf, sizeof(buf)));
    }

	/* The test prints the following:
	[0.00] -> [0]
	[1023.00] -> [1023]
	[1024.00] -> [1.0K]
	[1025.00] -> [1.0K]
	[11264.00] -> [11K]
	[1048575.00] -> [1024K]
	[1048576.00] -> [1.0M]
	[1048577.00] -> [1.0M]
	[12582912.00] -> [12M]
	[1073741823.00] -> [1024M]
	[1073741824.00] -> [1.0G]
	[1073741825.00] -> [1.0G]
	[13958643712.00] -> [13G]
	[1099511627775.00] -> [1024G]
	[1099511627776.00] -> [1.0T]
	[1099511627777.00] -> [1.0T]
	[15393162788864.00] -> [14T]
	*/

	

    return 0;
}