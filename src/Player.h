/*
 * Player.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "../config.h"

class Player {
public:
	Player();
	virtual ~Player();

	PLAYERS id;
};

#include "HumanPlayer.h"
#include "ComputerPlayer.h"

#endif /* PLAYER_H_ */
