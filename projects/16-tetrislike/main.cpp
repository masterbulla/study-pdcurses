#pragma comment(lib , "pdcurses.lib")

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <curses.h>

#define SCREEN_W 10
#define SCREEN_H 20
#define FIELD_W 10
#define FIELD_H 20

#define BLOCK_TYPE_NUM 7
#define BLOCK_W 4
#define BLOCK_H 4

static char field[FIELD_H][FIELD_W] = {0};
static char block[BLOCK_TYPE_NUM][BLOCK_H][BLOCK_W] = {
	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{0, 2, 2, 0},
		{0, 2, 2, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{0, 3, 3, 0},
		{3, 3, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{0, 4, 4, 0},
		{0, 0, 4, 4},
		{0, 0, 0, 0},
	},
	{
		{0, 5, 0, 0},
		{0, 5, 5, 5},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 6, 0},
		{6, 6, 6, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{0, 7, 0, 0},
		{7, 7, 7, 0},
		{0, 0, 0, 0},
	},
};

WINDOW* playWindow;

int main() {
	initscr();
	if (has_colors() == FALSE || start_color() == ERR) {
		endwin();
		return -1;
	}
    resize_term(SCREEN_H, SCREEN_W);

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);

	WINDOW* playWindow = newwin(LINES, COLS, 0, 0);
	wbkgd(playWindow, COLOR_PAIR(1));
	wmove(playWindow, 0, 0);
	touchwin(playWindow);

	char current[BLOCK_H][BLOCK_W] = {0};
	bool request_new_block = true;
	int cur_x = 0;
	int cur_y = 0;

	cbreak();
	keypad(playWindow, TRUE);
	wtimeout(playWindow, 1000);

	int key = 0;
	while ((key = wgetch(playWindow)) != 'q') {

		if (request_new_block) {
			request_new_block = false;
			int type = rand() % BLOCK_TYPE_NUM;
			for (int y=0; y<BLOCK_H; y++) {
				for (int x=0; x<BLOCK_W; x++) {
					current[y][x] = block[type][y][x];
				}
			}
		}

		// ここで移動
		if (key != ERR) {
			if (key == KEY_LEFT) {
				bool is_move = true;
				for (int y=0; y<BLOCK_H; y++) {
					for (int x=0; x<BLOCK_W; x++) {
						if (current[y][x] > 0 && field[cur_y+y][cur_x+x-1] > 0
						||  current[y][x] > 0 && cur_x+x-1 < 0) {
							is_move = false;
						}
					}
				}
				if (is_move) {
					cur_x--;
				}
			}

			if (key == KEY_RIGHT) {
				bool is_move = true;
				for (int y=0; y<BLOCK_H; y++) {
					for (int x=0; x<BLOCK_W; x++) {
						if (current[y][x] > 0 && field[cur_y+y][cur_x+x+1] > 0
						||  current[y][x] > 0 && cur_x+x+1 >= FIELD_W) {
							is_move = false;
						}
					}
				}
				if (is_move) {
					cur_x++;
				}
			}
			if (key == KEY_UP) {
				char tmp[BLOCK_H][BLOCK_W] = {0};
				memcpy(tmp, current, sizeof(tmp));
				for (int y=0; y<BLOCK_H; y++) {
					for (int x=0; x<BLOCK_W; x++) {
						current[x][BLOCK_W-1-y] = tmp[y][x];
					}
				}
			}
		}


		for (int y=0; y<BLOCK_H; y++) {
			for (int x=0; x<BLOCK_W; x++) {
				if (current[y][x] > 0 && field[cur_y+y+1][cur_x+x] > 0
				||  current[y][x] > 0 && cur_y+y+1 >= FIELD_H) {
					// 固定					
					for (int y=0; y<BLOCK_H; y++) {
						for (int x=0; x<BLOCK_W; x++) {
							if (current[y][x] > 0) {
								field[y+cur_y][x+cur_x] = current[y][x];
							}
						}
					}
					request_new_block = true;
					cur_x = 0;
					cur_y = 0;
					goto BREAK;
				}
			}
		}
BREAK:
		// 削除処理
		for (int y=0; y<FIELD_H; y++) {
			bool is_clear = true;
			for (int x=0; x<FIELD_W; x++) {
				if (field[y][x] <= 0) {
					is_clear = false;
					break;
				}
			}
			if (is_clear) {
				for (int k=y-1; k >= 0; k--) {
					for (int x=0; x<FIELD_W; x++) {
						field[k+1][x] = field[k][x];
					}
				}
			}
		}

		cur_y++;

		wclear(playWindow);
		for (int y=0; y<FIELD_H; y++) {
			for (int x=0; x<FIELD_W; x++) {
				if (field[y][x] > 0) {
					mvwaddch(playWindow, y, x, '#' | COLOR_PAIR(field[y][x]));
				}
				if (x >= cur_x && x < cur_x+BLOCK_W
				&&  y >= cur_y && y < cur_y+BLOCK_H
				&& current[y-cur_y][x-cur_x] > 0) {
					mvwaddch(playWindow, y, x, '#' | COLOR_PAIR(current[y-cur_y][x-cur_x]));
				}
			}
		}
		touchwin(playWindow);
		wnoutrefresh(playWindow);
		doupdate();
	}

    endwin();
	return 0;
}
