#include "data.h"

int pos[8][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };// 八个方位

void sweep1(int x, int y)// 操作1
{
	int i, cnt = 0;
	// 搜索当前坐标周围有没有地雷
	
	if (x >= 1 && x <= row && y >= 1 && y <= column)
	{
		if (status != STATUS9)
			steps++;
		if (userMap[x][y] == '.' || userMap[x][y] == '?') {
			if (originMap[x][y] == '*')//触雷
			{
				if (steps == 1)//第一次操作触雷
				{
					steps = 0;status = 1;opened = 0;
					gameInit();//重新生成地图
					sweep1(x, y);//用户点击的还是(x,y)
				}
				else
				{
					status = STATUS5;//失败
					return;
				}
			}
			else
			{
				opened += 1;
				for (i = 0; i < 8; i++) // 搜索8个方位
				{
					if (x + pos[i][0] >= 1 && x + pos[i][0] <= row && y + pos[i][1] >= 1 && y + pos[i][1] <= column)
					{
						if (originMap[x + pos[i][0]][y + pos[i][1]] == '*')
							cnt++;
					}
				}
				if (cnt > 0) // 有雷
				{
					userMap[x][y] = '0' + cnt;
				}
				else // 没有雷
				{
					userMap[x][y] = '0';
					for (i = 0; i < 8; i++)
					{
						if (x + pos[i][0] >= 1 && x + pos[i][0] <= row && y + pos[i][1] >= 1 && y + pos[i][1] <= column)
						{
							if (userMap[x + pos[i][0]][y + pos[i][1]] == '.' || userMap[x + pos[i][0]][y + pos[i][1]] == '?')
								sweep1(x + pos[i][0], y + pos[i][1]);
						}
					}
				}
			}
		}
	}
	return;
}
// 标记地雷、标记问题、取消标记-->格子不应该是打开了的

void sweep2(int x, int y)// 旗子
{
	
	if (x >= 1 && x <= row && y >= 1 && y <= column)
	{
		steps++;
		if (userMap[x][y] == '.')//标记没打开的格子
		{
			userMap[x][y] = '!';
			mineNum--;
			status = STATUS2;
		}
	}
	return;
}

void sweep3(int x, int y)// 旗子->问号
{
	
	if (x >= 1 && x <= row && y >= 1 && y <= column)
	{
		steps++;
		if (userMap[x][y] == '!')
		{
			mineNum++;
			userMap[x][y] = '?';
			status = STATUS3;
		}
	}
	return;
}

void sweep4(int x, int y)// 取消问号
{
	
	if (x >= 1 && x <= row && y >= 1 && y <= column)
	{
		steps++;
		if (userMap[x][y] == '?')
		{
			userMap[x][y] = '.';
			status = STATUS4;
		}
	}
	return;
}

void sweep9(int x, int y)// 递归展开
{
	int cnt = 0; // 统计此时用户标记了多少个格子
	int i;
	if (x >= 1 && x <= row && y >= 1 && y <= column)
	{
		//双击操作只能对打开了的格子执行
		if (userMap[x][y] != '.' && userMap[x][y] != '!' && userMap[x][y] != '?')
		{
			//判断是否符合打开格子的要求
			for (i = 0; i < 8; i++)
			{
				if (x + pos[i][0] >= 1 && x + pos[i][0] <= row && y + pos[i][1] >= 1 && y + pos[i][1] <= column)
				{
					if (userMap[x + pos[i][0]][y + pos[i][1]] == '!') // 统计用户标记了多少格子
						cnt++;
				}
			}
			//符合打开格子的要求
			if (cnt + '0' == userMap[x][y]) // 符合要求
			{
				//判断周围格子里面有没有雷，如果有雷直接结束
				for (i = 0; i < 8; i++)
				{
					if (x + pos[i][0] >= 1 && x + pos[i][0] <= row && y + pos[i][1] >= 1 && y + pos[i][1] <= column)
					{
						if (originMap[x + pos[i][0]][y + pos[i][1]] != '*' && userMap[x + pos[i][0]][y + pos[i][1]] == '!')
							userMap[x + pos[i][0]][y + pos[i][1]] = 'x';// 标记错了
						else if (originMap[x + pos[i][0]][y + pos[i][1]] == '*' && userMap[x + pos[i][0]][y + pos[i][1]] != '!')
						{
							// 注意！如果周围的格子标记错了，打开了地雷，游戏直接结束，不打开其他格子
							status = STATUS5;
						}
					}
				}
				if (status == STATUS5)
				{
					return;
				}
				//如果没有雷，打开格子
				for (i = 0; i < 8; i++)
				{
					if (x + pos[i][0] >= 1 && x + pos[i][0] <= row && y + pos[i][1] >= 1 && y + pos[i][1] <= column)
					{
						if (userMap[x + pos[i][0]][y + pos[i][1]] != '!')
							sweep1(x + pos[i][0], y + pos[i][1]); // 打开
					}
				}
			}
		}
	}
	return;
}

void sweep0(ExMessage m,int click)//获取输入，状态转移
{
	int x = m.y / PIC_SIZE;
	int y = m.x / PIC_SIZE + 1;
	switch (click) 
	{
		case 0://左键
			sweep1(x, y);
			break;
		case 1://右键
			if (userMap[x][y] == '.')
				sweep2(x, y);
			else if (userMap[x][y] == '!')//2的基础上
				sweep3(x, y);
			else if (userMap[x][y] == '?')//3的基础上
				sweep4(x, y);
			break;
		case 2://双击
			sweep9(x, y);
			break;
		default:
			break;
	}
}