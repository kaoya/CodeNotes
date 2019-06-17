/*********************************************************************
*
* ����: KaoYa
*
* ����: 2019-6-17
*
* ����: �ɱ�������ɱ�������ʹ��
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
�ɱ�����꣬���������ַ�ʽʵ�֣�һ���Ǳ�׼C��__VA_ARGS__����һ����GCC��args...

һ����׼C��__VA_ARGS__

#define DBGLOG(format, ...)        printf(format, __VA_ARGS__)              // ��GCC��MS�ж������ã�����GCC�����ʡ�Բ��������ʧ��

���У�...��ʾ�����ɱ䣬__VA_ARGS__��Ԥ������Ϊʵ�ʵĲ��������滻��

����GCC��args...

#define DBGLOG(format, args...)    printf(format, args)                     // ����GCC�¿��ã���MS�б�������

���÷�������Ļ���һ�£�ֻ�ǲ��������б仯��


��һ����Ҫע�⣬�����ĺ궨�岻��ʡ�Կɱ���������ʡ���ˣ��ڱ�׼C�л������������б�Ҫ�ᵽ
"##"���ӷ��ŵ��÷���"##"�������Ƕ�token�������ӣ��������У�format��__VA_ARGS__��args����token��
���tokenΪ�գ���ô���������ӣ���������ʡ�Կɱ�������������궨����и��죺

#define DBGLOG(format, ...)        printf(format, ##__VA_ARGS__)            // ��GCC��MS�ж������ã�ʡ�Բ���Ҳ�����ã�ǿ���Ƽ�����д��
#define DBGLOG(format, args...)    printf(format, ##args)                   // ֻ����GCC��ʹ�ã���MS�б�������

*/

/*
#if defined _MSC_VER

#define DBGLOG1(format, ...)        printf(format, __VA_ARGS__)
#define DBGLOG2(format, ...)        printf(format, ##__VA_ARGS__)

#elif defined __GNUC__

#define DBGLOG1(format, args...)    printf(format, args)
#define DBGLOG2(format, args...)    printf(format,## args)

#endif
*/

#define DBGLOG1(format, ...)        printf(format, __VA_ARGS__)
#define DBGLOG2(format, ...)        printf(format, ##__VA_ARGS__)

void deblog(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    return;
}

int main(int argc, char *argv[])
{
    int i = 0;
    
    deblog("deblog\n");
    deblog("deblog %d\n", i++);

    DBGLOG1("DBGLOG1\n");
    DBGLOG1("DBGLOG1 %d\n", i++);

    DBGLOG2("DBGLOG2\n");
    DBGLOG2("DBGLOG2 %d\n", i++);

    return 0;
}