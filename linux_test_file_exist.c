/*********************************************************************
*
* ����: KaoYa
*
* ����: 2013-6-21
*
* ����: linux���ж��ļ���Ŀ¼�Ƿ���ڵķ���
*
*********************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


/************************************************************************
**������PrtLog
**���ܣ�linuxʱ���ʽ���Լ��䳤������ʵ��
**��������
**���أ�none
**���ߣ�KaoYa, 2013-1-24
**��ע��
    1). asctime(), ctime(), gmtime() and localtime() return a pointer to 
    static data and hence are not thread-safe, Thread-safe versions asctime_r(), 
    ctime_r(), gmtime_r() and localtime_r().
************************************************************************/
void PrtLog(const char *format, ...)
{
    char buf[1024];
    char szTime[30];
    time_t t;
    struct tm tmp;
    
    va_list ap;
    va_start(ap, format);
    vsprintf(buf, format, ap);
    va_end(ap);
    
    buf[sizeof(buf)-1] = 0x00;
    
    t = time(NULL);
    localtime_r(&t, &tmp);
    strftime(szTime, sizeof(szTime), "%G-%m-%d %H:%M:%S", &tmp);
    
    printf("[%s] %s\n", szTime, buf);
}

/************************************************************************
**������IsFileExist
**���ܣ��ж�ָ���ļ�����Ŀ¼�Ƿ����
**������
        pathname[in] - �ļ���Ŀ¼
**���أ�
        true - ����, false - ������
**���ߣ�KaoYa, 2013-6-21
**��ע��
    1). access�����𲻳������ļ�����Ŀ¼
************************************************************************/
int IsFileExist(const char *pathname)
{
	return (0 == access(pathname, F_OK));
}

/************************************************************************
**������IsPathExist
**���ܣ��ж�ָ��Ŀ¼�Ƿ����
**������
        pathname[in] - �ļ���Ŀ¼
**���أ�
        true - ����, false - ������
**���ߣ�KaoYa, 2013-6-21
**��ע��
    1). opendirֻ�������ж�Ŀ¼�Ƿ���ڣ��������ж��ļ��Ƿ����(�ļ�����
    ����NULL)
************************************************************************/
int IsPathExist(const char *pathname)
{
	return (NULL != opendir(pathname));
}

/************************************************************************
**������IsFileExist3
**���ܣ��ж�ָ���ļ�����Ŀ¼�Ƿ����
**������
        pathname[in] - �ļ���Ŀ¼
**���أ�
        true - ����, false - ������
**���ߣ�KaoYa, 2013-6-21
**��ע��
    1). stat�ܵõ������ļ���Ŀ¼�ĸ�����Ϣ����������������ļ�����Ŀ¼
************************************************************************/
int IsFileExist3(const char *pathname)
{
    struct stat sb;
     
    if (stat(pathname, &sb) == -1)
    {
        perror("stat");
        return 0;
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
 
    return 1;
}

int main(int argc, char *argv[])
{
	int i;
	char szFile[][200] = 
	{
		"/etc/inittab",
		"/etc/inittaB",
		"/etc/",
		"/etC/"
	};
	
	// �ļ��Ƿ����
	for(i=0; i<sizeof(szFile)/sizeof(*szFile); i++)
	{
		printf("\n");
		
		if(IsFileExist(szFile[i]))
		{
			PrtLog("IsFileExist [%s] exist!", szFile[i]);
		}
		else
		{
			PrtLog("IsFileExist [%s] is no exist!", szFile[i]);
		}
		
		if(IsPathExist(szFile[i]))
		{
			PrtLog("IsPathExist [%s] exist!", szFile[i]);
		}
		else
		{
			PrtLog("IsPathExist [%s] is no exist!", szFile[i]);
		}
		
		IsFileExist3(szFile[i]);
	}

    return 0;
}
