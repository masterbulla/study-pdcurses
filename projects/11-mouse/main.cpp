// ファイヤープロジェクト >> curses >> input
// http://www.fireproject.jp/feature/c-language/curses/mouse.html
// prefresh について
// http://docs.oracle.com/cd/E19455-01/816-3522/6m9q1pt6r/index.html
#pragma comment(lib , "pdcurses.lib")

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

/**

	マウス入力は取れるけれど、
	そこまでレスポンスが言い訳ではないみたい。

*/

int main() {
	MEVENT event;
	int input;

	if (initscr() == NULL) {
		exit(EXIT_FAILURE);
	}

	// cbreakモードじゃないとダメ。
	cbreak();
	// これも必須
	keypad(stdscr, TRUE);

	// マウス左クリックを有効化。座標もとれるように
	mousemask(BUTTON1_PRESSED | BUTTON3_PRESSED | REPORT_MOUSE_POSITION, NULL);
	refresh();

	while ((input = mvwgetch(stdscr, 0, 0)) != 'q') {
		if (input == KEY_MOUSE) {
			mvprintw(2, 5, "mouse event");
			if(nc_getmouse(&event) != OK){
				mvprintw(3, 5, "getmouse failure");
				continue;
			}
			mvprintw(3, 5, "x = %d, y = %d, z = %d", event.x, event.y, event.z);
			if (event.bstate == BUTTON1_PRESSED) {
				mvprintw(event.y, event.x, "*");
			}
			else if (event.bstate == BUTTON3_PRESSED) {
				mvprintw(event.y, event.x, " ");
			}
			refresh();
		}
		else {
			mvprintw(2, 5, "not mouse event %c", input);
		}
	}

	endwin();
	exit(EXIT_SUCCESS);
}
