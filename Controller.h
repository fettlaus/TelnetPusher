/*
 * Controller.h
 *
 *  Created on: Apr 18, 2010
 *      Author: Arne Wischer
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#include "ClientList.h"
#include "Controller.h"
#include "Client.h"
#include "Game.h"

#include "config.h"
int main();
void send_all(client_list* spielerliste, char* string, int length);

#endif /* CONTROLLER_H_ */
