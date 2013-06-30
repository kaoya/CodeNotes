#include "stdio.h"

/*
 int 是 C 语言的基本整数类型，可以满足我们处理一般数据的需求。C 语言还提供了四个可以修饰 int 的关键
 字：short、long、signed，以及 unsigned。利用这四个关键字，C 语言标准定义了以下整数类型：
      1) short int（可简写为 short），和 int 一样，也是有符号整数
      2) long int（简写：long），有符号整数
      3) long long int（简写：long long），C99 标准添加的类型，有符号整数
      4) unsigned int（简写：unsigned），无符号整数，不能表示负数
      5) unsigned long int（简写：unsigned long），无符号整数，不能表示负数
      6) unsigned short int（简写：unsigned short），无符号整数，不能表示负数
      7) unsigned long long int（简写：unsigned long long），C99 添加的类型，无符号整数
      8) 所有没有标明 unsigned 的整数类型默认都是有符号整数。
*/


/*
========================================================================================
后缀                                       类型
========================================================================================
u 或 U                                     unsigned
l 或 L                                     long
ll 或 LL                                   long long (如果您的编译器不支持 C99 标准，那就不能使用 long long 和 unsigned long long)
lu、LU、Lu、lU、ul、uL、Ul 或 UL           unsigned long
llu、LLU、LLu、llU、ull、ULL、uLL、Ull     unsigned long long
========================================================================================
*/

int main(int argc, char* argv[])
{
	// 整形常量
	int dec = 123;      // 十进制
	int oct = 0123;     // 八进制
	int hex = 0x123;    // 十六进制

	// 整形后缀
	unsigned int uVal = 123u;    // 无符号后缀: u或U
	long lVal = 123l;            // 长整形后缀: l或L
	__int64 llVal = 123i64;      // 64-bit后缀: i64


	printf("sizeof(1U)=%d, sizeof(1L)=%d, sizeof(1i64)=%d.\r\n", sizeof(1U), sizeof(1L), sizeof(1i64));


	return 0;

}