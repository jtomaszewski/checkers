#include "main.h"

Game* g;
GameHandler* gh;

int main(int argc, char **argv) {
	g = new Game;
	gh = new GameHandler;

	std::cout << "Konczymy grę...";

	return 0;
}
