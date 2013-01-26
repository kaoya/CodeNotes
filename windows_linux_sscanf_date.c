/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2013-1-24
*
* 描述: 对于时间字符串"20121224192432"的解析，由此增强对sscanf函数的认知
*
*********************************************************************/

void sscanf_date()
{
    char szStartTm[] = "20121224191720";
    SYSTEMTIME st;
 
    memset(&st, 0x00, sizeof(st));
    sscanf(szStartTm, "%4d%2d%2d%2d%2d%2d", 
        &st.wYear, &st.wMonth, &st.wDay, 
        &st.wHour, &st.wMinute, &st.wSecond);
 
    return ;
};