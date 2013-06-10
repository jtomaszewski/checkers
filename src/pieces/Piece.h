/*
 * Piece.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef PIECE_H_
#define PIECE_H_

class Piece;

#include "../Square.h"
#include "../Player.h"

class Piece {
public:
	Square *square;
	PLAYERS player_id = PLAYER_NONE;
	PIECE_TYPES type;

	virtual ~Piece();
	virtual Moves getPossibleMoves(Square** board);
};

#endif /* PIECE_H_ */
