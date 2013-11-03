// ファイヤープロジェクト >> 出力文字の属性
// http://www.fireproject.jp/feature/c-language/curses/attribute.html
#pragma comment(lib , "pdcurses.lib")

#include <curses.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <signal.h>
//#include <unistd.h>

#define YSTEP 2

void sig_handler(int SIG);

static short repeat_flag = 1;

int main(void) {
	int y;

	if (initscr() == NULL) {
		exit(EXIT_FAILURE);
	}

	y = 0;
	attrset(A_NORMAL);
	mvprintw(y, 0, "Normal");

	y += YSTEP;
	attron(A_STANDOUT);
	mvprintw(y, 0, "A_STANDOUT");
	attrset(A_NORMAL);

	y += YSTEP;
	attron(A_UNDERLINE);
	mvprintw(y, 0, "A_UNDERLINE");
	attrset(A_NORMAL);

	y += YSTEP;
	attron(A_REVERSE);
	mvprintw(y, 0, "A_REVERSE");
	attrset(A_NORMAL);

	y += YSTEP;
	attron(A_BLINK);
	mvprintw(y, 0, "A_BLINK");
	attrset(A_NORMAL);

	y += YSTEP;
	attron(A_DIM);
	mvprintw(y, 0, "A_DIM");
	attrset(A_NORMAL);

	y += YSTEP;
	attron(A_BOLD);
	mvprintw(y, 0, "A_BOLD");
	attrset(A_NORMAL);

	y += YSTEP;
	attron(A_PROTECT);
	mvprintw(y, 0, "A_PROTECT");
	attrset(A_NORMAL);

	y += YSTEP;
	attron(A_INVIS);
	mvprintw(y, 0, "A_INVIS");
	attrset(A_NORMAL);

	y += YSTEP;
	attron(A_ALTCHARSET);
	mvprintw(y, 0, "A_ALTCHARSET");
	attrset(A_NORMAL);

	y += YSTEP;
	attron(A_CHARTEXT);
	mvprintw(y, 0, "A_CHARTEXT");
	attrset(A_NORMAL);

	refresh();

	while (1) ;

	endwin();
	exit(EXIT_SUCCESS);
}

void sig_handler(int SIG) {
	repeat_flag = 0;
}
