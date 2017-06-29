/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2017-06-29
*
* 描述: 演示usage的使用方法
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

static void usage(const char *program_name)
{
    fprintf(stderr, "usage: %s OPERATION entry1 [entry2]\n"
            "API example program to show how to manipulate resources "
            "accessed through AVIOContext.\n"
            "OPERATIONS:\n"
            "list      list content of the directory\n"
            "move      rename content in directory\n"
            "del       delete content in directory\n",
            program_name);
}

int main(int argc, char *argv[])
{
    const char *op = NULL;

    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }
    
    op = argv[1];
    
    /* ... */
    
    return 0;
}