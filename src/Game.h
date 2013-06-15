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
	Square *selected_square = NULL; // zaznaczone obecnie pole
	bool force_selected = false; // czy gracz musi teraz ruszyc sie tym pionkiem? (czyli jest w trakcie swojej tury..)
	bool must_kill = false; // czy obecny gracz ma bicie, ktorego musi dokonac w tej turze?

	/**
	 * stworzenie gry - stworzenie widoku gry, przypisanie pionków i graczy
	 * @return
	 */
    Game();

    virtual ~Game();

    /**
     * przypisujemy graczy
     */
	void assignPlayers();

	/**
	 * zaznacz dany kwadrat, jako ten, którym będziemy się poruszać
	 * @param square
	 */
	void selectSquare(Square *square);

	/**
	 * wszystkie możliwe ruchy, jakie ma do dyspozycji w tej chwili dany gracz
	 * @param player
	 * @return
	 */
	Moves getAllPossibleMoves(PLAYER_ID player);

	/**
	 * czy ten ruch jest obecnie możliwy?
	 * @param executeMove
	 * @return prawdziwy odpowiednik tego ruchu. NULL, jesli nie ma
	 */
	Move* canMove(Move *move);

	/**
	 * wykonanie ruchu.
	 * ruch się nie wykona, jeśli pole docelowe nie jest oznaczone jako possible
	 * @param executeMove
	 * @return true, jeśli ruch się wykonał
	 */
	bool executeMove(Move *move);

	/**
	 * zmiana tury
	 */
	void changeTurn();

	/**
	 * jesli mamy zaznaczone jakies pole, wszystkie mozliwe pola ruchow docelowych oznaczamy jako mozliwe
	 */
	void markPossibleSquares();

	/**
	 * czy dany gracz ma w tej chwili możliwość bicia?
	 * @param player_id
	 * @return
	 */
	bool hasKillingMove(PLAYER_ID player_id);

	/**
	 * probuje zamienic pionka w damkę, jeśli tylko ma taką możliwość
	 * @return true if successed
	 */
	bool tryQueenTransform(Pawn *pawn);
};

#endif /* GAME_H_ */
