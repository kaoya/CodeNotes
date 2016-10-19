/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2016-10-19
*
* 描述: 打印具有层级结构（有缩进）的日志信息
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

#define MAX_LEVEL   10          // 最大层级
#define INDENTATION 3           // 每层缩进的空格数

/************************************************************************
**函数：printf_level_fmt
**功能：打印具有层级结构（有缩进）的日志信息
**参数：
        [in] level  - 层级，取值范围[0, MAX_LEVEL], 0为顶层，超过上限的按MAX_LEVEL处理
        [in] fmt    - 格式化字符串
**返回：
**备注：
        例如：
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