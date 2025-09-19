#include "gameFrameWork.h"
#include "tcs.h"

IMAGE imgBG;
IMAGE imgSnake[4];
IMAGE imgApple;
IMAGE imgBody;
void gameInit() {
	loadimage(&imgBG, L"./she/bg.bmp");
	loadimage(&imgApple, L"./she/apple.bmp");
	loadimage(&imgBody, L"./she/body.bmp");
	TCHAR tchar[100];
	for (int i = 0; i < 4; i++)
	{
		_stprintf(tchar, L"./she/head%d.bmp",i);
		loadimage(&imgSnake[i], tchar);
	}
	newApple();
	newSnake();
	return;
}
void gamePaint() {
	// ����
	putimage(0, 0, &imgBG);
	// ƻ��
	putimage(p_apple->lie * 30, p_apple->hang * 30, &imgApple);
	// ��ͷ
	putimage(p_snake->header->lie * 30, p_snake->header->hang * 30, &imgSnake[p_snake->fangxiang]);
	//��
	snake_node* p_node = p_snake->header->next;
	while (p_node) {
		putimage(p_node->lie * 30, p_node->hang * 30, &imgBody);
		p_node = p_node->next;
	}
	return;
}

void gameInterval() {
	snakeMove();
	if (enableEatApple()) {
		snakeGrow();
		newApple();
	}
	if (enableOut()) {
		gameOver();
	}
	if (enableEatSelf()) {
		gameOver();
	}
	return;
}

void gameKeyPress(int key) {
	switch (key)
	{
	case VK_LEFT:
		if (p_snake->fangxiang != 0)
		{
			p_snake->fangxiang = 2;
		}
		break;
	case  VK_RIGHT:
		if (p_snake->fangxiang != 2)
		{
			p_snake->fangxiang = 0;
		}
		break;
	case VK_UP:
		if (p_snake->fangxiang != 3)
		{
			p_snake->fangxiang = 1;
		}
		break;
	case VK_DOWN:
		if (p_snake->fangxiang != 1)
		{
			p_snake->fangxiang = 3;
		}
		break;
	}
	return;
}

void gameMouseUp(int mouseX,int mouseY) {
	/*������*/
	return;
}

void gameMouseMove(int mouseX, int mouseY) {
	/*������*/
	return;
}

void gameMouseDown(int mouseX, int mouseY) {
	/*������*/
	return;
}

void gameMouseRightDown(int mouseX, int mouseY) {
	/*������*/
	return;

}


void gameOver() {
	// stop ��1
	stop = 1;
	// �ͷ�ƻ��
	free(p_apple);
	p_apple = NULL;
	// �ͷ��ߵĽڵ�
	snake_node* p_cur = p_snake->header;
	snake_node* p_tmp = NULL;
	while (p_cur) {
		p_tmp = p_cur->next;
		free(p_cur);
		p_cur = p_tmp;
	}
	// �ͷ���
	free(p_snake);
	p_snake = NULL;
	return;
}