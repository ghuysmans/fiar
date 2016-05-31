#ifndef __BOARD_H
#define __BOARD_H


#define TOKEN char
typedef struct {
	int played; //< moves count
	int rows;
	int cols;
	//the last row contains counters: legal move for j in O(1)!
	//each token is a sequence number so the whole history is stored
	TOKEN *board;
} Game;


/**
 * Displays the board.
 * @param game Game object
 */
void print_board(Game * const game);

/**
 * Checks whether a given move can be played.
 * @param game Game object
 * @param j column
 */
int can_play(Game * const game, const int j);

/**
 * Plays a legal move.
 * @param game Game object
 * @param j column
 */
void play(Game *game, const int j);

/**
 * Undoes a move.
 * @param game Game object
 * @param i row
 * @param j column
 */
void undo(Game *game, const int j);

/**
 * Creates a Game object.
 * @param rows grid rows
 * @param cols grid columns
 */
Game *create_game(const int rows, const int cols);

/**
 * Destroys a Game object.
 */
void destroy_game(Game *game);


#endif //__BOARD_H
