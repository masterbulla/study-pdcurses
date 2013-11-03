
#pragma comment(lib , "pdcurses.lib")
#pragma comment(lib , "winmm.lib")

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <Windows.h>

#define FRAME_RATE 60L
#define FRAME_TIME 1000/FRAME_RATE

static int _fps;
static int _fpsCount;
static long _prevTime;
static long _nowTime;

static bool frameLimit() {
    long diff = timeGetTime() - _nowTime;
    long sleepTime = (FRAME_TIME - diff);
    if (sleepTime > 0) {
		Sleep(sleepTime);
    }
    _nowTime = timeGetTime();
    if ((_nowTime-_prevTime) > 1000L) {
        _fps = _fpsCount;
        _fpsCount = 0;
        _prevTime = _nowTime;
    }
    _fpsCount++;
    return true;
}

#define CHIP_W 8
#define CHIP_H 12
#define SCREEN_W 64
#define SCREEN_H 20
#define SCREEN_VW CHIP_W*SCREEN_W
#define SCREEN_VH CHIP_H*SCREEN_H

static float px = 0;
static float py = 0;
static float vx = 1.0f;
static float vy = 1.0f;

/**

	ダブルクリックぽいことすると極端にFPSが下がる例。

*/

int main() {
	initscr();
    start_color();
    resize_term(SCREEN_H, SCREEN_W);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_RED);
 
    WINDOW* wnd = newwin(LINES-1, COLS, 0, 0);
    wbkgd(wnd, COLOR_PAIR(1));

	cbreak();// エンターが押されなくても入力とする
	keypad(wnd, TRUE);// キーパッドを有効に
	mouse_set(ALL_MOUSE_EVENTS);// 全てのマウスイベントを取得する
	wrefresh(wnd);

	// 入力チェックのタイムアウト
	wtimeout(wnd, 0);

	WINDOW* mouseInfo = newwin(1, COLS, LINES-1, 0);
	wbkgd(mouseInfo, COLOR_PAIR(1));
	wrefresh(mouseInfo);

	while (1) {
		frameLimit();
		wclear(wnd);

		char str[10];
		sprintf_s(str, "%2d", _fps);
		mvwaddstr(wnd, 0, 0, str);

		int x = (int)(px / CHIP_W);
		int y = (int)(py / CHIP_H);
		mvwaddch(wnd, y, x, '@' | COLOR_PAIR(2));

		px += vx;
		py += vy;
		if (px < 0 || px > SCREEN_VW-CHIP_W) vx *= -1.0f;
		if (py < 0 || py > SCREEN_VH-CHIP_H) vy *= -1.0f;

		wrefresh(wnd);

		int c = wgetch(wnd);
		if (c != ERR) {
			if (c == KEY_MOUSE) {
				int button = 0;
				request_mouse_pos();

				mvprintw(0, 5, "mouse event");

				wmove(mouseInfo, 0, 0);
				if (MOUSE_MOVED)
					waddstr(mouseInfo, "moved: ");
				else if (MOUSE_WHEEL_UP)
					waddstr(mouseInfo, "wheel up: ");
				else if (MOUSE_WHEEL_DOWN)
					waddstr(mouseInfo, "wheel dn: ");
				else if ((BUTTON_STATUS(button) &
					BUTTON_ACTION_MASK) == BUTTON_PRESSED)
					waddstr(mouseInfo, "pressed: ");
				else if ((BUTTON_STATUS(button) &
					BUTTON_ACTION_MASK) == BUTTON_CLICKED)
					waddstr(mouseInfo, "clicked: ");
				else if ((BUTTON_STATUS(button) &
					BUTTON_ACTION_MASK) == BUTTON_DOUBLE_CLICKED)
					waddstr(mouseInfo, "double: ");
				else
					waddstr(mouseInfo, "released: ");

				wprintw(mouseInfo, "Position: Y: %d X: %d", MOUSE_Y_POS, MOUSE_X_POS);
				wrefresh(mouseInfo);
			}
		}
	}
     
    endwin();
	return 0;
}
