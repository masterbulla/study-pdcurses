
#include "window.h"
#include <curses.h>

namespace curses {

class Window::Impl {
public:
	typedef std::shared_ptr<Impl> Ptr;
	Impl() :
	wnd(nullptr),
	sub(false) {
	}

	Impl(int x, int y, int width, int height) :
	wnd(nullptr),
	sub(false) {
		wnd = ::newwin(height, width, y, x);
	}

	~Impl() {
		::delwin(wnd);
	}

	WINDOW* wnd;
	bool sub;
};

}// namespace pdcurses
