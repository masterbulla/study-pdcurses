#pragma comment(lib , "pdcurses.lib")

#include "window.h"
#include <curses.h>
#include <string.h>

#include <memory>
#include <string>

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
	wnd->move(0, 0);
	wnd->addch('a');
     
	// 中央揃え
	wnd->move(((COLS-1)-strlen("Hello world!!")) / 2, 3);
	wnd->addstr("Hello world!!");

	wnd->refresh();

	while (1) ;
	return 0;
}
