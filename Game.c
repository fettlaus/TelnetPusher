/*
 * Game.c
 *
 *  Created on: Apr 18, 2010
 *      Author: Arne Wischer
 */
#include <semaphore.h>
#include "ClientList.h"
#include "Game.h"
void* game_run(void* args){
	fd_set fds;

	getLock()

	//lock game_semaphore
	//mark players as ingame
	//generate time
	//send each player("time up")
	//set starttime in playerlist
	//sleep(until finished)
	//echo ergebnisse
	return 0;
}
