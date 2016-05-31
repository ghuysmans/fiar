#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "board.h"

#define RED(x) !((x) & 1)
#define YELLOW(x) ((x) & 1)
#define EMPTY(x) !(x)
#define TO_CHAR(x) (EMPTY(x) ? '.' : (RED(x) ? 'R' : 'Y'))
#define INDEX(g,i,j) g->board[g->cols*(i)+j]

void print_board(Game * const game) {
	int i, j;
	//header
	for (j=0; j<game->cols; j++)
		printf("%c ", INDEX(game, game->rows, j)==game->rows ? '*' : '0'+j);
	printf("\n");
	//tokens
	for (i=game->rows-1; i>=0; i--) {
		for (j=0; j<game->cols; j++)
			printf("%c ", TO_CHAR(INDEX(game, i, j)));
		printf("\n");
	}
}

/**
 * Updates the board array associated to a Game.
 * @param game Game object
 * @param i row
 * @param j column
 * @param v sequence number or 0 to undo a previous move at (i,j)
 */
void update_board(const Game *game, const int i, const int j, const int v) {
	assert(i>=0 && i<game->rows);
	assert(j>=0 && j<game->cols);
	if (v) {
		assert(EMPTY(INDEX(game, i, j)));
		INDEX(game, i, j) = v;
		INDEX(game, game->rows, j)++;
	}
	else {
		assert(!EMPTY(INDEX(game, i, j)));
		assert(INDEX(game, game->rows, j) > 0);
		INDEX(game, i, j) = 0;
		INDEX(game, game->rows, j)--;
	}
}

int can_play(Game *game, const int j) {
	return INDEX(game, game->rows, j) < game->rows;
}

void play(Game *game, const int j) {
	update_board(game, INDEX(game, game->rows, j), j, ++game->played);
}

void undo(Game *game, const int j) {
	assert(game->played > 0);
	game->played--;
	update_board(game, --INDEX(game, game->rows, j), j, 0);
}

Game *create_game(const int rows, const int cols) {
	Game *game = calloc(sizeof(Game) + sizeof(TOKEN)*(rows+1)*cols, 1);
	if (game) {
		game->rows = rows;
		game->cols = cols;
		game->board = (char*)game + sizeof(Game);
	}
	return game;
}

void destroy_game(Game *game) {
	free(game);
}
