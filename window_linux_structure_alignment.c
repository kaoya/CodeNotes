/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2014-5-15
*
* 描述: 总结在windows和linux下结构体对齐方式的差异：
*       1、windows xp下用VC 6.0测试，linux PC下用gcc (Debian 4.4.5-8) 4.4.5和ARM嵌入式arm-hismall-linux-gcc (GCC) 3.4.3
*       2、结构体对齐主要有两种方式：#pragma pack(1)和__attribute__两种方式，以下按1字节对齐的测试结果：
*       -----------------------------------------------------------------------------------------------------
                                                     | #pragma pack(1)方式      | __attribute__方式
*       -----------------------------------------------------------------------------------------------------
*       windows xp (VC 6.0)                          | OK                       | 编译失败
*       -----------------------------------------------------------------------------------------------------
*       linux PC (gcc (Debian 4.4.5-8) 4.4.53)       | OK                       | OK
*       -----------------------------------------------------------------------------------------------------
*       lnux ARM (arm-hismall-linux-gcc (GCC) 3.4.3) | 没有按1字节对齐          | OK
*       -----------------------------------------------------------------------------------------------------
*
*       3、从测试结果来看，#pragma pack(1)方式在linux不同的gcc版本下，会表现出不同的结果，兼容性不好。可是__attribute__
*       方式在windows下又编译不过去。目前还没有找到同一代码可以同时兼容windows和linux的方法。
*
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __flv_header
{
    char       signature[3];           // always "FLV"
    char       version;                // should be 1
    char       flags;
    int        offset;                 // always 9
} flv_header;

typedef struct 
#ifndef _MSC_VER
__attribute__((packed, aligned(1))) 
#endif
__flv_header2
{
    char       signature[3];           // always "FLV"
    char       version;                // should be 1
    char       flags;
    int        offset;                 // always 9
} flv_header2;

#pragma pack(1)
typedef struct __flv_header3
{
    char       signature[3];           // always "FLV"
    char       version;                // should be 1
    char       flags;
    int        offset;                 // always 9
} flv_header3;
#pragma pack()


int main(void)
{
    printf("sizeof(no alignment) = %d, sizeof(__attribute__) = %d, sizeof(#pragma pack) = %d.\n",
        sizeof(flv_header),
        sizeof(flv_header2),
        sizeof(flv_header3));

    /*
    windows xp (VC6.0)输出:                             sizeof(no alignment) = 12, sizeof(__attribute__) = 12, sizeof(#pragma pack) = 9.

    linux PC (gcc (Debian 4.4.5-8) 4.4.5)输出:          sizeof(no alignment) = 12, sizeof(__attribute__) = 9, sizeof(#pragma pack) = 9.

    ARM嵌入式 (arm-hismall-linux-gcc (GCC) 3.4.3)输出:  sizeof(no alignment) = 12, sizeof(__attribute__) = 9, sizeof(#pragma pack) = 12.
    */


    getchar();
    
    return EXIT_SUCCESS;
}
