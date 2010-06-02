/*
 * config.h
 *
 *  Created on: Apr 18, 2010
 *      Author: Arne Wischer
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define PORT 5000
#define MAXPORT 5500

#define NUMPLAYER 10 //int
#define STARTCHAR 's' //char
#define EXITCHAR 'e'
#define STOPCHAR ' '

#define RANDOM_LOWER 3 //sec
#define RANDOM_UPPER 10 //sec
#define GAME_TIMEOUT 7 //sec

#define SELECT_TIMEOUT_US 50000
#define BUF_SIZE 5
#define NAMELENGTH 15

#define WELCOMEMSG "Willkommen beim Tastendruecken. Bitte Namen eingeben!"
#define ANNOUNCEMSG "Neuer Spieler:"

#define DEBUG

#endif /* CONFIG_H_ */
