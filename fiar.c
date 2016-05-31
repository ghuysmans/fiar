#include <stdio.h>
#include <string.h>
#include "board.h"
#include "ai.h"

#define ROWS 6
#define COLS 7

int main(int argc, char *argv[]) {
	Game *game = create_game(ROWS, COLS);
	if (argc==3 && !strcmp(argv[1], "display")) {
		char *p = argv[2];
		char *err;
		while (*p) {
			int col = *p - '0';
			if (col>=0 && col<COLS) {
				if (can_play(game, col)) {
					play(game, col);
					if (victory(game, col))
						printf("victory!\n");
				}
				else {
					err = "illegal move";
					goto err_handler;
				}
			}
			else {
				int i;
				err = "unknown move syntax";
err_handler:
				fprintf(stderr, "error: %s.\n%s\n", err, argv[2]);
				for (i=0; i<p-argv[2]; i++)
					fprintf(stderr, " ");
				fprintf(stderr, "^\n");
				return 2;
			}
			p++;
		}
		print_board(game);
	}
	else if ((argc==2 || argc==3) && !strcmp(argv[1], "play")) {
		int j;
		if (argc==3 && !strcmp(argv[2], "red"))
			goto red;
		while (1) {
			print_board(game);
			do {
				printf("Your move: ");
				if (scanf("%d", &j) != 1) {
					printf("\n");
					goto out;
				}
			} while (!can_play(game, j));
			play(game, j);
			if (victory(game, j)) {
				printf("You've won!\n");
				break;
			}
			else {
				int ret = negamax(game, DEFEAT, VICTORY, 12, &j);
red:
				if (ret == CUT)
					printf("I've got no idea what to do...\n"
						"I'm gonna try %d.\n", j);
				else
					printf("I'll play %d (score %d)\n", j, ret);
				play(game, j);
				if (victory(game, j)) {
					printf("You've lost!\n");
					break;
				}
			}
		}
		print_board(game);
	}
	else {
		fprintf(stderr, "usage:\t%s display moves\n", argv[0]);
		fprintf(stderr, "\t%s play [yellow|red]\n", argv[0]);
		fprintf(stderr, "try:\t%s display 01221\n", argv[0]);
		fprintf(stderr, "\t%s play\n", argv[0]);
		return 1;
	}
out:
	destroy_game(game);
	return 0;
}
