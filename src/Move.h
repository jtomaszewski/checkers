/*
 * Move.h
 *
 *  Created on: 10-06-2013
 *      Author: slimak
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "../config.h"

class Pawn;
class Square;

class Move {
public:
	Square *from, *to;
	list<Piece*> killed_pieces;

	Move(Square *from, Square *to);
	Move(Move* const);

	/**
	 * ruchy są podobne gdy mają to samo pole zaczynajace i docelowe
	 * @param executeMove
	 * @return
	 */
	bool operator==(const Move move);

	/**
	 * czy to jest ruch-bicie?
	 * @return
	 */
	bool isKillingMove();

	/**
	 * czy to jest pojedyncze przesuniecie ?
	 * @return
	 */
	bool isSingleStep();
};
typedef list<Move*> Moves;

#endif /* MOVE_H_ */
