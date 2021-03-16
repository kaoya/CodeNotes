/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2021-3-16
*
* 描述: 计算数字二进制格式中1的位数，汉明重量（Hamming Weight）
*
*********************************************************************/
#include <stdio.h>

int hammingweight(int x)
{
    int n = 0;
    while (x) { n ++; x &= (x - 1); }
    return n;
}

int main(int argc, char *argv[])
{
    int i;
    int x[] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0x0ff};

    for (i = 0; i < sizeof(x)/sizeof(*x); i++) {
        printf("0x%x | hammingweight = %d\n", x[i], hammingweight(x[i]));
    }

    return 0;
}