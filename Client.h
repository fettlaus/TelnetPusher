/*
 * Client.h
 *
 *  Created on: 21 Apr 2010
 *      Author: aat065
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <semaphore.h>
#include "ClientList.h"

struct client_args {
	client_entry* client;
	client_list* spielerliste;
};

void* client_run(void* args);

#endif /* CLIENT_H_ */
