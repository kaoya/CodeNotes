/*  We start by defining a RECORD structure
    and then create NRECORDS versions each recording their number.
    These are appended to the file records.dat.  */


/*
    ע�⣺JFFS2�ļ�ϵͳ��֧��mmap + MAP_SHEARED������ǰ�ҽӴ���linuxǶ��ʽ��̨�ն˵�Flash
����JFFS2���ļ�ϵͳ��

    linuxϵͳ����mmap��ӳ��һ���ļ�ʱֻ��ʹ��MAP_SHEARED�����ŻὫӳ���ڴ���޸�д���ļ���
����jffs2�ļ�ϵͳȴ��֧����д�ص�ӳ�䣬��MAP_SHARED��������ʹ�ã�ֻ��ʹ��MAP_PRIVATE
����ӳ�䣬ʵ���ó�����google��֪��jffs2��һ�����ԣ�����ԭ���д���һ��ȷ��
*/


/*
    UNIX�����̵ڶ�����̼�ͨ�Ŷ�mmap����������˵�����ú�����Ҫ��;��������
    1����һ����ͨ�ļ�ӳ�䵽�ڴ��У�ͨ������Ҫ���ļ�����Ƶ����дʱʹ�ã��������ڴ��дȡ��I/O��д���Ի�ýϸߵ����ܣ�
    2���������ļ����������ڴ�ӳ�䣬����Ϊ���������ṩ�����ڴ�ռ䣻
    3��Ϊ�޹����Ľ����ṩ�����ڴ�ռ䣬һ��Ҳ�ǽ�һ����ͨ�ļ�ӳ�䵽�ڴ��С�

ʹ�������ļ��ṩ�����ڴ�ӳ�䣺

�����ھ�����Ե��ϵ�Ľ���֮�䡣���ڸ��ӽ����������Ե��ϵ���ڸ��������ȵ���mmap()��Ȼ����� fork()����ô�ڵ���fork()֮���ӽ��̼̳и���������ӳ���ĵ�ַ�ռ䣬ͬ��Ҳ�̳�mmap()���صĵ�ַ�����������ӽ��̾Ϳ���ͨ��ӳ���� �����ͨ���ˡ�ע�⣬���ﲻ��һ��ļ̳й�ϵ��һ����˵���ӽ��̵���ά���Ӹ����̼̳�������һЩ��������mmap()���صĵ�ַ��ȴ�ɸ��ӽ��̹�ͬά���� ���ھ�����Ե��ϵ�Ľ���ʵ�ֹ����ڴ���õķ�ʽӦ���ǲ��������ڴ�ӳ��ķ�ʽ����ʱ������ָ��������ļ���ֻҪ������Ӧ�ı�־���ɡ� 
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
    
    // JFFS2�ļ�ϵͳ�᷵��ʧ��
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

