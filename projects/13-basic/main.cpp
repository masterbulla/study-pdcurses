
#pragma comment(lib , "pdcurses.lib")

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define SCREEN_W 64
#define SCREEN_H 20

/**

	PDCurses基本

*/

int main() {
	initscr();// メインウィンドウであるstdscrのポインタを返す。
	//WINDOW* stdwin = initscr(); これでもOK.

	// カラーが使えるかのチェック。
	// 色分けが認識できないと成り立たないアプリは確認必須。
    if (has_colors() == FALSE || start_color() == ERR) {
		endwin();
		return -1;
	}
    resize_term(SCREEN_H, SCREEN_W);

	// 使用する色の設定
	// 文字色＋背景色で設定する
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_RED);

	// ウィンドウを使わなくても描画はできる
	// ※ウィンドウにstdscrを使うのと同じ
	move(0, 0);						// = wmove(stdscr, 0, 0);
	attron(A_BOLD);					// attronで好きな属性をオンにする
	addstr("# hello pdcurses");
	attrset(A_NORMAL);				// 使い終わったらsetで一気にNORMALに戻す
	mvaddstr(1, 0, "## introduction");
	mvaddstr(2, 2, "+ i see.");
	mvaddstr(3, 2, "+ i understand.");
	mvaddstr(4, 2, "+ i understood.");
	attrset(COLOR_PAIR(1));			// 色の変更。init_pairで指定した番号
	mvaddstr(5, 2, "+ i got it.");
	attrset(A_NORMAL);				// 元に戻す

	// フォーマット文字列。但しC++では推奨されない。
	mvprintw(6, 2, "format string %d", 200);
	refresh();

	while (1) ;

    endwin();						// 終了処理
	return 0;
}
