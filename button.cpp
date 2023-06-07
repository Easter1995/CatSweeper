#include "data.h"

// “鼠标操作”相关函数
// 鼠标消息
// 支持如下消息：
//  WM_MOUSEMOVE  鼠标移动
//  WM_MOUSEWHEEL  鼠标滚轮拨动
//  WM_LBUTTONDOWN  左键按下     用到的
//  WM_LBUTTONUP  左键弹起
//  WM_LBUTTONDBLCLK 左键双击
//  WM_MBUTTONDOWN  中键按下
//  WM_MBUTTONUP  中键弹起
//  WM_MBUTTONDBLCLK 中键双击
//  WM_RBUTTONDOWN  右键按下     用到的
//  WM_RBUTTONUP  右键弹起
//  WM_RBUTTONDBLCLK 右键双击

void levelbutton()
{

	initgraph(1000, 700);//生成初始图形化窗口
	setbkcolor(RGB(255, 255, 255));//设置背景颜色
	cleardevice();//清空窗口
	IMAGE img;//声明图片
	loadimage(&img, "./button/welcome.JPG", 1000, 700);//加载图片
	putimage(0, 0, &img);//显示图片在面板上
	loadimage(&img, "./button/newbutton1.JPG");//加载图片
	putimage(0, 550, &img);//显示图片在面板上
	loadimage(&img, "./button/newbutton2.JPG");
	putimage(250, 550, &img);
	loadimage(&img, "./button/newbutton3.JPG");
	putimage(500, 550, &img);
	loadimage(&img, "./button/newbutton4.JPG");
	putimage(750, 550, &img);
	while (mode != 1 && mode != 2 && mode != 3 && mode != 4)
	{
		MOUSEMSG msg;//声明鼠标信息
		if (MouseHit())
		{
			msg = GetMouseMsg();//将鼠标信息赋值
			int mouseX = msg.x;//得到鼠标所点位置横坐标
			int mouseY = msg.y;//纵坐标

			int imageLX = 0;//图片左侧坐标
			int imageUY = 550;//图片上侧坐标
			int imageRX = img.getwidth();//图片宽
			int imageDY = img.getheight();//图片高
			switch (msg.uMsg)
			{
			case WM_LBUTTONUP:
				if (mouseX >= 0 && mouseX <= 250 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					mode = 1;//如果点击到低级
				else if (mouseX >= 250 && mouseX <= 500 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					mode = 2;//如果点击到中级
				else if (mouseX >= 500 && mouseX <= 750 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					mode = 3;//如果点击到高级
				else if (mouseX >= 750 && mouseX <= 1000 && mouseY >= imageUY && mouseY <= imageUY + imageDY)
					mode = 4;//如果点击到自定义
				break;
			case WM_LBUTTONDOWN:
				loadimage(&img, "./button/newbuttonclicked.JPG");//点击后特效
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
			closegraph();//关闭窗口
	}
	return;
}
void restartbutton()
{
	IMAGE img;
	loadimage(&img, "./button/restartbutton.JPG");//加载按钮
	putimage(column * PIC_SIZE / 2 - 70, 0, &img);//显示按钮图片
	return;
}
bool restart(ExMessage m)
{
	int flag = 0;
	if (m.message == WM_LBUTTONDOWN && m.x > column * PIC_SIZE / 2 - 70 && m.x < column * PIC_SIZE / 2 + 60)
		flag = 1;//如果点击了重新开始
	return flag;
}
bool stop(ExMessage m)
{
	int flag = 0;
	if (m.message == WM_LBUTTONDOWN && m.x > column / 10 * PIC_SIZE + 65 && m.x < column / 10 * PIC_SIZE + 95)
		flag = 1;//如果点击了暂停
	return flag;
}
void custom()
{
begin:
	int flag = 0, i = 0, j = 0, k = 0, judge = 0;
	row = 0; column = 0; mineNum = 0;
	initgraph(400, 400);
	char s[10];
	InputBox(s, 10, "Rows? ");//弹出输入框，并输入行数
	row = atoi(s);
	InputBox(s, 10, "Colums? ");//弹出输入框，并输入列数
	column = atoi(s);
	InputBox(s, 10, "Number of mines? ");//弹出输入框，并输入雷数
	mineNum = atoi(s);
	if (row < 9 || column < 9 || row>24 || column>30 || mineNum > row * column * 9 / 10 || mineNum < 10)
	{
		initgraph(400, 400, SHOWCONSOLE);//弹出提示框
		MessageBox(GetHWnd(), "The input is invalid, please try again", "Notice!", MB_OK);//提示输入不合法
		goto begin;
	}
	closegraph();
	return;
}
