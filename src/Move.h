/*
 * Move.h
 *
 *  Created on: 10-06-2013
 *      Author: slimak
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "../config.h"

class Square;

class Move {
public:
	unsigned int type;
	Square *from, *to;
	Move(Square *from, Square *to, int type);
	bool canMove();
	bool canKill();
	bool operator==(const Move move);
};
typedef list<Move> Moves;

#endif /* MOVE_H_ */
