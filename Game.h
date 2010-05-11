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
	sem_t* game_wait;
	char* startchar;
};

void* game_run(void* args);

#endif /* GAME_H_ */
