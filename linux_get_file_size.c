/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2013-1-24
*
* 描述: linux下获取文件大小
*
*********************************************************************/



/*********************************************************************
* 文 件 名: linux_get_file_size.c
* 
* 创 建 人: KaoYa, 2012-10-09
*
* 文件描述: linux下可以用有两种方式获取文件大小：ftell或者stat。前者通
*           过计算文件偏移量来获取文件大小，后者通过读取文件属性来取得
*           大小
*
*********************************************************************/

// 方法一：
unsigned long get_file_size(const char *path)  
{  
    unsigned long filesize = -1;  
    FILE *fp;  
    fp = fopen(path, "r");  
    if(fp == NULL)  
        return filesize;  
    fseek(fp, 0L, SEEK_END);  
    filesize = ftell(fp);  
    fclose(fp);  
    return filesize;  
}
 
// 方法二（从man 2 stat从拷贝而来）：
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    struct stat sb;
 
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
     
    if (stat(argv[1], &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }
 
    printf("File type:                ");
 
    switch (sb.st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFIFO:
        printf("FIFO/pipe\n");
        break;
    case S_IFLNK:
        printf("symlink\n");
        break;
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown?\n");
        break;
    }
 
    printf("I-node number:          %ld\n", (long) sb.st_ino);
 
    printf("Mode:                   %lo (octal)\n",
           (unsigned long) sb.st_mode);
 
    printf("Link count:             %ld\n", (long) sb.st_nlink);
    printf("Ownership:              UID=%ld   GID=%ld\n",
           (long) sb.st_uid, (long) sb.st_gid);
 
    printf("Preferred I/O block size: %ld bytes\n",
           (long) sb.st_blksize);
    printf("File size:              %lld bytes\n",
           (long long) sb.st_size);
    printf("Blocks allocated:       %lld\n",
           (long long) sb.st_blocks);
 
    printf("Last status change:     %s", ctime(&sb.st_ctime));
    printf("Last file access:       %s", ctime(&sb.st_atime));
    printf("Last file modification: %s", ctime(&sb.st_mtime));
 
    exit(EXIT_SUCCESS);
}
