/*
 * Game.h
 *
 *  Created on: Apr 18, 2010
 *      Author: Arne Wischer
 */

#ifndef GAME_H_
#define GAME_H_


struct game_args {
	client_list* spielerliste;
	char startchar;
};

void* game_run(void* args);
void send_all(client_list* clist,char* msg, int size, int sender);
#endif /* GAME_H_ */
