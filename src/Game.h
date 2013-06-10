/*
 * Game.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "Display.h"
#include "Player.h"

class Game {
public:
	Board *board;
	Display *display;
	Player *player1, *player2, *current_player;
	Square *selected_square = NULL;

    Game();
    virtual ~Game();
	void assignPlayers();
	void selectSquare(Square *square);
	bool canMove(Move *move);
	bool move(Move *move);
	void removePiece(Piece *piece);
	void changeTurn();
};

#endif /* GAME_H_ */
