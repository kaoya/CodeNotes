/*********************************************************************
*
* ����: KaoYa
*
* ����: 2016-10-17
*
* ����: ��ȡshell������������
*
*********************************************************************/
#include <stdio.h>


int main()
{
    char cmd[] = "date +%z";
    char out[32] = {0};
    FILE *fp = NULL;
    
    fp = popen(cmd, "r");
    fread(out, sizeof(out), 1, fp);
    pclose(fp);
    
    printf("out = %s", out);

    return 0;
}
