/*
 * config.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "stdio.h"
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;
#define ALL(x) (x).begin(),(x).end()
#define FOREACH(i,x) for( typeof((x).begin()) i=(x).begin(); (i)!=(x).end(); ++(i) )
#define FOREACHD(i,x) for( typeof((x).rbegin()) i=(x).rbegin(); (i)!=(x).rend(); ++(i) )
#define FOR(i,a,b) for( typeof(a) i=(a);(i)<(b);++(i))
#define FORD(i,a,b) for( typeof(a) i=(a);(i)>=(b);--(i))
#define REP(i,b) for( typeof(b) i=0;(i)<(b);++(i))
#define REPD(i,b) for( typeof(b) i=(b);(i)>=0;--(i))

#define IMAGES_PATH "images/"

#define BOARD_COLS 8 // number of squares
#define BOARD_SQUARES_SUM (BOARD_COLS*BOARD_COLS) // sum of all squares on board
#define SQUARE_WIDTH 40 // px
#define BOARD_OFFSET 0
#define BOARD_OFFSET_X BOARD_OFFSET
#define BOARD_OFFSET_Y BOARD_OFFSET
#define BOARD_WIDTH (SQUARE_WIDTH*BOARD_COLS) // px

#define COLOR_SQUARE1 al_map_rgb(0, 60, 20)
#define COLOR_SQUARE2 al_map_rgb(0, 120, 60)
#define COLOR_SQUARE(x,y) (SQUARE_ODD(x, y) ? COLOR_SQUARE1 : COLOR_SQUARE2)
#define COLOR_SQUARE_SELECTED al_map_rgb(200,60,60)
#define COLOR_SQUARE_POSSIBLE al_map_rgb(150,150,60)

enum PIECE_TYPE {NOTHING, PAWN, QUEEN};
const string PIECE_TYPE_NAME[] = {"nothing", "pawn", "queen"};
enum PLAYER_ID {PLAYER_TOP = 1, PLAYER_BOTTOM};

enum EVENT_TYPES {EVENT_NONE, EVENT_SQUARE_SELECT};
struct EventResponse {
	EVENT_TYPES type = EVENT_NONE;
	int i;
	EventResponse() {};
	EventResponse(EVENT_TYPES type, const int i = NULL): type(type), i(i) {}
};

// global variables
class Game;
extern Game* g;
class GameHandler;
extern GameHandler* gh;
class Pawn;
typedef Pawn Piece; // Piece to pionek ogólnie. Nie było sensu jednak robić specjalnie podklasy, jest więc nim Pawn

// useful macros
#define BETWEEN(a,x,y) ((a) >= (x) && (a) <= (y))
#define WITHIN(x,y,ax,ay,bx,by) (BETWEEN(x,ax,bx) && BETWEEN(y,ay,by))

#define SQUARE_ITOX(i) ((i) % BOARD_COLS)
#define SQUARE_ITOY(i) ((i) / BOARD_COLS)
#define CORRECTXY(x,y) (BETWEEN(x,0,BOARD_COLS-1) && BETWEEN(y,0,BOARD_COLS-1))
#define SQUARE_XYTOI(x,y) (CORRECTXY(x, y) ? ((y)*BOARD_COLS + (x)) : -1)
#define SQUARE_ODD(x,y) (((x) + (y)) % 2)
#define GET_SQUARE_X(x) (BOARD_OFFSET_X + (x) * SQUARE_WIDTH)
#define GET_SQUARE_Y(y) (BOARD_OFFSET_Y + (y) * SQUARE_WIDTH)
#define SQUARE_WITHIN(ex,ey) (((ey)-BOARD_OFFSET_Y) / SQUARE_WIDTH * BOARD_COLS) + (((ex)-BOARD_OFFSET_X) / SQUARE_WIDTH)

#define ARE_PIECES(s1,s2) (s1->piece && s2->piece)
#define IS_ENEMY(s1,s2) (ARE_PIECES(s1,s2) && s1->piece->player_id != s2->piece->player_id)

#endif /* CONFIG_H_ */
