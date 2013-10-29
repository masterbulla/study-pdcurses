#pragma comment(lib , "pdcurses.lib")
#pragma comment(lib , "winmm.lib")

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

int main() {
	initscr();
    start_color();
    resize_term(SCREEN_H, SCREEN_W);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_RED);
 
    WINDOW* wnd = newwin(LINES, COLS, 0, 0);
    wbkgd(wnd, COLOR_PAIR(1));
     
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
	}
     
    endwin();
	return 0;
}
