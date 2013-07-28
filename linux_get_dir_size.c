/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2013-07-28
*
* 描述: linux下获取文件夹大小的方法：有两种方法。一种是通过readdir递归
*       获取每个文件大小计算总和。另一种是ftw函数来计算。后者代码简单但
*       会用到全局变量(需要注意线程安全性)。
*
*       特别强调：ftw函数获取的文件夹大小跟du -sb获取的一样，但却不一定
*       是“真实”的文件夹大小。涉及到“文件的洞”的概念。
*
*       如果要获取文件夹所在的磁盘的空间信息，可以用statfs函数。
*
*********************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/vfs.h>

// 方法一：readdir递归计算每个文件大小的总和
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
 

// 方法二：使用ftw函数计算
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


// 方法三：获取文件夹所在磁盘空间信息
/*
struct statfs
{
   long    f_type;     // 文件系统类型
   long    f_bsize;    // 经过优化的传输块大小
   long    f_blocks;   // 文件系统数据块总数
   long    f_bfree;    // 可用块数
   long    f_bavail;   // 非超级用户可获取的块数
   long    f_files;    // 文件结点总数
   long    f_ffree;    // 可用文件结点数
   fsid_t  f_fsid;     // 文件系统标识
   long    f_namelen;  // 文件名的最大长度
};

  statfs结构中可用空间块数有两种f_bfree和 f_bavail，前者是硬盘所有剩余空间，后
者为非root用户剩余空间，ext3文件系统给root用户分有5%的独享空间，所以这里是不
同的地方。这里要强调的是每块的大小一般是4K（×这句话错误，不一定都是4k，正确做法
是:总大小= sfs.f_blocks×f_bsize，即块数×每块的大小，单位是bytes，也就是要/1024/1024/1024才是GB单位，
另外要注意的问题是sfs.f_blocks×f_bsize数据过大溢出，可以sfs.f_blocks/1024×f_bsize/1024=MB单位）。因此，要实现与df结果一致的就得在
获得块数上乘以4，这样已用、可用、总块数就可以实现。如果还要实现百分比一致，
那么要注意的是，df命令获得是整数百分比，没有小数，这里使用的进一法，而不是四
舍五入法。所以在程序里直接+1取整。
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
