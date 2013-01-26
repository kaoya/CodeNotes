/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2013-1-24
*
* 描述: 递归扫描出指定目录下的所有文件
*
*********************************************************************/
 
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
 
 
// 一定要有chdir的动作，否者有问题，可能跟lstat用的是非完整路径名有关
void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
 
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %sn", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 || 
                strcmp("..",entry->d_name) == 0)
                continue;
            printf("%*s%s/n",depth,"",entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+4);
        }
        else printf("%*s%sn",depth,"",entry->d_name);
    }
    chdir("..");
    closedir(dp);
}
 
/*  Now we move onto the main function.  */
 
int main()
{
    printf("Directory scan of /home:n");
    printdir("/home",0);
    printf("done.n");
 
    exit(0);
}