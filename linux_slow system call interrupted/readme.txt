《linux系统编程》中第10章 介绍了linux的三种定时器：

1、简单的闹钟 - alarm
2、间歇定时器 - setitimer
3、高级定时器 - timer_create

使用alarm会产生SIGALRM信号，从而影响慢系统调用函数（如msgrcv等），慢系统调用会被中断，返回失败（errno设置为EINTR），使用timer_create就没有这个问题。一个进程只能使用一个alarm，timer_create也不会有这个限制。