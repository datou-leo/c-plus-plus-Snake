#pragma once
#include<stdio.h>
#include<tchar.h>
#include<graphics.h>
#include<mmsystem.h>
#pragma comment(lib ,"winmm.lib")
#include <time.h>
#include <conio.h>

#define N 20 //这里设置一节蛇的大小为20*20个像素
#define MAXM 1000

void InitGame();//初始化
void SnakeDraw();//绘制蛇
void SnakeMove();//蛇移动
void SnakeDirection();//蛇的方向控制
void EatFood();
void FoodPaint();
void FoodCool();
void GameBreak();
void GameOver();


enum CH {//枚举类型表示上下左右键的键值
	up = 72,
	down = 80,
	left = 75,
	right = 77
};

struct COOR {
	int x;
	int y;
};

struct SNAKE {
	int n;//蛇节数
	COOR scr[MAXM];//蛇节数的数组
	CH ch;
} snake;


struct Food {
	COOR fcr;//食物坐标
	int flag;//1标示没有食物，需要生成食物
} food;

IMAGE foods, snakeup, snakedown, snakeleft, snaketright, snakebody;
int main() {
	InitGame();//创建窗口

	while (1)//暂停
	{
		while (!_kbhit())
		{
			if (food.flag == 0) {
				FoodCool();
			}
			cleardevice();
			FoodPaint();
			SnakeMove();//蛇的移动
			SnakeDraw();//绘制蛇
			Sleep(300);
			EatFood();
			GameBreak();
		}
		SnakeDirection();
	}
	return 0;
}

void InitGame() {
	srand((unsigned int)time(NULL));//产生随机的种子
	initgraph(640, 480);
	setbkcolor(WHITE);//定义颜色
	cleardevice();//刷到背景去
	char ch[100];
	

	

	snake.scr[0].x = 0;//蛇开始出现的坐标
	snake.scr[0].y = 0;//蛇出现的坐标
	snake.n = 1;//蛇开始的节数
	snake.ch = right;
	food.flag = 0;//没有食物


	
}

void SnakeDraw() {//绘制蛇
	setlinecolor(GREEN); //设置蛇边缘的线条颜色
	setfillcolor(RED);  //设置蛇身的颜色
	//遍历数组
	for (int i = 0; i < snake.n; i++) {
		fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + N, snake.scr[i].y + N);  //根据蛇的当前长度，创建蛇身，
	}	

}

//蛇移动
void SnakeMove()
{
	for (int i = snake.n - 1; i > 0; i--) {
		snake.scr[i].x = snake.scr[i - 1].x;
		snake.scr[i].y = snake.scr[i - 1].y;
	}
	switch (snake.ch) {
	case up:
		snake.scr[0].y -= N;
		break;
	case down:
		snake.scr[0].y += N;
		break;
	case left:
		snake.scr[0].x -= N;
		break;
	case right:
		snake.scr[0].x += N;
		break;
	default:
		break;
	}
}

void SnakeDirection()
{
	switch (_getch())
	{
	case 72:
		if (snake.ch != down)
			snake.ch = up;
		break;
	case 80:
		if (snake.ch != up)
			snake.ch = down;
		break;
	case 75:
		if (snake.ch != right)
			snake.ch = left;
		break;
	case 77:
		if (snake.ch != left)
			snake.ch = right;
		break;


	default:
		break;
	}
}
//生成一个食物
void FoodCool()
{
	srand((unsigned)time(NULL));
	food.fcr.x = rand() % 32 * N;
	food.fcr.y = rand() % 24 * N;


	food.flag = 1;
}

void FoodPaint()
{
	//fillrectangle(food.fcr.x, food.fcr.y, food.fcr.x + N, food.fcr.y + N);
	setfillcolor(BLUE);
	fillroundrect(food.fcr.x, food.fcr.y, food.fcr.x + N, food.fcr.y + N, N, N);
}
//食物的坐标和蛇头坐标的重合
void EatFood()
{
	if (snake.scr[0].x == food.fcr.x&&snake.scr[0].y == food.fcr.y)//食物的坐标和蛇头坐标的重合
	{
		//节数增加
		snake.n++;
		food.flag = 0;
	}
}

//判断游戏退出
void GameBreak()
{
	//撞墙 
	if (snake.scr[0].y < -1 || snake.scr[0].y>471 || snake.scr[0].x < -1 || snake.scr[0].x>631)
	{
		//退出
		GameOver();
	}

	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.scr[0].x == snake.scr[i].x&&snake.scr[0].y == snake.scr[i].y)
		{
			//退出
			GameOver();
		}
	}

}

void GameOver()
{
	cleardevice();
	settextcolor(GREEN);
	settextstyle(50, 0, L"黑体");
	outtextxy(200, 200, L"game over");
	Sleep(2000);
	exit(0);
}