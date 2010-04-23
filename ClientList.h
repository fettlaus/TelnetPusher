/*
 * ClientList.h
 *
 *  Created on: Apr 19, 2010
 *      Author: Arne Wischer
 */

#ifndef CLIENTLIST_H_
#define CLIENTLIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

typedef struct client_entry{
	struct client_entry* next;
	int socket;
	pthread_t thread;
	sem_t *sem;
	unsigned playable: 1;
	unsigned ingame: 1;
	unsigned exited: 1;
	char *name;
	unsigned int starttime;
	unsigned int timed;
} client_entry;

typedef struct client_list{
	struct client_entry* head;
	int count;
} client_list;

void clientlist_init(client_list*);
client_entry* clientlist_add(client_list*,int);
int clientlist_remove(client_list*, int);
int clientlist_convert_fd();
//char* clientlist_get_name(int *socket);

#endif /* CLIENTLIST_H_ */
