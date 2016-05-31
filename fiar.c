#include <stdio.h>
#include "board.h"

#define ROWS 6
#define COLS 7

int main(int argc, char *argv[]) {
	Game *game = create_game(ROWS, COLS);
	print_board(game);
	play(game, 0, 0);
	play(game, 0, 1);
	print_board(game);
	undo(game, 0, 1);
	print_board(game);
	destroy_game(game);
	return 0;
}
