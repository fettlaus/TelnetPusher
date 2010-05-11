/*
 * Controller.c
 *
 *  Created on: Apr 18, 2010
 *      Author: Arne Wischer
 */
#include "Controller.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "ClientList.h"
#include "Client.h"
#include "Game.h"

#include "config.h"

int main(){
	int sock,err,realport,clientsock;
    struct sockaddr_in address;
    client_entry *newclient;
    client_list spielerliste;
    pthread_t game;
    sem_t gamewait;
    sem_init(&gamewait,0,0);

    struct game_args game_arguments;

    clientlist_init(&spielerliste);
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
    	perror("socket() fehlgeschlagen");
        return 1;
    }
    realport = PORT;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(realport);
    address.sin_family = AF_INET;


    err = bind(sock, (struct sockaddr*)&address, sizeof(address));
    while(err == -1 && realport <= MAXPORT){
    	realport += 1;
    	err = bind(sock, (struct sockaddr*)&address, sizeof(address));
    }
    if (err == -1)
    {
	   perror("bind() fehlgeschlagen");
       return 2;
    }
    err = listen(sock, 3);
    if (err == -1)
    {
	   perror("listen() fehlgeschlagen");
	   return 3;
    }

    game_arguments.game_wait = &gamewait;
    game_arguments.spielerliste = &spielerliste;


    pthread_create(&game, NULL, game_run, &game_arguments);

    for(;;){
    	clientsock = accept(sock,NULL,0);
    	if(clientsock == -1){
    		perror("accept() fehlgeschlagen");
    	}else{
    		if(spielerliste.count >= NUMPLAYER){
    			newclient = clientlist_add(&spielerliste,clientsock,&gamewait);
				pthread_create(&(newclient->thread), NULL, client_run, &newclient);
    		}else{
				write(clientsock,"Too many connections",20);
				close (clientsock);
			}
    	}
    }


		return 0;
}

void send_all(client_list* spielerliste, char* string,int length){
	client_entry* m;
	for (m = spielerliste->head; m; m = m->next){
		write(m->socket, string, length);
	}
}
