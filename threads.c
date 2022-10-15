#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/times.h>
#include <string.h>
#include <stdlib.h>

int count;
int i;
int tab[6];
char message[5][50] = {":hello", ":are you there ", ":call me if you see the message", ":it s been along time since we talk"};

typedef struct message{
    void *message;
    struct message *next;
}   message_t;
typedef struct email{
    int id;
    void *emailadress;
    int confirmed;
    message_t *message;
    struct email *next;
}   email_t;
typedef struct converstion{
    void *email;
    struct converstion *next;
}   converstion_t;
pthread_mutex_t mutex;
email_t *new_m;
converstion_t *conver ;
void *handler();

void send_message(int sender, int id_reciever, email_t *buff);

char	*strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		size;
	int		index;

	index = 0;
	if (!s1 || !s2)
		return (NULL);
	size = strlen(s1) + strlen(s2);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (s1[index])
	{
		str[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2[index])
	{
		str[strlen(s1) + index] = s2[index];
		index++;
	}
	str[size] = '\0';
	return (str);
}
void send_message(int sender, int id_reciever, email_t *buff)
{
    char sende[2];
    sende[1] = '\0';
    while (buff->id != id_reciever)
        buff = buff->next;
    int message_index = rand() % 4;
    if (buff->id == id_reciever)
    {
        sprintf(sende, "%d",sender);
        buff->message->message = strjoin(sende, message[message_index]);
        buff->message = buff->message->next;
        buff->message->next = NULL;
    }
    else
    {
        printf("warning wrong destination");
    }
}
void *handler()
{
    new_m = malloc(sizeof(email_t));
    conver = malloc(sizeof(converstion_t));
    char bu[2];
    bu[1] = '\0';
    pthread_mutex_lock(&mutex);
    new_m->id = count;
    tab[i] = count;
    i++;
    sprintf(bu,"%d", count);
    printf("%s", bu);
    new_m->emailadress = strjoin(bu, "_id@thread42.me");
    count++;
    conver->email = new_m;
    conver = conver->next;
    conver->next = NULL;
    srand ( time(NULL) );
    int randomIndex = rand() % i;
    int id = tab[randomIndex];
    if (count - 1)
        send_message(count - 1,id, new_m);
    pthread_mutex_unlock(&mutex);
}
int main()
{
    int line;
    struct tms res;
    pthread_t t[4];
   pthread_mutex_init(&mutex, NULL);
   pthread_create(t + i, NULL, &handler, NULL);
    pthread_join(t[i], NULL);
    pthread_mutex_destroy(&mutex);
    printf("%d\n", count);
}