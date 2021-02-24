/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2021-2-24
*
* 描述: 按字节对齐计算大小
*
*********************************************************************/

#include <stdio.h>

#define ALIGN(x, k)     (((x)+((k)-1)) & ~((k)-1))
#define ALIGN_BYTE(x)   ALIGN((x), 8)
#define ALIGN_WORD(x)   ALIGN((x), 16)

int main(int argc, char *argv[])
{
    int x;

    for (x = 9; x >= 0; x--) {
        printf("ALIGN_BYTE(%d)=%d\n", x, ALIGN_BYTE(x));
    }

    for (x = 17; x >= 0; x--) {
        printf("ALIGN_WORD(%d)=%d\n", x, ALIGN_WORD(x));
    }

    return 0;
}