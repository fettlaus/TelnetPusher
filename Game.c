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
#include <stdio.h>

int get_sender(fd_set *fds);
client_entry* get_player(client_list* clist,int socket);
int fill_set(fd_set *fds, client_list *clist);
void block_playing(client_list* clist);
client_entry* wait_next_timeout(client_list* clist, char* buffer, int size, int timeout);
client_entry* wait_next(client_list* clist, char* buffer, int size);
void block_start(client_list* clist);
void block_random(client_list* clist, int waitfor);
void print_results(client_list* clist);

void* game_run(void* args){
	srand((unsigned int)time(NULL));
	struct game_args arg;
	arg = *(struct game_args*) args;

	client_entry* player;
	client_list* playerlist = arg.spielerliste;
	char* startmsg = "Game started. Please be ready to hit the Spacebar!";
	char* pushmsg = "PUSH SPACEBAR!";
#ifdef DEBUG
    printf("Game Thread started\n");
#endif

    for(;;){
#ifdef DEBUG
    	printf("Blocking and wait for game to start\n");
#endif
		block_start(playerlist);
		int random_time = RANDOM_LOWER + (rand() % (RANDOM_UPPER-RANDOM_LOWER+1));
#ifdef DEBUG
		printf("Started with %d seconds waiting time\n",random_time);
#endif

		//set everyone playable to ingame
		for (player = playerlist->head; player; player = player->next){
			if(player->playable){
				player->ingame = 1;
				send(player->socket,startmsg,sizeof(startmsg),0);
			}
		}
#ifdef DEBUG
		printf("Blocking now for %d seconds\n",random_time);
#endif
		block_random(playerlist,random_time);
		//set starting time and send message
		for (player = playerlist->head; player; player = player->next){
			if(player->ingame && !player->exited){
				gettimeofday(&(player->starttime),NULL);
				send(player->socket,pushmsg,sizeof(pushmsg),0);
			}
		}
#ifdef DEBUG
		printf("It's time to push the button, you have %d seconds\n",GAME_TIMEOUT);
#endif
		block_playing(playerlist);
		//Wait for everyone to push
		for (player = playerlist->head; player; player = player->next){
			if(player->ingame && player->finishtime.tv_sec == 0 && player->finishtime.tv_usec == 0){

					player->exited = 1;
			}
		}
#ifdef DEBUG
		printf("printing results\n");
#endif
		print_results(playerlist);

		//Clean-UP

    }
}

void print_results(client_list* clist){
	client_entry* player;
	char buffer[16];
	for (player = clist->head; player; player = player->next){
		snprintf(buffer,sizeof(buffer),"Test");
		send_all(clist,buffer,sizeof(buffer),0);
	}
}

void send_all(client_list* clist,char* msg, int size, int sender){
	client_entry* player;
	for (player = clist->head; player; player = player->next){
		if(player->socket == sender)
			continue;
		if(player->socket == STDIN_FILENO)
			write(STDOUT_FILENO,msg,size);
		else
			send(player->socket,msg,size,MSG_NOSIGNAL);
	}
}

void block_playing(client_list* clist){
	char buffer;
	struct timeval targettime,curtime;
	client_entry* player;
	gettimeofday(&curtime,NULL);
	targettime.tv_sec = curtime.tv_sec + GAME_TIMEOUT;

	while( curtime.tv_sec < targettime.tv_sec){
		gettimeofday(&curtime,NULL);
		player = wait_next_timeout(clist,&buffer,sizeof(buffer),SELECT_TIMEOUT_US);
		if(buffer == EXITCHAR){
			player->exited = 1;
		}else if(buffer == STOPCHAR && !player->finishtime.tv_sec && !player->finishtime.tv_sec){
			player->finishtime.tv_sec = curtime.tv_sec - player->starttime.tv_sec;
			player->finishtime.tv_usec = curtime.tv_usec - player->starttime.tv_usec;
		}

	}


}
void block_start(client_list* clist){
	char buffer;
	int running = 0;
	client_entry* player;
	while(!running){
		player = wait_next_timeout(clist,&buffer,sizeof(buffer),500);
		if(buffer == EXITCHAR)
			player->exited = 1;
		else if(buffer == STARTCHAR && player->playable && !player->exited)
			running = 1;
	}

}

void block_random(client_list* clist, int waitfor){
	char buffer;
	struct timeval targettime,curtime;
	client_entry* player;
	gettimeofday(&curtime,NULL);
	targettime.tv_sec = curtime.tv_sec + waitfor;

	while( curtime.tv_sec < targettime.tv_sec){
		gettimeofday(&curtime,NULL);
		player = wait_next_timeout(clist,&buffer,sizeof(buffer),SELECT_TIMEOUT_US);
		if(buffer == EXITCHAR){
			player->exited = 1;
		}

	}
}

client_entry* wait_next(client_list* clist, char* buffer,int size){
	return wait_next_timeout(clist, buffer, size, 0);
}

client_entry* wait_next_timeout(client_list* clist,char* buffer, int size, int timeout){
	fd_set fds;
	int max,sender;
	struct timeval tout;
	tout.tv_sec = 0;
	tout.tv_usec = timeout;
	max = fill_set(&fds,clist);
	if(timeout)
		select(max+1,&fds,NULL,NULL,&tout);
	else
		select(max+1,&fds,NULL,NULL,NULL);
	sender = get_sender(&fds);
	read(sender, &buffer, size);
	return get_player(clist,sender);
}

int get_sender(fd_set *fds)
{
    int i = 0;
    while(!FD_ISSET(i, fds))
        i++;
    return i;
}

client_entry* get_player(client_list* clist,int socket){
	client_entry* m;
	for (m = clist->head; m; m = m->next){
		if(m->socket == socket)
			return m;
	}
	return 0;
}

int fill_set(fd_set *fds, client_list *clist)
{
    int max = 0;
    struct client_entry *item;

    for (item = clist->head; item; item = item->next)
    {
        if (item->socket > max)
            max = item->socket;
        FD_SET(item->socket, fds);
    }
    return max;
}
