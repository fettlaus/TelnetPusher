/*
 * ClientList.h
 *
 *  Created on: Apr 19, 2010
 *      Author: Arne Wischer
 */

#ifndef CLIENTLIST_H_
#define CLIENTLIST_H_
#include <pthread.h>
#include <semaphore.h>

typedef struct client_entry{
	struct client_entry* next;
	int socket;
	pthread_t thread;
	sem_t *sem;
	sem_t* game_wait;
	unsigned playable: 1; //ready to play
	unsigned ingame: 1; // now playing
	unsigned exited: 1; //player quit, to be deleted
	char *name;
	unsigned int starttime;
	unsigned int timed;
} client_entry;

typedef struct client_list{
	struct client_entry* head;
	int count;
} client_list;

void clientlist_init(client_list*);
client_entry* clientlist_add(client_list*,int,sem_t*);
int clientlist_remove(client_list*, int);
int clientlist_convert_fd();
//char* clientlist_get_name(int *socket);

#endif /* CLIENTLIST_H_ */
