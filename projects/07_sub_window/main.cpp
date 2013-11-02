#pragma comment(lib , "pdcurses.lib")

#include <curses.h>
#include <string.h>

int main() {
    initscr();
    start_color();
    resize_term(20, 48);
 
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_CYAN);
 
	// 親ウィンドウを作る
    WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
    wbkgd(mainWindow, COLOR_PAIR(1));
	wbkgd(mainWindow, '#');// #で埋め尽くして

	// 子ウィンドウ１を作る
	WINDOW* subWindow = subwin(mainWindow, LINES>>1, COLS>>1, LINES>>1, COLS>>1);
	wbkgd(subWindow, '@');// -で埋め尽くす

	// 子ウィンドウ２を作る
	WINDOW* sub2Window = derwin(subWindow, 5, 10, 0, 0);
	wbkgd(sub2Window, '.');// .で埋め尽くす

	// 親だけリフレッシュしても
	// 描画領域を共有しているので子ウィンドウの更新が反映される。
	wrefresh(mainWindow);
	
	// =======================================
	// サブウィンドウを絶対座標で無理やり移動する。
	// 問題なく動くが、これは推奨されない、というかやってはいけないレベル。
	// =======================================
#if 0
	getchar();

	mvwin(sub2Window, 2, 4);
	wclear(mainWindow);// 一回クリアしないと上手く更新されない
	wbkgd(mainWindow, '#');
	wclear(subWindow);// 一回クリアしないと上手く更新されない
	wbkgd(subWindow, '@');
	wrefresh(mainWindow);
	
	getchar();

	wclear(sub2Window);
	wbkgd(sub2Window, '.');// .で埋め尽くす
	wrefresh(sub2Window);
#else
	// =======================================
	// サブウィンドウを相対座標で移動する。
	// サブウィンドウの移動はこっち推奨。
	// =======================================
	getchar();

	wclear(mainWindow);// 一回クリアしないと上手く更新されない
	wbkgd(mainWindow, '#');
	wclear(subWindow);// 一回クリアしないと上手く更新されない
	wbkgd(subWindow, '@');
	wrefresh(mainWindow);
	
	getchar();

	wclear(sub2Window);
	mvderwin(sub2Window, 2, 2);// ★TODO
	wbkgd(sub2Window, '.');// .で埋め尽くす
	wrefresh(sub2Window);
#endif

	while (1) ;

    endwin();// 最後の後片付け
	return 0;
}
