#pragma comment(lib , "pdcurses.lib")

#include <curses.h>
#include <string.h>

int main() {
    initscr();
    start_color();
    resize_term(10, 40);
 
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_CYAN);
 
    WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
    wbkgd(mainWindow, COLOR_PAIR(1));
     
    // íÜâõëµÇ¶
    wmove(mainWindow, 3, ((COLS-1)-strlen("Hello world!!")) / 2);
    waddstr(mainWindow, "Hello world!!");
     
    mvwaddch(mainWindow, 5, 5, 'a' | COLOR_PAIR(2));
    wrefresh(mainWindow);
    
	while (1) ;

    endwin();// ç≈å„ÇÃå„ï–ïtÇØ
	return 0;
}
