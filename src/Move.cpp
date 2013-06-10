/*
 * Move.cpp
 *
 *  Created on: 10-06-2013
 *      Author: slimak
 */

#include "Move.h"

Move::Move(Square *from, Square *to, int type = 0): from(from), to(to) {
	this->type = type ? type : MOVE | KILL;
}

bool Move::canMove() {
	return type & MOVE;
};

bool Move::canKill() {
	return type & KILL;
};

bool Move::operator==(const Move move) {
	return move.from == from && move.to == to && move.type & type;
}
