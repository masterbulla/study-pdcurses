
#include "window.h"
#include <curses.h>

namespace curses {

class Window::Impl {
public:
	Impl(int x, int y, int width, int height) :
	wnd(nullptr) {
		wnd = ::newwin(height, width, y, x);
	}

	~Impl() {
		::delwin(wnd);
	}

	WINDOW* wnd;
};

}// namespace pdcurses
