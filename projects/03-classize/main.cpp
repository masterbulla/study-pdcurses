#pragma comment(lib , "pdcurses.lib")

#include <curses.h>
#include <string.h>

class CursesSystem {
};

class CursesWindow {
public:


};

int main() {
    initscr();
    start_color();
    resize_term(10, 40);
 
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_CYAN);
 
    WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
    wbkgd(mainWindow, COLOR_PAIR(1));
     
    // 中央揃え
    wmove(mainWindow, 3, ((COLS-1)-strlen("Hello world!!")) / 2);
    waddstr(mainWindow, "Hello world!!");
     
    mvwaddch(mainWindow, 5, 5, 'a' | COLOR_PAIR(2));
    wrefresh(mainWindow);
    
	while (1) ;

    endwin();// 最後の後片付け
	return 0;
}
