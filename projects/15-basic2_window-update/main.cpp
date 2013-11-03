
#pragma comment(lib , "pdcurses.lib")

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define SCREEN_W 64
#define SCREEN_H 20

/**

	PDCurses基本 - ウィンドウの更新

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

	WINDOW* wnd1 = newwin(LINES, COLS, 0, 0);
	wbkgd(wnd1, COLOR_PAIR(1));

	WINDOW* wnd2 = newwin(LINES, COLS>>1, 0, COLS>>1);
	wbkgd(wnd2, COLOR_PAIR(2));

	WINDOW* wnd3 = newwin(LINES>>1, COLS>>1, LINES>>1, COLS>>1);
	wbkgd(wnd3, COLOR_PAIR(3));

	wmove(wnd1, 0, 0);
	waddstr(wnd1, "wnd1");

	wmove(wnd2, 0, 0);
	waddstr(wnd2, "wnd2");

	wmove(wnd3, 0, 0);
	waddstr(wnd3, "wnd3");

	wrefresh(wnd1);
	wrefresh(wnd2);
	wrefresh(wnd3);

	getchar();// wait

	/**
		これでウィンドウが全て描画できてめでたしめでたし･･･とはいかない。
		例えばウィンドウ１の内容が更新されたとする。
		次のようにデータを書き込んでリフレッシュすると、
		更新された部分しか画面上に再描画されない。

		全てリフレッシュしているはずなのに、
		ウィンドウ１の内容がウィンドウ２の上に
		表示されてしまっていることが分かる。
	*/
	wmove(wnd1, 1, 0);
	waddstr(wnd1, "updated asdlhiaglhigalihgalhidsal;fhkasdkl;hasd");
	
	wrefresh(wnd1);
	wrefresh(wnd2);
	wrefresh(wnd3);
	
	getchar();// wait

	/**
		この問題はtouchwin()を使うことで解決できる。
		touchwin()はウィンドウ全体に更新がかかっていることにする命令。
	*/
	
	// 全体に更新がかかったことにしてから
	touchwin(wnd1);
	touchwin(wnd2);
	touchwin(wnd3);

	// 再表示すればきちんと重なる。
	wrefresh(wnd1);
	wrefresh(wnd2);
	wrefresh(wnd3);

	getchar();// wait

	/**
		またwrefresh()は結構を時間がかかるらしい。※実行コストが高い
		refreshは()、内部でwnoutrefresh()の後にdoupdate()を呼んでいる。

		wnoutrefresh()はウィンドウ全体に更新がかかったことにするための命令。
		doupdate()は実際に更新されているものを再表示する命令。
		つまりwrefresh()を呼び出すたびに再表示命令が投げられてしまっている。
		
		この無駄を回避するためには、wrefresh()ではなく
		wnoutrefresh()を明示的に呼び出すようにし、
		最後に一回だけdoupdate()を呼び出すようにすればいい。
	*/

	// 全体に更新がかかったことにしてから
	touchwin(wnd1);
	touchwin(wnd2);
	touchwin(wnd3);

	wnoutrefresh(wnd1); // wrefreshではなく、論理的にだけリフレッシュする。
	wnoutrefresh(wnd2);
	wnoutrefresh(wnd3);
	doupdate();// 最後に１回だけ反映

	// 参考
	// http://www.fireproject.jp/feature/c-language/curses/multi-win.html
	// http://docs.python.jp/2.6/library/curses.html

	while (1) ;

    endwin();						// 終了処理
	return 0;
}
