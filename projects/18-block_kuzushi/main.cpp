#pragma comment(lib , "pdcurses.lib")

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <curses.h>

#define FPS 60

#define SCREEN_W	36
#define SCREEN_H	14

#define LEVEL_MAX 4
static int level = 0;
static const int DelayTable[LEVEL_MAX] = {10, 8, 6, 4};
static int delay = 0;
static bool gameover = false;

namespace bk {

	#define PANEL_Y SCREEN_H-1
	#define PANEL_MOVE_H 3

	static char field[SCREEN_H][SCREEN_W];
	static int ball_x;
	static int ball_y;
	static int vx = 1;
	static int vy = 1;

	static int panel_x = 10;
	static int panel_y = PANEL_Y;
	static int panel_w = 6;
	static int panel_h = 1;

	void initField() {
		for (int y=0; y<SCREEN_H; y++) {
			for (int x=0; x<SCREEN_W; x++) {
				if (x == 0 || x == SCREEN_W-1
				||  y == 0) {
					field[y][x] = 8;
				}
			}
		}
	}

	bool isIntersectField(int x, int y) {
		return field[y][x] != 0;
	}

	bool isIntersectPanel(int x, int y) {
		if (x >= bk::panel_x && x < bk::panel_x+bk::panel_w
		&&  y >= bk::panel_y && y < bk::panel_y+bk::panel_h) {
			return true;
		}
		return false;
	}

	void moveBall() {
		if (isIntersectField(ball_x+vx, ball_y)
		||  isIntersectPanel(ball_x+vx, ball_y)) {
			vx *= -1;
		}
		if (isIntersectField(ball_x, ball_y+vy)
		||	isIntersectPanel(ball_x, ball_y+vy)) {
			vy *= -1;
		}
		ball_x += vx;
		ball_y += vy;
	}

	bool isGameover() {
		return ball_y >= SCREEN_H;
	}

}// namespace bk

bool init() {
	initscr();
	if (has_colors() == FALSE || start_color() == ERR) {
		endwin();
		return false;
	}
	return true;
}

void setup() {
	resize_term(SCREEN_H, SCREEN_W);

	init_pair(1, COLOR_RED, COLOR_WHITE);		// ボール
	init_pair(2, COLOR_BLUE, COLOR_WHITE);		// パネル
	init_pair(3, COLOR_YELLOW, COLOR_WHITE);
	init_pair(4, COLOR_GREEN, COLOR_WHITE);
	init_pair(5, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(6, COLOR_CYAN, COLOR_WHITE);
	init_pair(7, COLOR_BLACK, COLOR_YELLOW);	// パネル移動領域
	init_pair(8, COLOR_CYAN, COLOR_BLACK);		// 壁

	curs_set(0);				// カーソルを表示しない
	noecho();					// 入力待ちのカーソルを表示しない
	cbreak();					// 入力時、エンターを待たない
	keypad(stdscr, TRUE);		// キーパッド有効(KEY_LEFTなど)
	wtimeout(stdscr, 0);		// キー入力の待ち時間
	bkgd(COLOR_PAIR(1));		// 背景色
	refresh();

	srand((unsigned int)time(NULL));
	bk::initField();
	bk::ball_x = 3;
	bk::ball_y = 3;
}

void update(int key) {
	switch (key) {
		case KEY_LEFT:
			bk::panel_x--;
			break;
		case KEY_RIGHT:
			bk::panel_x++;
			break;
		case KEY_UP:
			if (bk::panel_y > SCREEN_H-1-PANEL_MOVE_H)
			bk::panel_y--;
			break;
		case KEY_DOWN:
			if (bk::panel_y < SCREEN_H-1) {
				bk::panel_y++;
			}
			break;
	}
	gameover = bk::isGameover();

	if (delay <= 0) {
		delay = DelayTable[level];
		bk::moveBall();
	}
	else {
		delay--;
	}
	
}

void draw() {
	clear();
	for (int y=0; y<SCREEN_H; y++) {
		for (int x=0; x<SCREEN_W; x++) {

			// パネル移動領域
			if (y >= SCREEN_H-1-PANEL_MOVE_H) {
				mvaddch(y, x, '.' | COLOR_PAIR(6));
			}

			if (bk::field[y][x] > 0) {
				mvaddch(y, x, '#' | COLOR_PAIR(bk::field[y][x]));
			}

			if (bk::ball_x == x && bk::ball_y == y) {
				mvaddch(y, x, '@' | COLOR_PAIR(1));
			}
			if (x >= bk::panel_x && x < bk::panel_x+bk::panel_w
			&&  y >= bk::panel_y && y < bk::panel_y+bk::panel_h) {
				mvaddch(y, x, 'H' | COLOR_PAIR(2));
			}
		}
	}
	//mvprintw(0, 0, "x:%d/y:%d", cur_x, cur_y);
	touchwin(stdscr);
	wnoutrefresh(stdscr);
	doupdate();
}

void term() {
	endwin();
}

int main() {
	if (!init()) {
		return -1;
	}
	setup();

	clock_t time;
	clock_t pre_time = 0;

	int key = 0;
	while (!gameover) {
		time = clock();

		if ((double)(time - pre_time) >= CLOCKS_PER_SEC/FPS) {
			update(getch());
			draw();
			pre_time = time;
		}
	}

	mvaddstr(0, 0, "GAME OVER");
	refresh();

	while (1);

	term();
	return 0;
}
