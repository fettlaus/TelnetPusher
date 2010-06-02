/*
 * Client.h
 *
 *  Created on: 21 Apr 2010
 *      Author: aat065
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Telnet.h"
#include "ClientList.h"
#include "config.h"
#include "Game.h"

struct client_args {
	client_entry* client;
};

void* client_run(void* args);

#endif /* CLIENT_H_ */
