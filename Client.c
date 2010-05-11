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
	//make handshaking
	//Grosse Schleife:
	//pollend recv()
	//wenn button == e dann exit
	//wenn button == s dann
	//Mutex
	//TODO: Hier nacharbeiten
	//	wenn button == s
	//	wenn s dann Game_Semaphore++
	//Endmutex
	//recv()
	//wenn button == e dann exit
	//wenn button == leertaste
}
