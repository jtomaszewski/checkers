/*
 * GameHandler.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef GAMEHANDLER_H_
#define GAMEHANDLER_H_

class GameHandler;
#include "Game.h"
#include "GameView.h"

class GameHandler {
public:
	Game *game;
	GameView *game_view;
	ALLEGRO_THREAD* thread_allegro;

	GameHandler();
	virtual ~GameHandler();

	/**
	 * glowny wątek, który trwa podczas całej aplikacji - przyjmuje eventy z allegro oraz gdy trzeba, renderuje na nowo widok
	 * @param thread
	 * @param pointer
	 */
	static void* createAllegroThread(ALLEGRO_THREAD* thread, void* pointer);

	/**
	 * odpowiada za akcję przy kliknieciu myszka
	 * @param ev
	 * @return
	 */
	bool handleMouse(ALLEGRO_EVENT *ev);

	/**
	 * odpowiada za akcję przy przycisku na klawiaturze
	 * @param ev
	 * @return
	 */
	bool handleKeyboard(ALLEGRO_EVENT *ev);

	/**
	 * kliknięcie na dany kwadracik; być może powoduje zaznaczenie innego pionka.
	 * @param square
	 * @return
	 */
	bool selectSquare(Square *square);

	/**
	 * dokonanie wyboru w menu gry
	 * @param menu_selection
	 */
	void selectMenu(int menu_selection);
};

#endif /* GAMEHANDLER_H_ */
