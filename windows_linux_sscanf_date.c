/*********************************************************************
*
* ����: KaoYa
*
* ����: 2013-1-24
*
* ����: ����ʱ���ַ���"20121224192432"�Ľ������ɴ���ǿ��sscanf��������֪
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