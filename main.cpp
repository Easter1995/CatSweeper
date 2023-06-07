#include "data.h"
int row;
int column;
int mode;
int steps;
int status;
int mineNum;
int opened;
int mines;
int statement;//0表示正在暂停，1表示结束暂停
int flag;//用来看是否已经结束游戏，flag=0表示游戏没有结束，flag=1表示游戏已经结束
char** originMap;
char** userMap;
clock_t start_time;
clock_t end_time;
int time_1;//显示的时间
int sleepTime;//暂停的时间
clock_t time_stop1;//点击暂停的时间
clock_t time_stop2;//第二次点击暂停的时间
char str[10];//输出时间
IMAGE img[20];//存放所需要的所有图片
int main()
{
begin://函数重新执行
	steps = 0; status = 1; opened = 0, statement = 1;sleepTime = 0;
	ExMessage msg;
	dataInit();//数据初始化
	gameInit();//布置雷区
	picLoad(); //加载图片
	initgraph(column * PIC_SIZE, (row + 1) * PIC_SIZE);//初始化界面
	BeginBatchDraw();//开始批量绘图
	start_time = clock();
	while (true)
	{
		cleardevice();
		drawMap(); // 画地图
		sand(); // 画计时
		FlushBatchDraw(); // 防止屏闪
		if (status == 5 || status == 6)//重来一局or退出游戏
		{
			int ret;
			ret = MessageBox(GetHWnd(), "再来一局？\n点击“是”再玩一局\n点击“否”退出游戏", "notice", MB_YESNO);
			if (ret == IDYES)
			{
				clean();
				goto begin;
			}
			else
			{
				EndBatchDraw();
				closegraph;
				clean();
				return 0;
			}
		}
		if (MouseHit())//鼠标操作
		{
			msg = getmessage(EX_MOUSE);
			if (msg.y <= 30 && restart(msg))//点击了重新开始
			{
				clean();
				goto begin;
			}
			else if (msg.y <= 30 && stop(msg))//点击到了暂停键
			{
				if (statement == 1)//如果不是暂停状态
				{
					time_stop1 = clock();
					statement = 0;//进入暂停状态
				}
				else
				{
					time_stop2 = clock();
					statement = 1;//退出暂停状态
					sleepTime += (int)(double)(time_stop2 - time_stop1) / CLOCKS_PER_SEC;
				}
			}
			else
			{
				if (status != STATUS5 && status != STATUS6 && statement == 1)
				{
					bool leftButton = false;    // 左键是否按下
					bool rightButton = false;   // 右键是否按下
					bool bothButton = false;    // 左右键是否同时按下

					if (msg.message == WM_LBUTTONDOWN)
					{
						leftButton = true;
						Sleep(200);
						msg = getmessage(EX_MOUSE);
						if (msg.message == WM_RBUTTONDOWN)
						{
							bothButton = true;
						}
					}
					else if (msg.message == WM_RBUTTONDOWN)
					{
						rightButton = true;
						Sleep(100);
						msg = getmessage(EX_MOUSE);
						if (msg.message == WM_LBUTTONDOWN)
						{
							bothButton = true;
						}
					}
					if (bothButton)
						sweep0(msg, 2);
					else if (leftButton)
						sweep0(msg, 0);
					else if (rightButton)
						sweep0(msg, 1);
				}
			}
		}
		judge();//判断输赢
	}
}

void dataInit() // 初始化、分配内存
{
	int i;
	// 全局变量赋值
	levelbutton();
	switch (mode)
	{
	case 1:
		row = ROW1;
		column = COLUMN1;
		mineNum = MINE1;
		break;
	case 2:
		row = ROW2;
		column = COLUMN2;
		mineNum = MINE2;
		break;
	case 3:
		row = ROW3;
		column = COLUMN3;
		mineNum = MINE3;
		break;
	case 4:
		custom();
		break;
	}
	mines = mineNum;

	// 分配内存
	originMap = (char**)malloc(sizeof(char*) * (row + 2));
	userMap = (char**)malloc(sizeof(char*) * (row + 2));
	for (i = 0; i <= row + 1; i++)
	{
		originMap[i] = (char*)malloc(sizeof(char) * (column + 2));
		userMap[i] = (char*)malloc(sizeof(char) * (column + 2));
	}
	return;
}

void gameInit() // 随机数生成、布置雷区和普通区域
{
	int i, j;
	opened = 0; flag = 0;
	//生成随机数
	srand((unsigned)time(NULL));
	int x, y;
	for ( i = 1; i <= row; i++)
	{
		for ( j = 1; j <= column; j++)
		{
			originMap[i][j] = 0;
			userMap[i][j] = 0;
		}
	}
	//存有雷的地方
	for (i = 1; i <= mineNum; )
	{
		x = rand() % row + 1;//x属于[1,row]
		y = rand() % column + 1;//y属于[1,column]
		if (originMap[x][y] != '*')//保证不重复
		{
			originMap[x][y] = '*';
			i++;
		}
	}
	//存普通的格子
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= column; j++)
		{
			if (originMap[i][j] != '*')
			{
				originMap[i][j] = '.';
			}
			userMap[i][j] = '.';
			//printf("%c", originMap[i][j]);//调试用
		}
		//printf("\n");//调试用
	}
}

void picLoad()
{
	int i;
	//加载图片
	char temp[20] = { 0 };
	for (i = 0; i < 19; i++)
	{
		sprintf_s(temp, "./pics/%d.JPG", i);
		loadimage(img + i, temp, PIC_SIZE, PIC_SIZE);
	}
	return;
}

void drawMap() // 绘制地图
{
	//第一排
	int i, j;
	char number[5];
	for (i = 0; i < column; i++)
	{
		if (i == column / 10)//沙漏
			putimage(i * PIC_SIZE, 0, img + 14);
		else if (i == column - (column / 10) - 2)//炸弹数
			putimage(i * PIC_SIZE, 0, img + 15);
		else
			putimage(i * PIC_SIZE, 0, img + 13);
	}
	if (statement == 1)
		putimage(column / 10 * PIC_SIZE + 65, 0, img + 17);
	else 
		putimage(column / 10 * PIC_SIZE + 65, 0, img + 18);
	restartbutton();
	settextcolor(BLACK);//设置字体颜色
	setbkmode(TRANSPARENT);//设置背景颜色为透明
	settextstyle(20, 0, "黑体");
	sprintf_s(number, "x%d", mineNum);
	outtextxy((column - (column / 10) - 1) * PIC_SIZE, 10, number);
	for (i = 1; i <= row; i++)//i行
	{
		for (j = 1; j <= column; j++)//j列
		{
			if (userMap[i][j] == '.')//未翻开的格子
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + 9);
			}
			else if (userMap[i][j] == '*')//雷
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + MINE_PIC);
			}
			else if (userMap[i][j] >= '1' && userMap[i][j] <= '8')//带数字的格子
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + (userMap[i][j] - '0'));
			}
			else if (userMap[i][j] == '0')//不带数字的翻开的格子
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + 0);
			}
			else if (userMap[i][j] == '!')//旗子
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + FLAG_PIC);
			}
			else if (userMap[i][j] == '?')//问号
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + Q_PIC);
			}
			else if (userMap[i][j] == 'x')//错误
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + X_PIC);
			}
		}
	}
	return;
}

void sand()//计时
{
	settextcolor(BLACK);//设置字体颜色
	setbkmode(TRANSPARENT);//设置背景颜色为透明
	end_time = clock();
	if (statement == 1)
		time_1 = (int)(double)(end_time - start_time) / CLOCKS_PER_SEC - sleepTime;
	settextstyle(20, 0, "黑体");
	if (status != STATUS5 && status != STATUS6)
		sprintf_s(str, "%ds", time_1);
	outtextxy((column / 10 + 1) * PIC_SIZE, 10, str);
	return;
}

void clean()//释放内存
{
	int i, j;
	for (i = 0; i < row + 2; i++)
	{
		free(originMap[i]);
		free(userMap[i]);
	}
	free(originMap);
	free(userMap);
	return;
}

void judge() //判断游戏赢了还是输了，然后输出有全部地雷分布的地图
{
	int i, j;
	if (opened == row * column - mines && status != STATUS5)
		status = STATUS6;
	if (status == STATUS6 || status == STATUS5)
	{
		for (i = 1; i <= row; i++)
		{
			for (j = 1; j <= column; j++)
			{
				if (originMap[i][j] == '*')
				{
					userMap[i][j] = '*';
				}
			}
		}
	}
	//flag用于保证弹出框只出现一次
	if (status == STATUS5 && flag != 1)
	{
		flag = 1;
		MessageBox(GetHWnd(), "OH Nooooo! YOU LOSE...", ":(", MB_OK);
	}
	if (status == STATUS6 && flag != 1)
	{
		flag = 1;
		MessageBox(GetHWnd(), "CONGRATULATIONS! YOU WIN!", ":)", MB_OK);
	}
	drawMap();
	return;
}