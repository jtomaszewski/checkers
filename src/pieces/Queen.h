/*
 * Queen.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef QUEENPIECE_H_
#define QUEENPIECE_H_

#include "Pawn.h"

/**
 * @see Pawn
 */
class Queen: public Pawn {
public:
	Queen();
	Queen(Pawn* const);

	Moves getPossibleStepMoves(Square **board);
	Moves getPossibleKillMoves(Square **board);
	Moves getPossibleKillMoves(Square **board, Move *move, pii jumped_from_offset);
};

#endif /* QUEENPIECE_H_ */
