/*********************************************************************
*
* ����: KaoYa
*
* ����: 2016-10-19
*
* ����: ��ӡ���в㼶�ṹ��������������־��Ϣ
*
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define MAX_LEVEL   10          // ���㼶
#define INDENTATION 3           // ÿ�������Ŀո���

/************************************************************************
**������printf_level_fmt
**���ܣ���ӡ���в㼶�ṹ��������������־��Ϣ
**������
        [in] level  - �㼶��ȡֵ��Χ[0, MAX_LEVEL], 0Ϊ���㣬�������޵İ�MAX_LEVEL����
        [in] fmt    - ��ʽ���ַ���
**���أ�
**��ע��
        ���磺
        level 0 - 0
        level 0 - 1
        level 0 - 2
           |- level 1 - 0
           |- level 1 - 1
           |- level 1 - 2
              |- level 2 - 0
              |- level 2 - 1
              |- level 2 - 2
                 |- level 3 - 0
                 |- level 3 - 1
                 |- level 3 - 2
************************************************************************/
void printf_level_fmt(unsigned int level, const char *fmt, ...)
{
    va_list ap;
    unsigned int i = 0;
    char indentation[MAX_LEVEL * INDENTATION + 10] = {0};

    level = min(level, MAX_LEVEL);
    for (i=0; i<level * INDENTATION; i++) {
        indentation[i] = ' ';
    };
    indentation[i] = '\0';
    if (level > 0) {
        strcat(indentation, "|- ");
    }

    printf("%s", indentation);

    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    return ;
}

int main(int argc, char *argv[])
{
    int i, j;

    printf_level_fmt(0, "level 0\n");
    printf_level_fmt(0, "level 0 = %d\n", 5);

    for (i=0; i<10; i++) {
        for (j=0; j<3; j++) {
            printf_level_fmt(i, "level %d - %d\n", i, j);
        }
    }

    return 0;
}