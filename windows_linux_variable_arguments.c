/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2019-6-17
*
* 描述: 可变参数及可变参数宏的使用
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
可变参数宏，可以有两种方式实现，一种是标准C的__VA_ARGS__，另一种是GCC的args...

一、标准C的__VA_ARGS__

#define DBGLOG(format, ...)        printf(format, __VA_ARGS__)              // 在GCC和MS中都可以用，但在GCC中如果省略参数会编译失败

其中，...表示参数可变，__VA_ARGS__在预处理中为实际的参数集所替换。

二、GCC的args...

#define DBGLOG(format, args...)    printf(format, args)                     // 仅在GCC下可用，在MS中编译会出错

其用法和上面的基本一致，只是参数符号有变化。


有一点需要注意，上述的宏定义不能省略可变参数，如果省略了，在标准C中会编译出错。这里有必要提到
"##"连接符号的用法。"##"的作用是对token进行连接，在上例中，format、__VA_ARGS__、args即是token，
如果token为空，那么不进行连接，所以允许省略可变参数，对上述宏定义进行改造：

#define DBGLOG(format, ...)        printf(format, ##__VA_ARGS__)            // 在GCC和MS中都可以用，省略参数也可以用，强烈推荐这种写法
#define DBGLOG(format, args...)    printf(format, ##args)                   // 只能自GCC下使用，在MS中编译会出错

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