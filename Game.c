/*
 * Game.c
 *
 *  Created on: Apr 18, 2010
 *      Author: Arne Wischer
 */
#include <semaphore.h>
#include "ClientList.h"
#include "Controller.h"
#include "Game.h"
#include "config.h"
//#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

void* game_run(void* args){
	srand((unsigned int)time(NULL));
	struct game_args arg;
	arg = *(struct game_args*) args;

	client_list* spielerliste = arg.spielerliste;
	sem_t* gamewait = arg.spielerliste->game_wait;
	fd_set fds;
	char* startmsg = "Game started. Please be ready to hit the Spacebar!";
	char* pushmsg = "PUSH SPACEBAR!";
	sem_wait(gamewait);
	int random_time = RANDOM_LOWER + (rand() % (RANDOM_UPPER-RANDOM_LOWER+1));

	client_entry* m;
	for (m = spielerliste->head; m; m = m->next){
		if(m->playable){
			m->ingame = 1;
			send(m->socket,startmsg,sizeof(startmsg),0);
		}
	}
	sleep(random_time);

	for (m = spielerliste->head; m; m = m->next){
		if(m->ingame){
			gettimeofday(&(m->starttime),NULL);
			send(m->socket,pushmsg,sizeof(pushmsg),0);
			fds
		}
	}
	//Wait for everyone to push
	sleep(GAME_TIMEOUT);
	//remove timeouts
	for (m = spielerliste->head; m; m = m->next){
		if(m->ingame){
			if(m->finishtime == 0);
		}
	}

	//Clean-UP

	//mark players as ingame
	//generate time
	//send each player("time up")
	//set starttime in playerlist
	//sleep(until finished)
	//echo ergebnisse
	return 0;
}

void sendAll(){

}
