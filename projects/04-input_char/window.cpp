
#include "windowImpl.hpp"

#undef getch

namespace curses {

	Window::Window(int x, int y, int width, int height) {
		_impl = std::make_shared<Impl>(x, y, width, height);
	}

	Window::~Window() {
	}

	int Window::addstr(std::string str) {
		return ::waddstr(_impl->wnd, str.c_str());
	}

	int Window::addch(char c) {
		return ::waddch(_impl->wnd, c);
	}

	int Window::attroff(MCHAR t) {
		return ::wattroff(_impl->wnd, t);
	}

	int Window::attron(MCHAR t) {
		return ::wattron(_impl->wnd, t);
	}

	int Window::attrset(MCHAR t) {
		return ::wattrset(_impl->wnd, t);
	}

	int Window::getbegx() {
		return ::getbegx(_impl->wnd);
	}

	int Window::getbegy() {
		return ::getbegx(_impl->wnd);
	}

	int Window::bkgd(MCHAR t) {
		return ::wbkgd(_impl->wnd, t);
	}

	void Window::bkgdset(MCHAR t) {
		::wbkgdset(_impl->wnd, t);
	}

	int Window::box(char vertical_char, char horizontal_char) {
		return ::box(_impl->wnd, vertical_char, horizontal_char);
	}

	int Window::clear() {
		return ::wclear(_impl->wnd);
	}

	int Window::clrtoeol() {
		return ::wclrtoeol(_impl->wnd);
	}

	int Window::color_set(short a, void* b) {
		return ::wcolor_set(_impl->wnd, a, b);
	}

	int Window::curx() {
		return ::getcurx(_impl->wnd);
	}

	int Window::cury() {
		return ::getcury(_impl->wnd);
	}

	int Window::delch() {
		return ::wdelch(_impl->wnd);
	}

	int Window::deleteln() {
		return ::wdeleteln(_impl->wnd);
	}

	MCHAR Window::getbkgd() {
		return ::getbkgd(_impl->wnd);
	}

	char Window::getch() {
		return static_cast<char>(::wgetch(_impl->wnd));
	}

	std::string Window::getnstr(int len) {
		// yohhoyの日記 >> 文字列取得バッファとしてのstd::string
		// http://d.hatena.ne.jp/yohhoy/20130413/p1
		std::string buf(len, '\0');
		int r = ::wgetnstr(_impl->wnd, &buf[0], len);
		buf.resize(r);
		return buf;
	}

	int Window::idlok(bool b) {
		return ::idlok(_impl->wnd, b);
	}

	int Window::inch() {
		return ::winch(_impl->wnd);
	}

	int Window::insch(char t) {
		return ::winsch(_impl->wnd, t);
	}

	int Window::insertln() {
		return ::winsertln(_impl->wnd);
	}

	int Window::keypad(int b) {
		return ::keypad(_impl->wnd, b);
	}

	int Window::maxx() {
		return ::getmaxx(_impl->wnd);
	}

	int Window::maxy() {
		return ::getmaxy(_impl->wnd);
	}

	int Window::move(int x, int y) {
		return ::wmove(_impl->wnd, y, x);
	}

	int Window::nodelay(bool b) {
		return ::nodelay(_impl->wnd, b);
	}

	int Window::refresh() {
		return ::wrefresh(_impl->wnd);
	}

	int Window::resize(int lines, int cols) {
		return ::wresize(_impl->wnd, lines, cols);
	}

	int Window::scrl(int num) {
		return ::wscrl(_impl->wnd, num);
	}

	int Window::scroll() {
		return ::scroll(_impl->wnd);
	}

	int Window::scrollok(bool b) {
		return ::scrollok(_impl->wnd, b);
	}

	int Window::setscrreg(int top, int bottom) {
		return ::wsetscrreg(_impl->wnd, top, bottom);
	}

	Window::Ptr Window::subwin(int x, int y, int width, int height) {
		Window::Ptr p = std::shared_ptr<Window>();
		p->_impl->wnd = ::subwin(_impl->wnd, height, width, y, x);
		return p;
	}

	void Window::timeout(int t) {
		::wtimeout(_impl->wnd, t);
	}

}// namespace pdcurses
