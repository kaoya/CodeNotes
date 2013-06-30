/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2013-06-30
*
* 描述: linux删除文件和文件夹

=====================================================================
  命令     | 可删除文件？| 可删除空目录?  | 可删除非空目录？
=====================================================================
  unlink   |     √       |     ×          |    ×
  rmdir    |     ×       |     √          |    ×
  remove   |     √       |     √          |    ×
=====================================================================
* remove既能删除文件，也能删除空目录（不能删除非空目录）
* unlink只能删除文件，不能删除目录
* rmdir只能删除空目录（不能删除非空目录），不能删除文件
* 删除非空目录，没有现成的函数，可调用shell脚本命令system("rm -fr")来实现:
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// remove既能删除文件，也能删除空目录（不能删除非空目录）
// remove() deletes a name from the filesystem.  It calls unlink() for files, and rmdir() for directories.
void remove_file(void)
{
	char szDir[] = "/dir_tmp";
	char szFile[] = "/file.tmp";
  	char szCmd[200];

	// create file
	sprintf(szCmd, "touch %s", szFile);
	system(szCmd);

	// delete file
	if(0 == remove(szFile))
	{
		printf("remove() file succ: %s\n", szFile);
	}
	else
	{
		perror("remove() file fail");
	}

	// create not empty dir
	mkdir(szDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	sprintf(szCmd, "touch %s/1.tmp", szDir);
	system(szCmd);

	// delete not empty dir
	if(0 == remove(szDir))
	{
		printf("remove() not empty dir succ: %s\n", szDir);
	}
	else
	{
		perror("remove() not empty dir fail");
	}

	// create empty dir
	sprintf(szCmd, "%s/1.tmp", szDir);
	unlink(szCmd);

	// delete dir
	if(0 == remove(szDir))
	{
		printf("remove() empty dir succ: %s\n", szDir);
	}
	else
	{
		perror("remove() empty dir fail");
	}
}

// unlink只能删除文件，不能删除目录
void unlink_file(void)
{
	char szDir[] = "/dir_tmp";
	char szFile[] = "/file.tmp";
  	char szCmd[200];

	// create file
	sprintf(szCmd, "touch %s", szFile);
	system(szCmd);

	// delete file
	if(0 == unlink(szFile))
	{
		printf("unlink() file succ: %s\n", szFile);
	}
	else
	{
		perror("unlink() file fail");
	}

	// create dir
	mkdir(szDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	// delete dir
	if(0 == unlink(szDir))
	{
		printf("unlink() dir succ: %s\n", szDir);
	}
	else
	{
		perror("unlink() dir fail");
	}
}

// rmdir只能删除空目录（不能删除非空目录），不能删除文件
void rmdir_file(void)
{
	char szDir[] = "/dir_tmp";
	char szFile[] = "/file.tmp";
  	char szCmd[200];

	// create file
	sprintf(szCmd, "touch %s", szFile);
	system(szCmd);

	// delete file
	if(0 == rmdir(szFile))
	{
		printf("rmdir() file succ: %s\n", szFile);
	}
	else
	{
		perror("rmdir() file fail");
	}

	// create not empty dir
	mkdir(szDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	sprintf(szCmd, "touch %s/1.tmp", szDir);
	system(szCmd);

	// delete not empty dir
	if(0 == rmdir(szDir))
	{
		printf("rmdir() not empty dir succ: %s\n", szDir);
	}
	else
	{
		perror("rmdir() not empty dir fail");
	}

	// create empty dir
	sprintf(szCmd, "%s/1.tmp", szDir);
	unlink(szCmd);

	// delete empty dir
	if(0 == rmdir(szDir))
	{
		printf("rmdir() empty dir succ: %s\n", szDir);
	}
	else
	{
		perror("rmdir() empty dir fail");
	}
}


int main(int argc, char *argv[])
{
	remove_file();

	unlink_file();

	rmdir_file();

	exit(EXIT_SUCCESS);
}
