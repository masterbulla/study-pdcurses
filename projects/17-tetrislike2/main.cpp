#pragma comment(lib , "pdcurses.lib")

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <curses.h>

#define FPS 30

#define FIELD_W		10
#define FIELD_H		20
#define FIELD_BEGX	1			// 実際の開始位置
#define FIELD_BEGY	4			// 実際の開始位置
#define FIELD_RW	FIELD_W +2	// 左右判定用
#define FIELD_RH	FIELD_H +5	// 新規ブロック出現場所と下判定用

#define SCREEN_W	FIELD_RW
#define SCREEN_H	FIELD_RH-FIELD_BEGY

#define BLOCK_TYPE_NUM 7
#define BLOCK_W 4
#define BLOCK_H 4

static char field[FIELD_RH][FIELD_RW] = {0};
static const char blockData[BLOCK_TYPE_NUM][BLOCK_H][BLOCK_W] = {
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

typedef char BLOCK[BLOCK_H][BLOCK_W];

BLOCK current = {0};
bool request_new_block = true;
int cur_x = FIELD_BEGX;
int cur_y = 0;
int delay = 0;
bool gameover = false;

#define LEVEL_MAX 4
static int level = 0;
static const int DelayTable[LEVEL_MAX] = {20, 15, 10, 5};

namespace pz {

	void initField() {
		for (int y=0; y<FIELD_RH; y++) {
			for (int x=0; x<FIELD_RW; x++) {
				if (x == 0
				||  x == FIELD_RW-1
				||  y == FIELD_RH-1) {
					field[y][x] = 8;
				}
			}
		}
	}

	void newBlock() {
		int type = rand() % BLOCK_TYPE_NUM;
		for (int y=0; y<BLOCK_H; y++) {
			for (int x=0; x<BLOCK_W; x++) {
				current[y][x] = blockData[type][y][x];
			}
		}
	}

	void fixBlock(const BLOCK& src, int begx, int begy) {
		for (int y=0; y<BLOCK_H; y++) {
			for (int x=0; x<BLOCK_W; x++) {
				if (current[y][x] > 0) {
					field[y+begy][x+begx] = src[y][x];
				}
			}
		}
	}

	bool isIntersectField(const BLOCK& src, int begx, int begy) {
		for (int y=0; y<BLOCK_H; y++) {
			for (int x=0; x<BLOCK_W; x++) {
				if (src[y][x] > 0 && field[begy+y][begx+x] > 0) {
					return true;
				}
			}
		}
		return false;
	}

	bool isMoveX(const BLOCK& src, int reg_x) {
		return !isIntersectField(src, cur_x+reg_x, cur_y);
	}

	bool isMoveY(const BLOCK& src, int reg_y) {
		return !isIntersectField(src, cur_x, cur_y+reg_y);
	}

	bool isRotate() {
		BLOCK tmp = {0};
		for (int y=0; y<BLOCK_H; y++) {
			for (int x=0; x<BLOCK_W; x++) {
				tmp[x][BLOCK_W-1-y] = current[y][x];
			}
		}
		if (!isMoveX(tmp, 0)) return false;
		if (!isMoveY(tmp, 0)) return false;
		return true;
	}

	void rotate() {
		char tmp[BLOCK_H][BLOCK_W] = {0};
		memcpy(tmp, current, sizeof(tmp));
		for (int y=0; y<BLOCK_H; y++) {
			for (int x=0; x<BLOCK_W; x++) {
				current[x][BLOCK_W-1-y] = tmp[y][x];
			}
		}
	}

	int clearLine() {
		int n = 0;
		for (int y=FIELD_BEGY; y<FIELD_BEGY+FIELD_H; y++) {
			bool is_clear = true;
			for (int x=FIELD_BEGX; x<FIELD_BEGX+FIELD_W; x++) {
				if (field[y][x] <= 0) {
					is_clear = false;
					n++;
					break;
				}
			}
			if (is_clear) {
				for (int k=y-1; k >= 0; k--) {
					for (int x=FIELD_BEGX; x<FIELD_BEGX+FIELD_W; x++) {
						field[k+1][x] = field[k][x];
					}
				}
			}
		}
		return n;
	}

	bool isGameover() {
		for (int y=0; y<FIELD_BEGY; y++) {
			for (int x=FIELD_BEGX; x<FIELD_BEGX+FIELD_W; x++) {
				if (field[y][x] > 0) return true;
			}
		}
		return false;
	}

}// namespace pz

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

	init_pair(1, COLOR_RED,	COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	init_pair(3, COLOR_YELLOW, COLOR_WHITE);
	init_pair(4, COLOR_GREEN, COLOR_WHITE);
	init_pair(5, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(6, COLOR_CYAN, COLOR_WHITE);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);
	init_pair(8, COLOR_BLACK, COLOR_GREEN);	// 壁

	curs_set(0);				// カーソルを表示しない
	noecho();					// 入力待ちのカーソルを表示しない
	cbreak();					// 入力時、エンターを待たない
	keypad(stdscr, TRUE);		// キーパッド有効(KEY_LEFTなど)
	wtimeout(stdscr, 0);		// キー入力の待ち時間
	bkgd(COLOR_PAIR(1));		// 背景色
	refresh();

	pz::initField();
	srand((unsigned int)time(NULL));
}

void update(int key) {
	if (request_new_block) {
		request_new_block = false;
		pz::newBlock();
	}

	switch (key) {
		case KEY_LEFT:
			if (pz::isMoveX(current, -1)) {
				cur_x--;
			}
			break;
		case KEY_RIGHT:
			if (pz::isMoveX(current, 1)) {
				cur_x++;
			}
			break;
		case KEY_UP:
			if (pz::isRotate()) {
				pz::rotate();
			}
			break;
		case KEY_DOWN:
			if (pz::isMoveY(current, 1)) {
				cur_y++;
			}
			break;
	}

	if (!pz::isMoveY(current, 1)) {
		pz::fixBlock(current, cur_x, cur_y);
		gameover = pz::isGameover();

		pz::clearLine();
		request_new_block = true;
		cur_x = FIELD_BEGX;
		cur_y = 0;
	}
	else {
		if (delay <= 0) {
			delay = DelayTable[level];
			cur_y++;
		}
		else {
			delay--;
		}
	}
}

void draw() {
	clear();
	for (int y=0; y<FIELD_RH-FIELD_BEGY; y++) {
		for (int x=0; x<FIELD_RW; x++) {
			if (field[FIELD_BEGY+y][x] > 0) {
				mvaddch(y, x, '#' | COLOR_PAIR(field[FIELD_BEGY+y][x]));
			}

			int tcury = cur_y - FIELD_BEGY;
			if (tcury >= 0
			&&  x >= cur_x && x < cur_x+BLOCK_W
			&&  y >= tcury && y < tcury+BLOCK_H
			&& current[y-tcury][x-cur_x] > 0) {
				mvaddch(y, x, '#' | COLOR_PAIR(current[y-tcury][x-cur_x]));
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
