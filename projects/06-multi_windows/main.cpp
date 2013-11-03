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
	curses::Initializer ci(24, 60);
	ci.setColorPair(1, COLOR_WHITE, COLOR_BLACK);
	ci.setColorPair(2, COLOR_CYAN, COLOR_WHITE);
	ci.setColorPair(3, COLOR_WHITE, COLOR_CYAN);

	curses::Window::Ptr wnd = make_shared<curses::Window>(0, 0, COLS, LINES);
	curses::Window::Ptr wnd2 = make_shared<curses::Window>(2, 2, 40, 16);
	curses::Window::Ptr wnd3 = make_shared<curses::Window>(2, 2, 8, 4);

	wnd->clear();
	wnd->bkgd(COLOR_PAIR(1));
	wnd->box('#', '#');
	wnd->refresh();

	wnd2->clear();
	wnd2->bkgd(COLOR_PAIR(2));
	wnd2->box('+', '+');
	wnd2->refresh();

	wnd3->clear();
	wnd3->bkgd(COLOR_PAIR(3));
	wnd3->box('@', '@');
	wnd3->refresh();

	while (true) ;

	return 0;
}
