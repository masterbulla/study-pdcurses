#pragma comment(lib , "pdcurses.lib")

#include <curses.h>
#include <string.h>

int main() {
    initscr();
    start_color();
    resize_term(20, 48);
 
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_CYAN);
 
	// �e�E�B���h�E�����
    WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
    wbkgd(mainWindow, COLOR_PAIR(1));
	wbkgd(mainWindow, '#');// #�Ŗ��ߐs������

	// �q�E�B���h�E�P�����
	WINDOW* subWindow = subwin(mainWindow, LINES>>1, COLS>>1, LINES>>1, COLS>>1);
	wbkgd(subWindow, '@');// -�Ŗ��ߐs����

	// �q�E�B���h�E�Q�����
	WINDOW* sub2Window = derwin(subWindow, 5, 10, 0, 0);
	wbkgd(sub2Window, '.');// .�Ŗ��ߐs����

	// �e�������t���b�V�����Ă�
	// �`��̈�����L���Ă���̂Ŏq�E�B���h�E�̍X�V�����f�����B
	wrefresh(mainWindow);
	
	// =======================================
	// �T�u�E�B���h�E���΍��W�Ŗ������ړ�����B
	// ���Ȃ��������A����͐�������Ȃ��A�Ƃ���������Ă͂����Ȃ����x���B
	// =======================================
#if 0
	getchar();

	mvwin(sub2Window, 2, 4);
	wclear(mainWindow);// ���N���A���Ȃ��Ə�肭�X�V����Ȃ�
	wbkgd(mainWindow, '#');
	wclear(subWindow);// ���N���A���Ȃ��Ə�肭�X�V����Ȃ�
	wbkgd(subWindow, '@');
	wrefresh(mainWindow);
	
	getchar();

	wclear(sub2Window);
	wbkgd(sub2Window, '.');// .�Ŗ��ߐs����
	wrefresh(sub2Window);
#else
	// =======================================
	// �T�u�E�B���h�E�𑊑΍��W�ňړ�����B
	// �T�u�E�B���h�E�̈ړ��͂����������B
	// =======================================
	getchar();

	wclear(mainWindow);// ���N���A���Ȃ��Ə�肭�X�V����Ȃ�
	wbkgd(mainWindow, '#');
	wclear(subWindow);// ���N���A���Ȃ��Ə�肭�X�V����Ȃ�
	wbkgd(subWindow, '@');
	wrefresh(mainWindow);
	
	getchar();

	wclear(sub2Window);
	mvderwin(sub2Window, 2, 2);// ��TODO
	wbkgd(sub2Window, '.');// .�Ŗ��ߐs����
	wrefresh(sub2Window);
#endif

	while (1) ;

    endwin();// �Ō�̌�Еt��
	return 0;
}
