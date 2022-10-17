#include <pthread.h>
#include <stdio.h>

void *routine1()
{
    printf("hello from my deeps");
}
int main()
{
    pthread_t   t1;

    pthread_create(&t1, NULL, &routine1,NULL);
    pthread_join(pthread_self(), NULL);
}