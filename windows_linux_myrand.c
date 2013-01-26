/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2013-1-24
*
* 描述: 产生[m, n)的随机自然数
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*****************************************************
**函数: myrand
**功能: 产生[m, n)的随机自然数
**备注:
    1). rand函数产生0到RAND_MAX的随机数；
    2). 如:
    [0, 10) ----- myrand(0, 10)
    [0, 10] ----- myrand(0, 11)  就是[0, 11)
    [5, 13) ----- myrand(5, 13)
    [5, 13] ----- myrand(5, 14)  就是[5, 14)
    3). 注意: 最好用srand()初始化随机数发生器，要不每次
    运行程序rand()都是产生一模一样的随机数，如：
    srand((unsigned int)getpid());
*****************************************************/
static int myrand(int m, int n)
{
    int nVal;
 
    if(m >= n)
    {
        return (-1);
    }
     
    nVal = m + (int)( (n-m+0.0) * (rand()/(RAND_MAX+0.0)) );
     
    return nVal;
}


int main(int argc, char *argv[])
{
	int i;
	int nVal;

	/* Seed the random-number generator with current time so that
    * the numbers will be different every time we run.
    */
	srand( (unsigned)time( NULL ) );

	// [0, 10)
	printf("\n[0, 10):\n");
	for(i=0; i<100; i++)
	{
		nVal = myrand(0, 10);
		printf("%d ", nVal);
	}

	// [0, 10] 就是 [0, 11)
	printf("\n[0, 10]:\n");
	for(i=0; i<100; i++)
	{
		nVal = myrand(0, 11);
		printf("%d ", nVal);
	}

	// [1, 10)
	printf("\n[1, 10):\n");
	for(i=0; i<100; i++)
	{
		nVal = myrand(1, 10);
		printf("%d ", nVal);
	}

	// [5, 13]
	printf("\n[5, 13]:\n");
	for(i=0; i<100; i++)
	{
		nVal = myrand(5, 14);
		printf("%d ", nVal);
	}
	
	return 0;
}