/*
 * ClientList.c
 *
 *  Created on: Apr 19, 2010
 *      Author: Arne Wischer
 */
#include "ClientList.h"

#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

void clientlist_init(client_list *list){
	list->count = 0;
	list->head = NULL;
}

client_entry* clientlist_add(client_list *list, int socket){
	client_entry * new;
	new = malloc(sizeof(client_entry));
	if(!new)
		perror("malloc() fuer Client fehlgeschlagen");
	new->socket = socket;
	new->next = list->head;
	new->ingame = 0;
	new->exited = 0;
	new->playable = 0;
	new->clist = list;
	list->head = new;
	list->count++;
	return new;
}

int clientlist_remove(client_list *list, int socket){
	client_entry *count, *prev;

	if(list->count <= 0)
		return 1;

	for(count = list->head;count;count = count->next){
		if(count->socket == socket)
			break;
		prev = count;
	}

	return 0;

}

int clientlist_convert_fd();
