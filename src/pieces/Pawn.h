/*
 * Pawn.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef PAWNPIECE_H_
#define PAWNPIECE_H_

#include "Piece.h"

class Pawn: public Piece {
public:
	Pawn();
	static bool isMovePossible(Move *move, Square** board);
	Squares getPossibleSquares(Square** board);
	Moves getPossibleMoves(Square** board);
};

#endif /* PAWNPIECE_H_ */
