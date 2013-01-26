/*********************************************************************
*
* ����: KaoYa
*
* ����: 2013-1-24
*
* ����: ��ӡ64λ����(��windows��linux���ǲ�ͬ��)
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>


#ifndef _M_IX86
typedef long long  _INT64;
#else
typedef __int64    _INT64;
#endif

/************************************************************************
**������test_printf_int64
**���ܣ����Դ�ӡ64λ����
**������none
**���أ�none
**���ߣ�KaoYa, 2013-01-23
**��ע��
    1). windows��linux��64λ���εĶ��岻ͬ������printf��ӡҲ��һ��
    ---------------------------------------
             | ��������    | printf��ʽ��
    ---------------------------------------
    windows  | __int64     | %I64d
    ---------------------------------------
    linux    | long long   | %lld
    ---------------------------------------
    2). ��������windows��linux��ִ�У��������ֽ�Ȼ��ͬ�Ľ����
    ��windows�����
    llVal=222222222, lVal=1111111, nVal=10
    llVal=222222222, lVal=0, nVal=1111111
    ��linux�����
    llVal=                                                       222222222, lVal=0, nVal=1111111
    llVal=222222222, lVal=1111111, nVal=10
************************************************************************/
void test_printf_int64(void)
{
    int nVal = 10;
    long lVal = 1111111;
    _INT64 llVal = 222222222;

    printf("llVal=%I64d, lVal=%ld, nVal=%d\n", llVal, lVal, nVal);
    printf("llVal=%lld, lVal=%ld, nVal=%d\n", llVal, lVal, nVal);
}


int main(int argc, char *argv[])
{
    test_printf_int64();

    return 0;
}



