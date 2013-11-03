// ファイヤープロジェクト >> 出力文字の属性
// http://www.fireproject.jp/feature/c-language/curses/attribute.html
#pragma comment(lib , "pdcurses.lib")

#include <curses.h>
#include <stdlib.h>
#include <stdio.h>

#define YSTEP 2

static short repeat_flag = 1;

int main(void) {
	int x,y;
	int color_pair_no;

	int colors[] = {  
		COLOR_BLACK,
		COLOR_RED,
		COLOR_GREEN,
		COLOR_YELLOW,
		COLOR_BLUE,
		COLOR_MAGENTA,
		COLOR_CYAN,
		COLOR_WHITE,
	};
	int color_num = 8;

	if(initscr() == NULL){
		fprintf(stderr, "initscr failure\n");
		exit(EXIT_FAILURE);
	}

	if(has_colors() == FALSE || start_color() == ERR){
		endwin();
		fprintf(stderr, "has_colors or start_color failure\n");
		exit(EXIT_FAILURE);
	}

	// カラーを登録する
	color_pair_no = 1;
	for(y = 0; y < color_num; y++){
		for(x = 0; x < color_num; x++){
			init_pair(color_pair_no, colors[x], colors[y]);
			color_pair_no++;
		}
	}

	// 表示
	color_pair_no = 1;
	for(y = 0; y < LINES && y < color_num; y++){
		for(x = 0; x < COLS && x < color_num; x++){
			attrset(COLOR_PAIR(color_pair_no));
			mvprintw(y, x, "*");
			color_pair_no++;
		}
	}

	refresh();

	while (true) ;

	endwin();
	exit(EXIT_SUCCESS);
}
