#include <sys/syscall.h>
#include <sys/types.h>


// ��ȡ�߳�tid
pid_t gettid(void)
{
	return syscall(SYS_gettid);
}