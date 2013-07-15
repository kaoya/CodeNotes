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

