#include "gameFrameWork.h"
int interval = 100;
int screenWidth = 600;
int screenHeight = 600;
int times = 0;
int stop = 0;

void initGame() {
	/*随机时间种子*/
	srand((unsigned)time(NULL));
	/*设置背景颜色*/
	setbkcolor(NULL);
	/*设置背景模式*/
	setbkmode(TRANSPARENT);
	/*初始化游戏*/
	gameInit();
	return;
}

void paint() {
	/*批量绘图开始*/
	BeginBatchDraw();
	/*使用当前背景色清空绘图设备*/
	cleardevice();
	/*调用游戏绘图*/
	gamePaint();
	/*批量绘制结束*/
	EndBatchDraw();
	return;
}

void run() {
	/*创建鼠标和按键结构体变量*/
	ExMessage msg;
	/*循环接收外设传来的消息：
		判断线程的信息队列
			检查是否按键
				鼠标移动：
				鼠标左键点击
				鼠标左键抬起
				鼠标左键再次点击
				鼠标右键点击
				鼠标右键抬起
				鼠标右键再次点击
				上下左右
		
			重新绘画
			继续
	*/
	while (1) {
		if (peekmessage(&msg,-1, true)) {
			switch (msg.message) {
			case WM_MOUSEMOVE:
				gameMouseMove(msg.x, msg.y);
				break;
			case WM_LBUTTONDOWN:
				gameMouseDown(msg.x, msg.y);
				break;
			case WM_LBUTTONUP:
				gameMouseUp(msg.x, msg.y);
				break;
			case WM_LBUTTONDBLCLK:
				break;
			case WM_RBUTTONDOWN:
				break;
			case WM_RBUTTONUP:
				gameMouseRightDown(msg.x, msg.y);
				break;
			case WM_RBUTTONDBLCLK:
				break;
			case WM_KEYDOWN:
				gameKeyPress(msg.vkcode);
			}
			paint();
			continue;
		}
		/*睡眠1ms*/
		Sleep(1);
		/*计数器+1*/
		times++;
		/*如果计时器对interval/10取余不为0，继续*/
		if (times % (interval / 10) != 0) {
			continue;
		}
		/*重置计数器为0*/
		times = 0;
		/*若停止标志为1，跳出循环*/
		if (stop) break;
		/*进入游戏主程*/
		gameInterval();
		/*重新绘画*/
		paint();
	}
	return;
}

void drawImage(int picture_x, int picture_y, IMAGE* picture) {
	/*调用库函数*/
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ��ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ��ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				if (dstX < 0) continue;
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
	return;
}

void drawImageAlpha(int x0, int y0, IMAGE* img, double f) {
	/*调用库函数*/
	int qwidth, qheight;
	qwidth = img->getwidth();
	qheight = img->getheight();


	//PͼΪ����ͼ,RSΪĿ��ͼƬ
	static IMAGE RS(qwidth, qheight);
	static IMAGE P(qwidth, qheight);


	//����ͼ�Ļ���
	getimage(&P, x0, y0, qwidth, qheight);


	//��ȡָ�룬��Ϊ͸���ȼ���
	DWORD* M = GetImageBuffer(&P);
	DWORD* N = GetImageBuffer(img);
	DWORD* R = GetImageBuffer(&RS);


	// ����������ͼģʽ�������˸����
	BeginBatchDraw();


	//�����븳ֵ
	int i, j;
	for (i = 0; i < qheight; i++) {
		for (j = 0; j < qwidth; j++) {
			int r, g, b;
			int ij;
			//����
			ij = i * qwidth + j;
			r = (int)((GetRValue(N[ij])) * (1 - f) + GetRValue(M[ij]) * f);
			g = (int)((GetGValue(N[ij])) * (1 - f) + GetGValue(M[ij]) * f);
			b = (int)((GetBValue(N[ij])) * (1 - f) + GetBValue(M[ij]) * f);
			R[ij] = RGB(r, g, b);
		}
	}

	//����ͼƬ���ͷ��ڴ�
	putimage(x0, y0, &RS);
	FlushBatchDraw();// ����
	return;
}

int hitTest(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	/*调用库函数*/
	return !(x1 + w1 < x2 ||
		y1 + h1 < y2 ||
		x2 + w2 < x1 ||
		y2 + h2 < y1);
}

int main(int argc,char* argv[]) {	
	/*初始化绘图窗口*/
	initgraph(screenWidth,screenHeight,0);
	/*初始化游戏*/
	initGame();
	/*绘画*/
	paint();
	/*清空消息范围*/
	flushmessage();
	/*若当前有键盘输入，从控制台中读取单个字符*/
	while (_kbhit()) _getch(); 
	/*进入run线程*/
	run();
	/*关闭图形模式*/
	closegraph();
	return 0;
}