/*
 * Player.h
 *
 *  Created on: 17-06-2013
 *      Author: slimak
 */


#ifndef PLAYER_H_
#define PLAYER_H_

enum PLAYER_ID { PLAYER_TOP = 1, PLAYER_BOTTOM };
enum PLAYER_TYPE { PLAYER_HUMAN = 1, PLAYER_COMPUTER };

struct Player {
	PLAYER_ID id;
	PLAYER_TYPE type;
	const char* c_str() {
		char *str = new char[15];
		sprintf(str, id == PLAYER_TOP ? "Black" : "White");

		return str;
	}
};


#endif /* PLAYER_H_ */
