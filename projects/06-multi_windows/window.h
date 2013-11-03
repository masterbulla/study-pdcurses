// python - 15.8. curses >> 文字セル表示のための端末操作
// http://docs.python.jp/2.6/library/curses.html
// ファイヤープロジェクト >> cursesの基本的な関数
// http://www.fireproject.jp/feature/c-language/curses/basic.html
// NCURSES Programming HOWTO
// http://www.on-sky.net/~hs/misc/?NCURSES+Programming+HOWTO#l12
// Ruby 1.9.3 リファレンスマニュアル >> cursesライブラリ
// http://docs.ruby-lang.org/ja/1.9.3/class/Curses=3a=3aWindow.html
// sun >> Curses ライブラリ関数
// http://anselmo.homeunix.net/Solaris9-DocsDisk2/Solaris_9_Doc/common/SUNWjaman/reloc/sun_docs/ja/solaris_9/SUNWjaman/hman3curses/curses.3curses.html

#include <string>
#include <memory>

#ifndef CURSES_ASSERT
#include <cassert>
#define CURSES_ASSERT(x) assert(x)
#endif

namespace curses {

typedef unsigned long MCHAR;

class Window {
public:
	typedef std::shared_ptr<Window> Ptr;
	Window();
	Window(int x, int y, int width, int height);
	~Window();

	void getChar();

	int mvderwin(int x, int y);// 親ウィンドウの中で移動
	int mvwin(int x, int y);// ウィンドウを移動
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
	int move(int x, int y);// カーソルの移動。ウィンドウではない
	int nodelay(bool);
	int refresh();
	int resize(int lines, int cols);
	int scrl(int num);
	int scroll();
	int scrollok(bool);
	int setscrreg(int top, int bottom);
	Ptr subwin(int x, int y, int width, int height);// (x,y)は絶対座標
	Ptr derwin(int x, int y, int width, int height);// (x,y)は親からの相対座標
	void timeout(int);

private:
	class Impl;
	std::shared_ptr<Impl> _impl;
};

}// namespace pdcurses
