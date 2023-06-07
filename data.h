#pragma once
#include <stdio.h>
#include <time.h> // ���ڲ��������
#include <graphics.h>
#include <easyx.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
using namespace std;
// ����ģʽ
#define ROW1 9
#define COLUMN1 9
#define MINE1 10
// �м�ģʽ
#define ROW2 16
#define COLUMN2 16
#define MINE2 40
// �߼�ģʽ
#define ROW3 16
#define COLUMN3 30
#define MINE3 99
// ״̬
#define STATUS1 1 // ����1������״̬
#define STATUS2 2 // ����2������״̬
#define STATUS3 3 // ����3������״̬
#define STATUS4 4 // ����4������״̬
#define STATUS9 9 // ����9������״̬
#define STATUS5 5 // ɨ��ʧ�ܺ��״̬
#define STATUS6 6 // ɨ�׳ɹ����״̬

#define PIC_SIZE 40 // ɨ�׵�ͼ��ÿһ��Ĵ�С
#define MINE_PIC 10 // ͼƬ��������ͼƬ��λ��
#define FLAG_PIC 11 // ͼƬ����������ͼƬ��λ��
#define Q_PIC 12 // ͼƬ�������ʺ�ͼƬ��λ��
#define X_PIC 16 // ͼƬ�����д���ͼƬ��λ��
// ȫ�ֱ���
extern int mode;	// �û�ѡ���ģʽ
extern int func;	// �û�ѡ��Ĳ�������
extern int steps;	// �û��Ĳ�����
extern int mineNum; // ������ʾ��ʣ���������
extern int row;		// ��
extern int column;	// ��
extern int status;	// ��ʾ��ǰ״̬
extern int mines;	// ���ڴ洢��������
extern int opened;	// ��ʾ�û��Ѿ������ĸ�������
extern int statement;// ��ʾ��Ϸ����״̬
extern int sleepTime; // ��ʾ��ͣʱ��
// ȫ�����ݽṹ
// ��ͼ
extern char** originMap; // ��ʾԭ����ɨ�׵�ͼ
extern char** userMap;	 // ��ʾ�����û���ǹ����ɨ�׵�ͼ������������ĵ�ͼ
// ��������
void dataInit(); // ��ʼ���������ڴ�
void gameInit(); // ��������ɡ�������������ͨ����
void drawMap(); // ���Ƶ�ͼ
void levelbutton(); //��ť������ѡ��ģʽ
void sweep0(ExMessage m, int click);//����ģʽ
void sweep1(int x, int y);//����
void sweep2(int x, int y);//��ǵ���
void sweep3(int x, int y);//�ʺ�
void sweep4(int x, int y);//ȡ�����
void sweep9(int x, int y);//˫��
void sand(); //��ʱ��
void clean();//�ͷ��ڴ�
void judge();//�ж�ʤ��
void restartbutton();//�������¿�ʼ�İ�ť
bool restart(ExMessage m); //�ж��Ƿ������¿�ʼ
bool stop(ExMessage m);//�ж��Ƿ�����ͣ
void custom(); // �Զ���
void picLoad();// ����ͼƬ
