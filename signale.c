#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
char* itoa(int value, char* result, int base);
void handler(int sig,siginfo_t *info,void *ucontext)
{
    int i = 0;
    int ptr;
    char *resulte = malloc(100);
    if (sig == SIGTSTP)
    {
        ptr = info->si_value.sival_int;
        write(1, itoa(ptr,resulte, 10), 1);

    }
}
char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
int main()
{

    int sig = SIGTSTP;
    char *result = malloc(1000);
    struct sigaction sa;
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    write(1, itoa(getpid(), result, 10), 10);
    int pid = fork();
   if (pid != 0)
   {
    write (1, "main process", 13);
    write (1, itoa(getpid(),result,10), 5);
   }
   if (pid == 0) 
   {

    write(1, "this is the child squad", 17);
    write(1, itoa(getpid(), result,10), 5);
   }
   sigaction(sig, &sa, NULL);
    while (1)
    {
        pause();
    }
}