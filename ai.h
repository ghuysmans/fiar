#ifndef __AI_H
#define __AI_H


#define VICTORY 4242
#define DEFEAT -VICTORY
#define DRAW 0
#define CUT -1

/**
 * Determines the best move to play as the current player.
 * @param game Game object
 * @param alpha best max candidate
 * @param beta best min candidate
 * @param depth 0 means we have to stop
 * @param best best move
 * @return best score
 */
int negamax(Game *game, int alpha, int beta, int depth, int *best);


#endif //__AI_H
