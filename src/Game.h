/*
 * Game.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef GAME_H_
#define GAME_H_

#include "Board.h"

class Game {
public:
	Board *board;
	Player player1, player2, *current_player = NULL, *player_win = NULL;
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
	void assignPlayers(PLAYER_TYPE p1, PLAYER_TYPE p2);

	/**
	 * zaznacz dany kwadrat, jako ten, którym będziemy się poruszać
	 * @param square
	 */
	void selectSquare(Square *square);

	/**
	 * wszystkie możliwe ruchy, jakie ma do dyspozycji w tej chwili dany gracz
	 * @param player_id
	 * @return
	 */
	Moves getAllPossibleMoves(PLAYER_ID player);

	/**
	 * czy ten ruch jest obecnie możliwy?
	 * @param move
	 * @return prawdziwy odpowiednik tego ruchu. NULL, jesli nie ma
	 */
	Move* canMove(Move *move);

	/**
	 * wykonanie ruchu.
	 * ruch się nie wykona, jeśli pole docelowe nie jest oznaczone jako possible
	 * @param move
	 * @param emulate symuluje wykonanie ruchu
	 * @return true, jeśli ruch się wykonał
	 */
	bool executeMove(Move *move, bool emulate);

	/**
	 * zwraca listę wszystkich pionków danego gracza, które są obecnie na planszy
	 * @param player_id
	 * @return
	 */
	list<Pawn*> getPlayerPieces(PLAYER_ID player_id);

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
	 * @return pierwszy z brzegu ruch z biciem
	 */
	Move* hasKillingMove(PLAYER_ID player_id);

	/**
	 * probuje zamienic pionka w damkę, jeśli tylko ma taką możliwość
	 * @return true if successed
	 */
	bool tryQueenTransform(Pawn *pawn);

	/**
	 * dla obecnej tury wykonuje ruch automatycznie.
	 * @return false, jeśli nie ma żadnego ruchu.
	 */
	bool executeComputerMove();
};

#endif /* GAME_H_ */
