/*  We start by defining a RECORD structure
    and then create NRECORDS versions each recording their number.
    These are appended to the file records.dat.  */


/*
    注意：JFFS2文件系统不支持mmap + MAP_SHEARED，而此前我接触的linux嵌入式车台终端的Flash
就是JFFS2的文件系统。

    linux系统调用mmap在映射一个文件时只有使用MAP_SHEARED参数才会将映射内存的修改写回文件，
但是jffs2文件系统却不支持有写回的映射，即MAP_SHARED参数不能使用，只能使用MAP_PRIVATE
进行映射，实践得出，后google得知是jffs2的一大特性，具体原因尚待进一步确认
*/


/*
    UNIX网络编程第二卷进程间通信对mmap函数进行了说明。该函数主要用途有三个：
    1、将一个普通文件映射到内存中，通常在需要对文件进行频繁读写时使用，这样用内存读写取代I/O读写，以获得较高的性能；
    2、将特殊文件进行匿名内存映射，可以为关联进程提供共享内存空间；
    3、为无关联的进程提供共享内存空间，一般也是将一个普通文件映射到内存中。

使用特殊文件提供匿名内存映射：

适用于具有亲缘关系的进程之间。由于父子进程特殊的亲缘关系，在父进程中先调用mmap()，然后调用 fork()。那么在调用fork()之后，子进程继承父进程匿名映射后的地址空间，同样也继承mmap()返回的地址，这样，父子进程就可以通过映射区 域进行通信了。注意，这里不是一般的继承关系。一般来说，子进程单独维护从父进程继承下来的一些变量。而mmap()返回的地址，却由父子进程共同维护。 对于具有亲缘关系的进程实现共享内存最好的方式应该是采用匿名内存映射的方式。此时，不必指定具体的文件，只要设置相应的标志即可。 
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct {
    int integer;
    char string[24];
} RECORD;

#define NRECORDS (100)

int main()
{
    RECORD record, *mapped;
    int i, f;
    FILE *fp;

    fp = fopen("records.dat","w+");
    for(i=0; i<NRECORDS; i++) {
        record.integer = i;
        sprintf(record.string,"RECORD-%d",i);
        fwrite(&record,sizeof(record),1,fp);
    }
    fclose(fp);

/*  We now change the integer value of record 43 to 143
    and write this to the 43rd record's string.  */

    fp = fopen("records.dat","r+");
    fseek(fp,43*sizeof(record),SEEK_SET);
    fread(&record,sizeof(record),1,fp);

    record.integer = 143;
    sprintf(record.string,"RECORD-%d",record.integer);

    fseek(fp,43*sizeof(record),SEEK_SET);
    fwrite(&record,sizeof(record),1,fp);
    fclose(fp);

/*  We now map the records into memory
    and access the 43rd record in order to change the integer to 243
    (and update the record string), again using memory mapping.  */

    f = open("records.dat",O_RDWR);
    mapped = (RECORD *)mmap(0, NRECORDS*sizeof(record), 
                          PROT_READ|PROT_WRITE, MAP_SHARED, f, 0);
    
    // JFFS2文件系统会返回失败
    if(MAP_FAILED == mapped)
    {
        perror("mmap fail");
        goto exit;
    }

    mapped[43].integer = 243;
    sprintf(mapped[43].string,"RECORD-%d",mapped[43].integer);

    msync((void *)mapped, NRECORDS*sizeof(record), MS_ASYNC);
    
exit:
    munmap((void *)mapped, NRECORDS*sizeof(record));
    close(f);

    exit(0);
}

