void SaveDataHex(char *szFile, void *data, int len)
{
	FILE* fp = fopen(szFile, "ab");
	if (!fp)
	{
		return;
	}
	
	fwrite(data, len, 1, fp);
	fclose(fp);
}