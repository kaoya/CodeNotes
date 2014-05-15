/*********************************************************************
*
* ����: KaoYa
*
* ����: 2014-5-15
*
* ����: �ܽ���windows��linux�½ṹ����뷽ʽ�Ĳ��죺
*       1��windows xp����VC 6.0���ԣ�linux PC����gcc (Debian 4.4.5-8) 4.4.5��ARMǶ��ʽarm-hismall-linux-gcc (GCC) 3.4.3
*       2���ṹ�������Ҫ�����ַ�ʽ��#pragma pack(1)��__attribute__���ַ�ʽ�����°�1�ֽڶ���Ĳ��Խ����
*       -----------------------------------------------------------------------------------------------------
                                                     | #pragma pack(1)��ʽ      | __attribute__��ʽ
*       -----------------------------------------------------------------------------------------------------
*       windows xp (VC 6.0)                          | OK                       | ����ʧ��
*       -----------------------------------------------------------------------------------------------------
*       linux PC (gcc (Debian 4.4.5-8) 4.4.53)       | OK                       | OK
*       -----------------------------------------------------------------------------------------------------
*       lnux ARM (arm-hismall-linux-gcc (GCC) 3.4.3) | û�а�1�ֽڶ���          | OK
*       -----------------------------------------------------------------------------------------------------
*
*       3���Ӳ��Խ��������#pragma pack(1)��ʽ��linux��ͬ��gcc�汾�£�����ֳ���ͬ�Ľ���������Բ��á�����__attribute__
*       ��ʽ��windows���ֱ��벻��ȥ��Ŀǰ��û���ҵ�ͬһ�������ͬʱ����windows��linux�ķ�����
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
    windows xp (VC6.0)���:                             sizeof(no alignment) = 12, sizeof(__attribute__) = 12, sizeof(#pragma pack) = 9.

    linux PC (gcc (Debian 4.4.5-8) 4.4.5)���:          sizeof(no alignment) = 12, sizeof(__attribute__) = 9, sizeof(#pragma pack) = 9.

    ARMǶ��ʽ (arm-hismall-linux-gcc (GCC) 3.4.3)���:  sizeof(no alignment) = 12, sizeof(__attribute__) = 9, sizeof(#pragma pack) = 12.
    */


    getchar();
    
    return EXIT_SUCCESS;
}
