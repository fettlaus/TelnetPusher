/*
 * Client.c
 *
 *  Created on: 21 Apr 2010
 *      Author: aat065
 */

#include "Client.h"

void* client_run(void* args){
	struct client_args arg;
	arg = *(struct client_args*) args;
	client_entry* client = arg.client;
	int socket = client->socket;
	char buf[3];
	char welcome[] = WELCOMEMSG;
	char announcemsg[sizeof(ANNOUNCEMSG)+sizeof(client->name)];

	send(socket,welcome,sizeof(welcome),MSG_NOSIGNAL);
	read(socket, &client->name, sizeof(client->name));

	sprintf(buf,"%c%c%c",IAC,WILL,ECHO);
	send(socket,buf,sizeof(buf),MSG_NOSIGNAL);
	sprintf(buf,"%c%c%c",IAC,WILL,SUPPRESSGOAHEAD);
	send(socket,buf,sizeof(buf),MSG_NOSIGNAL);

	snprintf(announcemsg,sizeof(announcemsg),"%s%s",ANNOUNCEMSG,client->name);
	send_all(client->clist,ANNOUNCEMSG,sizeof(ANNOUNCEMSG)+sizeof(client->name),socket);
	client->playable = 1;
	return 0;
}
