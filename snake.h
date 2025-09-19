#pragma once
#include "data_type.h"
#include <stdlib.h>
#include "apple.h"
#include <stdio.h>
extern snake* p_snake;
void newSnake();
int enableEatApple();
int enableOut();
int enableEatSelf();
void snakeMove();
void snakeGrow();
void turnLeft();
void turnRight();
void turnUp();
void turnDown();
