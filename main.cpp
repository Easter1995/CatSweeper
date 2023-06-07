#include "data.h"
int row;
int column;
int mode;
int steps;
int status;
int mineNum;
int opened;
int mines;
int statement;//0��ʾ������ͣ��1��ʾ������ͣ
int flag;//�������Ƿ��Ѿ�������Ϸ��flag=0��ʾ��Ϸû�н�����flag=1��ʾ��Ϸ�Ѿ�����
char** originMap;
char** userMap;
clock_t start_time;
clock_t end_time;
int time_1;//��ʾ��ʱ��
int sleepTime;//��ͣ��ʱ��
clock_t time_stop1;//�����ͣ��ʱ��
clock_t time_stop2;//�ڶ��ε����ͣ��ʱ��
char str[10];//���ʱ��
IMAGE img[20];//�������Ҫ������ͼƬ
int main()
{
begin://��������ִ��
	steps = 0; status = 1; opened = 0, statement = 1;sleepTime = 0;
	ExMessage msg;
	dataInit();//���ݳ�ʼ��
	gameInit();//��������
	picLoad(); //����ͼƬ
	initgraph(column * PIC_SIZE, (row + 1) * PIC_SIZE);//��ʼ������
	BeginBatchDraw();//��ʼ������ͼ
	start_time = clock();
	while (true)
	{
		cleardevice();
		drawMap(); // ����ͼ
		sand(); // ����ʱ
		FlushBatchDraw(); // ��ֹ����
		if (status == 5 || status == 6)//����һ��or�˳���Ϸ
		{
			int ret;
			ret = MessageBox(GetHWnd(), "����һ�֣�\n������ǡ�����һ��\n��������˳���Ϸ", "notice", MB_YESNO);
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
		if (MouseHit())//������
		{
			msg = getmessage(EX_MOUSE);
			if (msg.y <= 30 && restart(msg))//��������¿�ʼ
			{
				clean();
				goto begin;
			}
			else if (msg.y <= 30 && stop(msg))//���������ͣ��
			{
				if (statement == 1)//���������ͣ״̬
				{
					time_stop1 = clock();
					statement = 0;//������ͣ״̬
				}
				else
				{
					time_stop2 = clock();
					statement = 1;//�˳���ͣ״̬
					sleepTime += (int)(double)(time_stop2 - time_stop1) / CLOCKS_PER_SEC;
				}
			}
			else
			{
				if (status != STATUS5 && status != STATUS6 && statement == 1)
				{
					bool leftButton = false;    // ����Ƿ���
					bool rightButton = false;   // �Ҽ��Ƿ���
					bool bothButton = false;    // ���Ҽ��Ƿ�ͬʱ����

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
		judge();//�ж���Ӯ
	}
}

void dataInit() // ��ʼ���������ڴ�
{
	int i;
	// ȫ�ֱ�����ֵ
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

	// �����ڴ�
	originMap = (char**)malloc(sizeof(char*) * (row + 2));
	userMap = (char**)malloc(sizeof(char*) * (row + 2));
	for (i = 0; i <= row + 1; i++)
	{
		originMap[i] = (char*)malloc(sizeof(char) * (column + 2));
		userMap[i] = (char*)malloc(sizeof(char) * (column + 2));
	}
	return;
}

void gameInit() // ��������ɡ�������������ͨ����
{
	int i, j;
	opened = 0; flag = 0;
	//���������
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
	//�����׵ĵط�
	for (i = 1; i <= mineNum; )
	{
		x = rand() % row + 1;//x����[1,row]
		y = rand() % column + 1;//y����[1,column]
		if (originMap[x][y] != '*')//��֤���ظ�
		{
			originMap[x][y] = '*';
			i++;
		}
	}
	//����ͨ�ĸ���
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= column; j++)
		{
			if (originMap[i][j] != '*')
			{
				originMap[i][j] = '.';
			}
			userMap[i][j] = '.';
			//printf("%c", originMap[i][j]);//������
		}
		//printf("\n");//������
	}
}

void picLoad()
{
	int i;
	//����ͼƬ
	char temp[20] = { 0 };
	for (i = 0; i < 19; i++)
	{
		sprintf_s(temp, "./pics/%d.JPG", i);
		loadimage(img + i, temp, PIC_SIZE, PIC_SIZE);
	}
	return;
}

void drawMap() // ���Ƶ�ͼ
{
	//��һ��
	int i, j;
	char number[5];
	for (i = 0; i < column; i++)
	{
		if (i == column / 10)//ɳ©
			putimage(i * PIC_SIZE, 0, img + 14);
		else if (i == column - (column / 10) - 2)//ը����
			putimage(i * PIC_SIZE, 0, img + 15);
		else
			putimage(i * PIC_SIZE, 0, img + 13);
	}
	if (statement == 1)
		putimage(column / 10 * PIC_SIZE + 65, 0, img + 17);
	else 
		putimage(column / 10 * PIC_SIZE + 65, 0, img + 18);
	restartbutton();
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ�����ɫΪ͸��
	settextstyle(20, 0, "����");
	sprintf_s(number, "x%d", mineNum);
	outtextxy((column - (column / 10) - 1) * PIC_SIZE, 10, number);
	for (i = 1; i <= row; i++)//i��
	{
		for (j = 1; j <= column; j++)//j��
		{
			if (userMap[i][j] == '.')//δ�����ĸ���
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + 9);
			}
			else if (userMap[i][j] == '*')//��
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + MINE_PIC);
			}
			else if (userMap[i][j] >= '1' && userMap[i][j] <= '8')//�����ֵĸ���
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + (userMap[i][j] - '0'));
			}
			else if (userMap[i][j] == '0')//�������ֵķ����ĸ���
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + 0);
			}
			else if (userMap[i][j] == '!')//����
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + FLAG_PIC);
			}
			else if (userMap[i][j] == '?')//�ʺ�
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + Q_PIC);
			}
			else if (userMap[i][j] == 'x')//����
			{
				putimage((j - 1) * PIC_SIZE, i * PIC_SIZE, img + X_PIC);
			}
		}
	}
	return;
}

void sand()//��ʱ
{
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ�����ɫΪ͸��
	end_time = clock();
	if (statement == 1)
		time_1 = (int)(double)(end_time - start_time) / CLOCKS_PER_SEC - sleepTime;
	settextstyle(20, 0, "����");
	if (status != STATUS5 && status != STATUS6)
		sprintf_s(str, "%ds", time_1);
	outtextxy((column / 10 + 1) * PIC_SIZE, 10, str);
	return;
}

void clean()//�ͷ��ڴ�
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

void judge() //�ж���ϷӮ�˻������ˣ�Ȼ�������ȫ�����׷ֲ��ĵ�ͼ
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
	//flag���ڱ�֤������ֻ����һ��
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