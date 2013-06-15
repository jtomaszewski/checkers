/*
 * Pawn.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef PAWNPIECE_H_
#define PAWNPIECE_H_

#include "../Square.h"
#include "../Player.h"

// próbuje dodać kwadrat do tablicy board, jeśli tylko miesci się w współrzędnych.
#define INSERT_SQUARE(v, x, y, board) (CORRECTXY(x, y) ? v.push_back( board[SQUARE_XYTOI(x, y)] ), true : false)

class Pawn {
public:
	Square *square;
	PLAYER_ID player_id;
	PIECE_TYPE type;

	Pawn();
	virtual ~Pawn();

	/**
	 * czy ten pionek ma w tym momencie możliwość bicia?
	 * @return
	 */
	bool canKill(Square **board);

	/**
	 * wszystkie ruchy, jakie ma w tej chwili do dyspozycji
	 * @param board
	 * @return
	 */
	virtual Moves getPossibleMoves(Square **board);

	/**
	 * wszystkie ruchy-kroki, czyli tylko przesunięcie w bok bez bicia pionków
	 * @param board
	 * @return
	 */
	virtual Moves getPossibleStepMoves(Square **board);

	/**
	 * wszystkie ruchy-bicia, czyli bijące 1+ wrogich pionków
	 * @param board
	 * @return
	 */
	virtual Moves getPossibleKillMoves(Square **board);
	virtual Moves getPossibleKillMoves(Square **board, Move *move, Square *came_from);
};

#endif /* PAWNPIECE_H_ */
