/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2013-1-24
*
* 描述: 打印64位整形(在windows和linux下是不同的)
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
**函数：test_printf_int64
**功能：测试打印64位整形
**参数：none
**返回：none
**作者：KaoYa, 2013-01-23
**备注：
    1). windows和linux对64位整形的定义不同，调用printf打印也不一样
    ---------------------------------------
             | 数据类型    | printf格式化
    ---------------------------------------
    windows  | __int64     | %I64d
    ---------------------------------------
    linux    | long long   | %lld
    ---------------------------------------
    2). 本函数在windows和linux下执行，产生两种截然不同的结果：
    ◆windows输出：
    llVal=222222222, lVal=1111111, nVal=10
    llVal=222222222, lVal=0, nVal=1111111
    ◆linux输出：
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



