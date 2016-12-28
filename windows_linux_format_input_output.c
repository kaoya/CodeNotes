#include <stdio.h>
#include <stdlib.h>

/*
说明：负号 为 左对齐
-------------------------------------------------------------------------
        格式          参数                |  输  出  |
-------------------------------------------------------------------------
        %10s         "Hello"              |     Hello|
        %-10s        "Hello"              |Hello     |
        %*s          10,"Hello"           |     Hello|
        %*s          3,"Hello"            |Hello|
        %.*s         3,"Hello"            |Hel|
        %10d         1234                 |      1234|
        %-10d        1234                 |1234      |
        %010d        1234                 |0000001234|
        %10.4f       12.34                |   12.3400|
 -------------------------------------------------------------------------
*/
static void format_input_output(void)
{
	printf("%10s\n",    "Hello");
	printf("%-10s\n",   "Hello");
	printf("%*s\n", 10, "Hello");
	printf("%*s\n", 3,  "Hello");
	printf("%.*s\n", 3, "Hello");
	
	printf("%10d\n",  1234);
	printf("%-10d\n", 1234);
	printf("%010d\n", 1234);

	printf("%10.4f\n", 12.34);
}

int main(int argc, char *argv[])
{
	format_input_output();

	exit(EXIT_SUCCESS);
}
