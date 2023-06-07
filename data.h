#pragma once
#include <stdio.h>
#include <time.h> // 用于产生随机数
#include <graphics.h>
#include <easyx.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
using namespace std;
// 初级模式
#define ROW1 9
#define COLUMN1 9
#define MINE1 10
// 中级模式
#define ROW2 16
#define COLUMN2 16
#define MINE2 40
// 高级模式
#define ROW3 16
#define COLUMN3 30
#define MINE3 99
// 状态
#define STATUS1 1 // 操作1结束的状态
#define STATUS2 2 // 操作2结束的状态
#define STATUS3 3 // 操作3结束的状态
#define STATUS4 4 // 操作4结束的状态
#define STATUS9 9 // 操作9结束的状态
#define STATUS5 5 // 扫雷失败后的状态
#define STATUS6 6 // 扫雷成功后的状态

#define PIC_SIZE 40 // 扫雷地图上每一格的大小
#define MINE_PIC 10 // 图片数组中雷图片的位置
#define FLAG_PIC 11 // 图片数组中旗子图片的位置
#define Q_PIC 12 // 图片数组中问号图片的位置
#define X_PIC 16 // 图片数组中错误图片的位置
// 全局变量
extern int mode;	// 用户选择的模式
extern int func;	// 用户选择的操作类型
extern int steps;	// 用户的操作数
extern int mineNum; // 用于显示的剩余地雷数量
extern int row;		// 行
extern int column;	// 列
extern int status;	// 表示当前状态
extern int mines;	// 用于存储地雷数量
extern int opened;	// 表示用户已经翻开的格子数量
extern int statement;// 表示游戏进行状态
extern int sleepTime; // 表示暂停时长
// 全局数据结构
// 地图
extern char** originMap; // 表示原本的扫雷地图
extern char** userMap;	 // 表示经过用户标记过后的扫雷地图，是用来输出的地图
// 函数声明
void dataInit(); // 初始化、分配内存
void gameInit(); // 随机数生成、布置雷区和普通区域
void drawMap(); // 绘制地图
void levelbutton(); //按钮，用来选择模式
void sweep0(ExMessage m, int click);//分配模式
void sweep1(int x, int y);//单击
void sweep2(int x, int y);//标记地雷
void sweep3(int x, int y);//问号
void sweep4(int x, int y);//取消标记
void sweep9(int x, int y);//双击
void sand(); //计时器
void clean();//释放内存
void judge();//判断胜负
void restartbutton();//布置重新开始的按钮
bool restart(ExMessage m); //判断是否点击重新开始
bool stop(ExMessage m);//判断是否点击暂停
void custom(); // 自定义
void picLoad();// 加载图片
