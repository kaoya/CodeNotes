/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2016-10-17
*
* 描述: 读取shell命令的输出内容
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
