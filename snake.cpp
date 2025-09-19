#include "snake.h"
SNAKE* p_snake = (SNAKE*)malloc(sizeof(SNAKE));
/*创建蛇结构体指针 初始化*/

void newSnake() {
	SNAKE_NODE* s1 = (SNAKE_NODE*)malloc(sizeof(SNAKE_NODE));
	SNAKE_NODE* s2 = (SNAKE_NODE*)malloc(sizeof(SNAKE_NODE));
	SNAKE_NODE* s3 = (SNAKE_NODE*)malloc(sizeof(SNAKE_NODE));
	SNAKE_NODE* s4 = (SNAKE_NODE*)malloc(sizeof(SNAKE_NODE));
	SNAKE_NODE* s5 = (SNAKE_NODE*)malloc(sizeof(SNAKE_NODE));
	
	*s1 = { 10,10,NULL,s2 };
	*s2 = { 11,10,s1,s3 };
	*s3 = { 12,10,s2,s4 };
	*s4 = { 13,10,s3,s5 };
	*s5 = { 14,10,s4,NULL };

	p_snake->fangxiang = 1;
	p_snake->length = 5;
	p_snake->header = s1;
	p_snake->ender = s5;
	return;
}
int enableEatApple() {
	return p_snake->header->hang == p_apple->hang && 
		p_snake->header->lie == p_apple->lie;
}
int enableOut() {
	return p_snake->header->hang == 0 ||
		p_snake->header->hang == 19 ||
		p_snake->header->lie == 0 ||
		p_snake->header->lie == 19;
}
int enableEatSelf() {
	snake_node* p_node = p_snake->header->next;
	while (p_node) {
		if (p_snake->header->hang == p_node->hang && 
			p_snake->header->lie  == p_node->lie) {
			return 1;
		}
		p_node = p_node->next;
	}
	return 0;
}
void snakeMove() {
	snake_node* p_node = p_snake->ender;
	while (p_node != p_snake->header)
	{
		p_node->hang = p_node->prev->hang;
		p_node->lie = p_node->prev->lie;
		p_node = p_node->prev;
	}
	switch (p_snake->fangxiang)
	{
	case 0:
		p_snake->header->lie++;
		break;
	case 1:
		p_snake->header->hang--;
		break;
	case 2:
		p_snake->header->lie--;
		break;
	case 3:
		p_snake->header->hang++;
		break;
	}
	return;
}
void snakeGrow() {
	p_snake->length++;
	snake_node* p_node = (snake_node*)malloc(sizeof(SNAKE_NODE));
	*p_node = { p_snake->ender->hang,p_snake->ender->lie,p_snake->ender,NULL };
	p_snake->ender->next = p_node;
	p_snake->ender = p_snake->ender->next;
	return;
}
void turnLeft() {
	p_snake->fangxiang = 2;
	return;
}
void turnRight() {
	p_snake->fangxiang = 0;
	return;
}
void turnUp() {
	p_snake->fangxiang = 1;
	return;
}
void turnDown() {
	p_snake->fangxiang = 3;
	return ;
}
