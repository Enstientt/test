#include <unistd.h>
#include <sys/resource.h>

int main()
{
    int pid;
    int n;
    int r;
    pid  = fork();
    if (pid == 0)
        write(1, "hello from the child\n", 21);
    else
    {
        r = wait(&n);
        printf("chhh %d\n", n);
        printf("chhh %d\n", r);
    }
}