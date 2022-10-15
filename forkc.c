#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
void *routine (void *args)
{
    int *res = malloc(sizeof(int));
    //pthread_mutex_lock(&mutex);
    char *s = (char *) args;
    *res = strlen(s);
   //pthread_mutex_unlock(&mutex);
   return (void *) res;
}
int main()
{
    int *res;
    char tab[9] = "it s me "; 
    pthread_t t[4];
    int i = 0;
    pthread_mutex_init(&mutex, NULL);
    for(i ; i < 1; i++)
        pthread_create(t + i, NULL, &routine, tab + i);
    for(i = 0; i < 1; i++)
        pthread_join(t[i], (void **) &res );
    pthread_mutex_destroy(&mutex);
    printf("%d", *res);
}
