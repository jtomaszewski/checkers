/*
 * Square.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef SQUARE_H_
#define SQUARE_H_

#include "../config.h"

class Square;
typedef list<Square*> Squares;

#include "Move.h"
#include "pieces/Pawn.h"

class Square {
public:
	Piece* piece = NULL;
	int x, y;
	bool selected = false, possible = false;

	Square(const int i);

	/**
	 * ustawia pionek na polu
	 * @internal obustronnie ustawia wskaznik na polu i pionku
	 * @param piece
	 */
	void setPiece(Piece* piece);
	const char* c_str();
};

#endif /* SQUARE_H_ */
