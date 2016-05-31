#include <stdio.h>
#include "board.h"
#include "ai.h"

//https://en.wikipedia.org/wiki/Negamax#Negamax_with_alpha_beta_pruning
int negamax(Game *game, int alpha, int beta, int depth, int *best) {
	int j; //current column
	int cut = 0; //did we get a CUT at some point?
	int best_score = DEFEAT; //best score we've seen so far
	int one_decision = 0; //have we ever taken a real decision?
	if (!depth)
		return CUT; //the search space is often way too large
	for (j=0; j<game->cols; j++) {
		if (can_play(game, j)) {
			play(game, j); {
				int v;
				if (victory(game, j)) //this has to be done here
					v = VICTORY; //since the last move is unknown...
				else {
					int trash; //we don't care about the next move
					v = -negamax(game, -beta, -alpha, depth-1, &trash);
				}
				if (-v == CUT) //check the original return value
					cut = 1;
				else {
					v /= 2; //so, longer paths are less interesting
					one_decision = 1;
					//update best* variables
					if (best_score < v) {
						best_score = v;
						*best = j;
					}
					alpha = MAX(alpha, v);
				}
			} undo(game, j);
			if (alpha >= beta)
				break; //prune
		}
	}
	return (!one_decision && cut) ? CUT : best_score;
}
