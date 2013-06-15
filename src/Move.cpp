/*
 * Move.cpp
 *
 *  Created on: 10-06-2013
 *      Author: slimak
 */

#include "Move.h"

Move::Move(Square *from, Square *to): from(from), to(to) {
	killed_pieces.clear();
}

bool Move::operator==(const Move move) {
	return move.from == from && move.to == to;
}

bool Move::isKillingMove() {
	return killed_pieces.size() > 0;
}

bool Move::isSingleStep() {
	return killed_pieces.size() <= 1;
}
