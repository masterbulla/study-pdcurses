// ファイヤープロジェクト >> cursesの基本的な関数
// http://www.fireproject.jp/feature/c-language/curses/basic.html
// NCURSES Programming HOWTO
// http://www.on-sky.net/~hs/misc/?NCURSES+Programming+HOWTO#l12
// Ruby 1.9.3 リファレンスマニュアル >> cursesライブラリ
// http://docs.ruby-lang.org/ja/1.9.3/class/Curses=3a=3aWindow.html

#include <string>
#include <memory>

namespace curses {

typedef unsigned long MCHAR;

class Window {
public:
	typedef std::shared_ptr<Window> Ptr;
	Window(int x, int y, int width, int height);
	~Window();

	int addstr(std::string);
	int addch(char);
	int attroff(MCHAR);
	int attron(MCHAR);
	int attrset(MCHAR);
	int getbegx();
	int getbegy();
	int bkgd(MCHAR);
	void bkgdset(MCHAR);
	int box(char vertical_char, char horizontal_char);
	int clear();
	int clrtoeol();
	int color_set(short, void*);
	int curx();
	int cury();
	int delch();
	int deleteln();
	MCHAR getbkgd();
	char getch();
	//std::string getstr(); バッファオーバーフローするため非推奨
	std::string getnstr(int len);// 読み込む文字数
	int idlok(bool);
	int inch();
	int insch(char);
	int insertln();
	int keypad(int);
	int maxx();
	int maxy();
	int move(int x, int y);
	int nodelay(bool);
	int refresh();
	int resize(int lines, int cols);
	int scrl(int num);
	int scroll();
	int scrollok(bool);
	int setscrreg(int top, int bottom);
	Ptr subwin(int x, int y, int width, int height);
	void timeout(int);

private:
	class Impl;
	std::shared_ptr<Impl> _impl;
};

}// namespace pdcurses
