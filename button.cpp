#include "data.h"

// ������������غ���
// �����Ϣ
// ֧��������Ϣ��
//  WM_MOUSEMOVE  ����ƶ�
//  WM_MOUSEWHEEL  �����ֲ���
//  WM_LBUTTONDOWN  �������     �õ���
//  WM_LBUTTONUP  �������
//  WM_LBUTTONDBLCLK ���˫��
//  WM_MBUTTONDOWN  �м�����
//  WM_MBUTTONUP  �м�����
//  WM_MBUTTONDBLCLK �м�˫��
//  WM_RBUTTONDOWN  �Ҽ�����     �õ���
//  WM_RBUTTONUP  �Ҽ�����
//  WM_RBUTTONDBLCLK �Ҽ�˫��

void levelbutton()
{

	initgraph(1000, 700);//���ɳ�ʼͼ�λ�����
	setbkcolor(RGB(255, 255, 255));//���ñ�����ɫ
	cleardevice();//��մ���
	IMAGE img;//����ͼƬ
	loadimage(&img, "./button/welcome.JPG", 1000, 700);//����ͼƬ
	putimage(0, 0, &img);//��ʾͼƬ�������
	loadimage(&img, "./button/newbutton1.JPG");//����ͼƬ
	putimage(0, 550, &img);//��ʾͼƬ�������
	loadimage(&img, "./button/newbutton2.JPG");
	putimage(250, 550, &img);
	loadimage(&img, "./button/newbutton3.JPG");
	putimage(500, 550, &img);
	loadimage(&img, "./button/newbutton4.JPG");
	putimage(750, 550, &img);
	while (mode != 1 && mode != 2 && mode != 3 && mode != 4)
	{
		MOUSEMSG msg;//���������Ϣ
		if (MouseHit())
		{
			msg = GetMouseMsg();//�������Ϣ��ֵ
			int mouseX = msg.x;//�õ��������λ�ú�����
			int mouseY = msg.y;//������

			int imageLX = 0;//ͼƬ�������
			int imageUY = 550;//ͼƬ�ϲ�����
			int imageRX = img.getwidth();//ͼƬ��
			int imageDY = img.getheight();//ͼƬ��
			switch (msg.uMsg)
			{
			case WM_LBUTTONUP:
				if (mouseX >= 0 && mouseX <= 250 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					mode = 1;//���������ͼ�
				else if (mouseX >= 250 && mouseX <= 500 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					mode = 2;//���������м�
				else if (mouseX >= 500 && mouseX <= 750 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					mode = 3;//���������߼�
				else if (mouseX >= 750 && mouseX <= 1000 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					mode = 4;//���������Զ���
				break;
			case WM_LBUTTONDOWN:
				loadimage(&img, "./button/newbuttonclicked.JPG");//�������Ч
				if (mouseX >= 0 && mouseX <= 250 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					putimage(0, 550, &img);
				else if (mouseX >= 250 && mouseX <= 500 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					putimage(250, 550, &img);
				else if (mouseX >= 500 && mouseX <= 750 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					putimage(500, 550, &img);
				else if (mouseX >= 750 && mouseX <= 1000 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					putimage(750, 550, &img);
				break;
			}

		}
		if (mode == 1 || mode == 2 || mode == 3 || mode == 4)
			closegraph();//�رմ���
	}
	return;
}
void restartbutton()
{
	IMAGE img;
	loadimage(&img, "./button/restartbutton.JPG");//���ذ�ť
	putimage(column * PIC_SIZE / 2 - 70, 0, &img);//��ʾ��ťͼƬ
	return;
}
bool restart(ExMessage m)
{
	int flag = 0;
	if (m.message == WM_LBUTTONDOWN && m.x > column * PIC_SIZE / 2 - 70 && m.x < column * PIC_SIZE / 2 + 60)
		flag = 1;//�����������¿�ʼ
	return flag;
}
bool stop(ExMessage m)
{
	int flag = 0;
	if (m.message == WM_LBUTTONDOWN && m.x > column / 10 * PIC_SIZE + 65 && m.x < column / 10 * PIC_SIZE + 95)
		flag = 1;//����������ͣ
	return flag;
}
void custom()
{
begin:
	int flag = 0, i = 0, j = 0, k = 0, judge = 0;
	row = 0; column = 0; mineNum = 0;
	initgraph(400, 400);
	char s[10];
	InputBox(s, 10, "Rows? ");//��������򣬲���������
	row = atoi(s);
	InputBox(s, 10, "Colums? ");//��������򣬲���������
	column = atoi(s);
	InputBox(s, 10, "Number of mines? ");//��������򣬲���������
	mineNum = atoi(s);
	if (row < 9 || column < 9 || row>24 || column>30 || mineNum > row * column * 9 / 10 || mineNum < 10)
	{
		initgraph(400, 400, SHOWCONSOLE);//������ʾ��
		MessageBox(GetHWnd(), "The input is invalid, please try again", "Notice!", MB_OK);//��ʾ���벻�Ϸ�
		goto begin;
	}
	closegraph();
	return;
}
