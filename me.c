#include <unistd.h>
#include <signal.h>
#include <stdio.h>

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
void handler(int sig)
{
    if (sig == SIGTSTP)
        write (1, "ouch", 4);
}
int main(int argc, char **argv)
{
    int pid = atoi(argv[1]);
    union sigval value;
    
    char bar[20] = "hello it me";
    value.sival_int = (int )bar;
    sigqueue(pid, SIGTSTP, value);
}