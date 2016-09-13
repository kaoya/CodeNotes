/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2016-8-30
*
* 描述: 用__attribute__((deprecated))管理过时的代码（函数、变量、类型）。
*
*       在开发一些库的时候，API的接口可能会过时，为了提醒开发者这个函数已经过时，
*       只要函数被使用，在编译是都会产生警告，警告信息中包含过时接口的名称及代码中的引用位置。
*
*       __attribute__可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。
*       __attribute__语法格式为：__attribute__ ((attribute))
*       需要注意的是： 使用__attribute__的时候，只能函数的声明处使用__attribute__，
*
*
* 例子：在编译时会出现类似警告：

# gcc attribute_deprecated.c  -o  test
attribute_deprecated.c: In function ‘main’:
attribute_deprecated.c:57: warning: ‘variable_old’ is deprecated (declared at attribute_deprecated.c:44)
attribute_deprecated.c:59: warning: ‘function_old’ is deprecated (declared at attribute_deprecated.c:49)
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#ifdef __GNUC__
#    define GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#    define GCC_VERSION_AT_LEAST(x,y) 0
#endif

#if GCC_VERSION_AT_LEAST(3,1)
#    define attribute_deprecated __attribute__((deprecated))
#elif defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#else
#    define attribute_deprecated
#endif


/* Variable Attribute */
attribute_deprecated int  variable_old = 0;

/* Function Attribute */
attribute_deprecated void function_old(void);

void function_old(void)
{
    printf("old function.\n");
    return;
}

int main(void)
{
    variable_old++;

    function_old();
    
    return EXIT_SUCCESS;
}
