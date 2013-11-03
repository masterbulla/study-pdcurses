
#pragma comment(lib , "pdcurses.lib")

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define SCREEN_W 64
#define SCREEN_H 20

/**

	PDCurses基本 - ウィンドウ

*/
int main() {
	initscr();
	if (has_colors() == FALSE || start_color() == ERR) {
		endwin();
		return -1;
	}
    resize_term(SCREEN_H, SCREEN_W);

	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);

	/**
	 * # ウィンドウを作る
	 * pdcursesのソースを見る限り、
	 * newwinで作られたウィンドウはstdscrと親子関係ではない。
	 * 但し、スクリーンサイズのようなグローバルパラメータは
	 * SPという変数に情報が保存され、それが様々な場所で参照される。
	 * なのでstdscrの子じゃないから親からの制約がないというわけではないぽい。
	 */
	// LINESとCOLSはグローバル変数。端末のサイズが入っている。
	WINDOW* wnd1 = newwin(LINES, COLS, 0, 0);
	wbkgd(wnd1, COLOR_PAIR(1));		// ウィンドウの文字色と背景色を指定

	// 適当に３つくらい作る
	WINDOW* wnd2 = newwin(LINES, COLS>>1, 0, COLS>>1);
	wbkgd(wnd2, COLOR_PAIR(2));

	WINDOW* wnd3 = newwin(LINES>>1, COLS>>1, LINES>>1, COLS>>1);
	wbkgd(wnd3, COLOR_PAIR(3));

	// ウィンドウにはstdscrと同様に文字が書き込める。
	// それらの関数は殆どが接頭辞としてwがついている。
	wmove(wnd1, 0, 0);
	waddstr(wnd1, "wnd1");

	wmove(wnd2, 0, 0);
	waddstr(wnd2, "wnd2");

	wmove(wnd3, 0, 0);
	waddstr(wnd3, "wnd3");

	/**
	 * refreshで表示！といきたいところだが、
	 * refreshを呼び出しても表示されない。
	 * 
	 * refreshはstdscrに対してのwrefreshであるから
	 * 各ウィンドウも個別にリフレッシュしてやる必要がある。
	 */
	//refresh();	// これはwrefresh(stdscr);と同義
	wrefresh(wnd1); 
	wrefresh(wnd2); // 後に描画したものが上書きされる
	wrefresh(wnd3);

	while (1) ;

    endwin();						// 終了処理
	return 0;
}
