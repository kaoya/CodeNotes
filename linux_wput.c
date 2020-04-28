/*********************************************************************
*
* 作者: KaoYa
*
* 日期: 2020-4-28
*
* 描述: linux使用wput上传文件
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>

static void test_wput(char *path)
{
    char cmd[250];

    /*
    * -t number, --tries=number
              Set number of retries to number. Specify -1 for infinite retrying, which is default, too.
    * --waitretry=SECONDS
              wait SECONDS between retries of an upload，这参数有的版本不支持
    * --basename=path
              This option causes Wput to snip path from all input-files when they are connected to the URL.
              wput /usr/share/doc.tgz ftp://host/ would create ftp://host//usr/share/doc.tgz, whereas specifying /usr/share/ as basename
              will result in ftp://host/doc.tgz being created.
    */
    memset(cmd, 0x00, sizeof(cmd));
    snprintf(cmd, sizeof(cmd) - 1,
        "wput -t 1 --waitretry=3 --basename='%s/' '%s' ftp://username:password@125.90.10.120:5000/test/",
        dirname(path),
        path);
    system(cmd);
}

int main(int argc, char *argv[])
{
    test_wput("/usr/share/doc.tgz");

    exit(EXIT_SUCCESS);
}
