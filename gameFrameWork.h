#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <easyx.h>
#include <conio.h>
#include <time.h>
#include "snake.h"
#include "apple.h"
#include "data_type.h"
#include <stdio.h>
extern int interval;
extern int screenWidth;
extern int screenHeight;
extern int stop;
extern int times;
void gamePaint();
void gameInit();
void gameInterval();
void gameKeyPress(int key);
void gameMouseDown(int mouseX,int mouseY);
void gameMouseUp(int mouseX, int mouseY);
void gameMouseMove(int mouseX, int mouseY);
void gameMouseRightDown(int mouseX, int mouseY);
void drawImage(int picture_x, int picture_y, IMAGE* pictue);
void drawImageAlpha(int x0, int y0, IMAGE* img, double f);
int hitTest(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);