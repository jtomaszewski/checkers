#include "main.h"

Game* g = NULL;
GameHandler* gh;

int main(int argc, char **argv) {
	g = new Game;
	gh = new GameHandler;

	printf("Konczymy grę...");

	return 0;
}
