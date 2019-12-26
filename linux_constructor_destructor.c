#include <stdio.h>
#include <stdlib.h>

static __attribute__((constructor)) void before_main(int argc, char *argv[])
{
    printf("[%s] %s.\n", argv[0], __FUNCTION__);
}

static __attribute__((destructor)) void after_main(void)
{
    printf("[%s].\n", __FUNCTION__);
}

int main(int argc, char *argv[])
{
    printf("[%s] %s.\n", argv[0], __FUNCTION__);
    exit(EXIT_SUCCESS);
}
