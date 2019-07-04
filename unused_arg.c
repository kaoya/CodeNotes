/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2019-07-04
*
* 描述: 有些参数，定义了没用到，编译会发出警告，又不能删除，怎么办?
*
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define UNUSED_ARG(a) (void)a

int main(int argc, char ** argv)
{
    UNUSED_ARG(argc);
    UNUSED_ARG(argv);

    return 0;
}