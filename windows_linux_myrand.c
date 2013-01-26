/*********************************************************************
*
* ����: KaoYa
*
* ����: 2013-1-24
*
* ����: ����[m, n)�������Ȼ��
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*****************************************************
**����: myrand
**����: ����[m, n)�������Ȼ��
**��ע:
    1). rand��������0��RAND_MAX���������
    2). ��:
    [0, 10) ----- myrand(0, 10)
    [0, 10] ----- myrand(0, 11)  ����[0, 11)
    [5, 13) ----- myrand(5, 13)
    [5, 13] ----- myrand(5, 14)  ����[5, 14)
    3). ע��: �����srand()��ʼ���������������Ҫ��ÿ��
    ���г���rand()���ǲ���һģһ������������磺
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

	// [0, 10] ���� [0, 11)
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