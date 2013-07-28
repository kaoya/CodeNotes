/*********************************************************************
*
* ����: KaoYa
*
* ����: 2013-07-28
*
* ����: linux�»�ȡ�ļ��д�С�ķ����������ַ�����һ����ͨ��readdir�ݹ�
*       ��ȡÿ���ļ���С�����ܺ͡���һ����ftw���������㡣���ߴ���򵥵�
*       ���õ�ȫ�ֱ���(��Ҫע���̰߳�ȫ��)��
*
*       �ر�ǿ����ftw������ȡ���ļ��д�С��du -sb��ȡ��һ������ȴ��һ��
*       �ǡ���ʵ�����ļ��д�С���漰�����ļ��Ķ����ĸ��
*
*       ���Ҫ��ȡ�ļ������ڵĴ��̵Ŀռ���Ϣ��������statfs������
*
*********************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/vfs.h>

// ����һ��readdir�ݹ����ÿ���ļ���С���ܺ�
unsigned long get_dir_size(const char *path)
{  
    DIR *d;
    struct dirent *de;
    struct stat buf;
    int total_size = 0;
    char fullpath[1024], currfile[1024];
    
    strcpy(fullpath, path);
    
    d = opendir(path);
    if(d == NULL)
    {
        perror("prsize");
        return 0;
    }
    
    while( NULL != (de = readdir(d)) )
    {
    	  if(strcmp(".", de->d_name) == 0 || strcmp("..", de->d_name) == 0)
        {
            continue;
        }
        
        sprintf(currfile, "%s/%s", fullpath, de->d_name);
        stat(currfile, &buf);
        if(S_ISDIR(buf.st_mode))
        {
            total_size += get_dir_size(currfile);
        }
        else
        {
            total_size += buf.st_size;
        }
    }
    
    closedir(d);
    
    return total_size;
}
 

// ��������ʹ��ftw��������
static unsigned int g_total_size = 0;
int sum(const char *fpath, const struct stat *sb, int typeflag)
{
    g_total_size += sb->st_size;
    return 0;
}

unsigned long get_dir_size2(const char *path)
{
    unsigned long total = 0;
    
    g_total_size = 0;
    if(ftw(path, &sum, 1))
    {
        perror("ftw");
    }
    total = g_total_size;
    
    return total;
}


// ����������ȡ�ļ������ڴ��̿ռ���Ϣ
/*
struct statfs
{
   long    f_type;     // �ļ�ϵͳ����
   long    f_bsize;    // �����Ż��Ĵ�����С
   long    f_blocks;   // �ļ�ϵͳ���ݿ�����
   long    f_bfree;    // ���ÿ���
   long    f_bavail;   // �ǳ����û��ɻ�ȡ�Ŀ���
   long    f_files;    // �ļ��������
   long    f_ffree;    // �����ļ������
   fsid_t  f_fsid;     // �ļ�ϵͳ��ʶ
   long    f_namelen;  // �ļ�������󳤶�
};

  statfs�ṹ�п��ÿռ����������f_bfree�� f_bavail��ǰ����Ӳ������ʣ��ռ䣬��
��Ϊ��root�û�ʣ��ռ䣬ext3�ļ�ϵͳ��root�û�����5%�Ķ���ռ䣬���������ǲ�
ͬ�ĵط�������Ҫǿ������ÿ��Ĵ�Сһ����4K������仰���󣬲�һ������4k����ȷ����
��:�ܴ�С= sfs.f_blocks��f_bsize����������ÿ��Ĵ�С����λ��bytes��Ҳ����Ҫ/1024/1024/1024����GB��λ��
����Ҫע���������sfs.f_blocks��f_bsize���ݹ������������sfs.f_blocks/1024��f_bsize/1024=MB��λ������ˣ�Ҫʵ����df���һ�µľ͵���
��ÿ����ϳ���4���������á����á��ܿ����Ϳ���ʵ�֡������Ҫʵ�ְٷֱ�һ�£�
��ôҪע����ǣ�df�������������ٷֱȣ�û��С��������ʹ�õĽ�һ������������
�����뷨�������ڳ�����ֱ��+1ȡ����
*/

void get_dir_size3(const char *path)
{
    struct statfs sfs;
    long f_1blocksize = 1024;

    int i = statfs(path, &sfs);
    int percent = (sfs.f_blocks - sfs.f_bfree ) * 100 / (sfs.f_blocks - sfs.f_bfree + sfs.f_bavail) + 1;

    printf("sfs.f_bsize = %ld\n", sfs.f_bsize);
    
    printf("\n/dev/xxxxx            %ld    %ld  %ld   %d%%\n",
        sfs.f_bsize/f_1blocksize * sfs. f_blocks, sfs.f_bsize/f_1blocksize * (sfs.f_blocks - sfs.f_bfree), 
        sfs.f_bsize/f_1blocksize * sfs.f_bavail, percent);

    char szCmd[256];
    sprintf(szCmd, "df %s", path);
    system(szCmd);
}
 
int main(int argc, char *argv[])
{
    char szDir[256];
    unsigned long lFileSize;
    
    strcpy(szDir, "/work");
    
    char szCmd[256];
    sprintf(szCmd, "du -sb %s", szDir);
    system(szCmd);
    
    printf("get_dir_size  %s: %ld\n", szDir, get_dir_size(szDir));
    printf("get_dir_size2 %s: %ld\n", szDir, get_dir_size2(szDir));
    
    strcpy(szDir, "/etc/");
    get_dir_size3(szDir);
    
 
    exit(EXIT_SUCCESS);
}
