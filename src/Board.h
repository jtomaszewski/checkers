/*
 * Board.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef BOARD_H_
#define BOARD_H_

class Board;

#include "Square.h"

#include "pieces/Pawn.h"
#include "pieces/Queen.h"

class Board {
public:
	static PIECE_TYPE DEFAULT_SETUP[];
	Square* squares[BOARD_SQUARES_SUM];

	Board();
	virtual ~Board();
	void assignSquaresAndPieces();
	static Piece* createPiece(PIECE_TYPE type);
};

#endif /* BOARD_H_ */
