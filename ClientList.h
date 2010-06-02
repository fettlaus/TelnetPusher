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
#include "config.h"

typedef struct client_entry{
	struct client_entry* next;
	int socket;
	pthread_t thread;
	sem_t* sem;
	unsigned playable: 1; //ready to play
	unsigned ingame: 1; // now playing
	unsigned exited: 1; //player quit, to be deleted
	char name[NAMELENGTH];
	struct timeval starttime;
	struct timeval finishtime;
	struct client_list* clist;
} client_entry;

typedef struct client_list{
	struct client_entry* head;
	int count;
} client_list;

void clientlist_init(client_list*);
client_entry* clientlist_add(client_list* spielerliste,int Socket);
int clientlist_remove(client_list*, int);
int clientlist_convert_fd();
//char* clientlist_get_name(int *socket);

#endif /* CLIENTLIST_H_ */
