#pragma comment(lib , "pdcurses.lib")

#include "window.h"
#include <string.h>
#include <memory>
#include <string>

#include <curses.h>
#undef getch

namespace curses {

class Initializer {
public:
	Initializer(int y, int x) {
		initscr();
		start_color();
		resize_term(y, x);
	}

	~Initializer() {
		endwin();
	}

	void setColorPair(int no, int col, int bgCol) {
		init_pair(no, col, bgCol);
	}
};

}// namespace pdcurses

using namespace std;

int main() {
	curses::Initializer ci(10, 40);
	ci.setColorPair(1, COLOR_WHITE, COLOR_BLACK);
	ci.setColorPair(2, COLOR_WHITE, COLOR_BLUE);
	ci.setColorPair(3, COLOR_WHITE, COLOR_CYAN);

	curses::Window::Ptr wnd = make_shared<curses::Window>(0, 0, COLS, LINES);
	wnd->bkgd(COLOR_PAIR(1));
	
	::nocbreak();// エンターを押すまで待つ
	//::noecho();

	char ch = 0;
	while (ch != 'q') {
		ch = wnd->getch();
		wnd->clear();
		wnd->move(0, 0);
		wnd->addch('a');
		wnd->move(((COLS-1)-strlen("Hello world!!")) / 2, 3);
		wnd->addstr("Hello world!!");
		wnd->refresh();
	}

	return 0;
}
