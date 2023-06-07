#include "data.h"

int pos[8][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };// �˸���λ

void sweep1(int x, int y)// ����1
{
	int i, cnt = 0;
	// ������ǰ������Χ��û�е���
	
	if (x >= 1 && x <= row && y >= 1 && y <= column)
	{
		if (status != STATUS9)
			steps++;
		if (userMap[x][y] == '.' || userMap[x][y] == '?') {
			if (originMap[x][y] == '*')//����
			{
				if (steps == 1)//��һ�β�������
				{
					steps = 0;status = 1;opened = 0;
					gameInit();//�������ɵ�ͼ
					sweep1(x, y);//�û�����Ļ���(x,y)
				}
				else
				{
					status = STATUS5;//ʧ��
					return;
				}
			}
			else
			{
				opened += 1;
				for (i = 0; i < 8; i++) // ����8����λ
				{
					if (x + pos[i][0] >= 1 && x + pos[i][0] <= row && y + pos[i][1] >= 1 && y + pos[i][1] <= column)
					{
						if (originMap[x + pos[i][0]][y + pos[i][1]] == '*')
							cnt++;
					}
				}
				if (cnt > 0) // ����
				{
					userMap[x][y] = '0' + cnt;
				}
				else // û����
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
// ��ǵ��ס�������⡢ȡ�����-->���Ӳ�Ӧ���Ǵ��˵�

void sweep2(int x, int y)// ����
{
	
	if (x >= 1 && x <= row && y >= 1 && y <= column)
	{
		steps++;
		if (userMap[x][y] == '.')//���û�򿪵ĸ���
		{
			userMap[x][y] = '!';
			mineNum--;
			status = STATUS2;
		}
	}
	return;
}

void sweep3(int x, int y)// ����->�ʺ�
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

void sweep4(int x, int y)// ȡ���ʺ�
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

void sweep9(int x, int y)// �ݹ�չ��
{
	int cnt = 0; // ͳ�ƴ�ʱ�û�����˶��ٸ�����
	int i;
	if (x >= 1 && x <= row && y >= 1 && y <= column)
	{
		//˫������ֻ�ܶԴ��˵ĸ���ִ��
		if (userMap[x][y] != '.' && userMap[x][y] != '!' && userMap[x][y] != '?')
		{
			//�ж��Ƿ���ϴ򿪸��ӵ�Ҫ��
			for (i = 0; i < 8; i++)
			{
				if (x + pos[i][0] >= 1 && x + pos[i][0] <= row && y + pos[i][1] >= 1 && y + pos[i][1] <= column)
				{
					if (userMap[x + pos[i][0]][y + pos[i][1]] == '!') // ͳ���û�����˶��ٸ���
						cnt++;
				}
			}
			//���ϴ򿪸��ӵ�Ҫ��
			if (cnt + '0' == userMap[x][y]) // ����Ҫ��
			{
				//�ж���Χ����������û���ף��������ֱ�ӽ���
				for (i = 0; i < 8; i++)
				{
					if (x + pos[i][0] >= 1 && x + pos[i][0] <= row && y + pos[i][1] >= 1 && y + pos[i][1] <= column)
					{
						if (originMap[x + pos[i][0]][y + pos[i][1]] != '*' && userMap[x + pos[i][0]][y + pos[i][1]] == '!')
							userMap[x + pos[i][0]][y + pos[i][1]] = 'x';// ��Ǵ���
						else if (originMap[x + pos[i][0]][y + pos[i][1]] == '*' && userMap[x + pos[i][0]][y + pos[i][1]] != '!')
						{
							// ע�⣡�����Χ�ĸ��ӱ�Ǵ��ˣ����˵��ף���Ϸֱ�ӽ�����������������
							status = STATUS5;
						}
					}
				}
				if (status == STATUS5)
				{
					return;
				}
				//���û���ף��򿪸���
				for (i = 0; i < 8; i++)
				{
					if (x + pos[i][0] >= 1 && x + pos[i][0] <= row && y + pos[i][1] >= 1 && y + pos[i][1] <= column)
					{
						if (userMap[x + pos[i][0]][y + pos[i][1]] != '!')
							sweep1(x + pos[i][0], y + pos[i][1]); // ��
					}
				}
			}
		}
	}
	return;
}

void sweep0(ExMessage m,int click)//��ȡ���룬״̬ת��
{
	int x = m.y / PIC_SIZE;
	int y = m.x / PIC_SIZE + 1;
	switch (click) 
	{
		case 0://���
			sweep1(x, y);
			break;
		case 1://�Ҽ�
			if (userMap[x][y] == '.')
				sweep2(x, y);
			else if (userMap[x][y] == '!')//2�Ļ�����
				sweep3(x, y);
			else if (userMap[x][y] == '?')//3�Ļ�����
				sweep4(x, y);
			break;
		case 2://˫��
			sweep9(x, y);
			break;
		default:
			break;
	}
}