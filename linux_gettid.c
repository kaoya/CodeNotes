#include <sys/syscall.h>
#include <sys/types.h>


// 获取线程tid
pid_t gettid(void)
{
	return syscall(SYS_gettid);
}