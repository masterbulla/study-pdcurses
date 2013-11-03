// prefresh について
// http://docs.oracle.com/cd/E19455-01/816-3522/6m9q1pt6r/index.html
#pragma comment(lib , "pdcurses.lib")

#include <curses.h>
#include <string.h>

int main() {
    initscr();
    start_color();
    resize_term(18, 40);
 
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_CYAN);
 
    WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
    wbkgd(mainWindow, COLOR_PAIR(1));
     
	// 中央揃え
	wmove(mainWindow, 3, ((COLS-1)-strlen("Hello world!!")) / 2);
	waddstr(mainWindow, "Hello world!!");
	mvwaddch(mainWindow, 5, 5, 'a' | COLOR_PAIR(2));
	wrefresh(mainWindow);

	// パッドを作る
	WINDOW* pad = newpad(18, 80);
	box(pad, '+', '+');
	for (int i=0; i<getmaxx(pad); i++) {
		wmove(pad, i/10, i);
		waddch(pad, '0'+i%10);
	}
	
	// padはstdscrに対して描画する
	int pmincol = 0;	// パッド中に表示する四角形の左上角の位置 X
	int pminrow = 0;	// パッド中に表示する四角形の左上角の位置 Y
	int smincol = 0;	// 画面に表示する四角形の各辺の位置 SCREEN_X
	int sminrow = 0;	// 画面に表示する四角形の各辺の位置 SCREEN_Y
	int smaxcol = 40;	// 画面に表示する四角形の各辺の位置 SCREEN_W
	int smaxrow = 18-1;	// 画面に表示する四角形の各辺の位置 SCREEN_H
	while (1) {
		prefresh(
			pad,
			pminrow,// つまりパッドの中において、どの部分を表示するかの開始座標X
			pmincol,
			sminrow,// 画面内のどこに表示するかX。座標は画面内でなければいけない。
			smincol,// XY共に右(プラス方向)であれば画面外に出ても落ちない。Yはマイナスになるとエラー吐く。
			smaxrow,
			smaxcol
			);

		if (pmincol < 80-40) {
			pmincol++;
		}
		getch();
	}

    endwin();// 最後の後片付け
	return 0;
}
