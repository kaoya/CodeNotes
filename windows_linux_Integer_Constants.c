#include "stdio.h"

/*
 int �� C ���ԵĻ����������ͣ������������Ǵ���һ�����ݵ�����C ���Ի��ṩ���ĸ��������� int �Ĺؼ�
 �֣�short��long��signed���Լ� unsigned���������ĸ��ؼ��֣�C ���Ա�׼�����������������ͣ�
      1) short int���ɼ�дΪ short������ int һ����Ҳ���з�������
      2) long int����д��long�����з�������
      3) long long int����д��long long����C99 ��׼��ӵ����ͣ��з�������
      4) unsigned int����д��unsigned�����޷������������ܱ�ʾ����
      5) unsigned long int����д��unsigned long�����޷������������ܱ�ʾ����
      6) unsigned short int����д��unsigned short�����޷������������ܱ�ʾ����
      7) unsigned long long int����д��unsigned long long����C99 ��ӵ����ͣ��޷�������
      8) ����û�б��� unsigned ����������Ĭ�϶����з���������
*/


/*
========================================================================================
��׺                                       ����
========================================================================================
u �� U                                     unsigned
l �� L                                     long
ll �� LL                                   long long (������ı�������֧�� C99 ��׼���ǾͲ���ʹ�� long long �� unsigned long long)
lu��LU��Lu��lU��ul��uL��Ul �� UL           unsigned long
llu��LLU��LLu��llU��ull��ULL��uLL��Ull     unsigned long long
========================================================================================
*/

int main(int argc, char* argv[])
{
	// ���γ���
	int dec = 123;      // ʮ����
	int oct = 0123;     // �˽���
	int hex = 0x123;    // ʮ������

	// ���κ�׺
	unsigned int uVal = 123u;    // �޷��ź�׺: u��U
	long lVal = 123l;            // �����κ�׺: l��L
	__int64 llVal = 123i64;      // 64-bit��׺: i64


	printf("sizeof(1U)=%d, sizeof(1L)=%d, sizeof(1i64)=%d.\r\n", sizeof(1U), sizeof(1L), sizeof(1i64));


	return 0;

}