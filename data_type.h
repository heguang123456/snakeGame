#pragma once
typedef struct snake_node
{
	int hang;
	int lie;
	snake_node* prev;
	snake_node* next;
}SNAKE_NODE;
typedef struct snake {
	int fangxiang;
	int length;
	SNAKE_NODE* header;
	SNAKE_NODE* ender;
}SNAKE;
typedef struct apple {
	int hang;
	int lie;
}APPLE;