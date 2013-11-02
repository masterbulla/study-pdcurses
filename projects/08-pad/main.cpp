#pragma comment(lib , "pdcurses.lib")

#include <curses.h>
#include <string.h>

int main() {
    initscr();
    start_color();
    resize_term(18, 40);
 
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_CYAN);
 
    WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
    wbkgd(mainWindow, COLOR_PAIR(1));
     
	// ��������
	wmove(mainWindow, 3, ((COLS-1)-strlen("Hello world!!")) / 2);
	waddstr(mainWindow, "Hello world!!");
	mvwaddch(mainWindow, 5, 5, 'a' | COLOR_PAIR(2));
	wrefresh(mainWindow);

	// �p�b�h�����
	WINDOW* pad = newpad(18, 80);
	box(pad, '+', '+');
	for (int i=0; i<getmaxx(pad); i++) {
		wmove(pad, i/10, i);
		waddch(pad, '0'+i%10);
	}
	
	// pad��stdscr�ɑ΂��ĕ`�悷��
	int pmincol = 0;	// �p�b�h���ɕ\������l�p�`�̍���p�̈ʒu X
	int pminrow = 0;	// �p�b�h���ɕ\������l�p�`�̍���p�̈ʒu Y
	int smincol = 0;	// ��ʂɕ\������l�p�`�̊e�ӂ̈ʒu SCREEN_X
	int sminrow = 0;	// ��ʂɕ\������l�p�`�̊e�ӂ̈ʒu SCREEN_Y
	int smaxcol = 40;	// ��ʂɕ\������l�p�`�̊e�ӂ̈ʒu SCREEN_W
	int smaxrow = 18-1;	// ��ʂɕ\������l�p�`�̊e�ӂ̈ʒu SCREEN_H
	while (1) {
		prefresh(
			pad,
			pminrow,// �܂�p�b�h�̒��ɂ����āA�ǂ̕�����\�����邩�̊J�n���WX
			pmincol,
			sminrow,// ��ʓ��̂ǂ��ɕ\�����邩X�B���W�͉�ʓ��łȂ���΂����Ȃ��B
			smincol,// XY���ɉE(�v���X����)�ł���Ή�ʊO�ɏo�Ă������Ȃ��BY�̓}�C�i�X�ɂȂ�ƃG���[�f���B
			smaxrow,
			smaxcol
			);

		if (pmincol < 80-40) {
			pmincol++;
		}
		getch();
	}

    endwin();// �Ō�̌�Еt��
	return 0;
}
