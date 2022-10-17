#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct myvar{
    pthread_mutex_t *mutex;
    int *value;
} var_t;
void *routine (void *args)
{
    var_t *snap;
    snap = (var_t *)args;
    pthread_mutex_lock(snap->mutex);
   for(int i = 0; i<1000000; i++)
        *(snap->value) +=1;
    printf("%d\n", pthread_self());
   pthread_mutex_unlock(snap->mutex);
   //return (void *)snap;
}
int main()
{
    int *res;
    int total = 0;
    int j;
    var_t *snap=malloc(sizeof(var_t));
    //char tab[9] = "it s me "; 
    snap->value = malloc(sizeof(int));
    snap->mutex = malloc(sizeof(pthread_mutex_t));
    pthread_t t[8];
    int i;
   pthread_mutex_init(snap->mutex, NULL);
    for(i=0 ; i < 8; i++)
    {

           pthread_create(t + i, NULL, &routine, snap);
         printf("*****%d\n",j );
    }
    for(i = 0; i < 8; i++)
    {
        pthread_join(t[i], NULL);
    }
    //system("leaks a.out");
    pthread_mutex_destroy(snap->mutex);
    printf("%d", *(snap->value));
}
