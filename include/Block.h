#pragma once

#include<graphics.h>
#include<ctime>
#include<stdlib.h>

#include"BaseBlock.h"

class Block :public BaseBlock
{
private:
	int Left, Top;//��Ϸ����ͼ�е�����Ļ��߽硢�ϱ߽����
	int x[4], y[4];//����Ԫ���������
	int type;//��������

public:
	Block();
	~Block();

	void SetType(int a);//���÷�������
	int GetType();//��÷���������ڽ��ȼ�¼

	static void SetTheme(int theme);

	void SetBaseBlock();//�������ͼƬ�����͵Ȼ�������

	int GetRow(int i);
	int GetCol(int i);

	//��ʼ���������ͼ���꣬���������
	virtual void SetPro(int type);

	//��Ϣ���ã������ͼ���굫���������ͣ����ڳ��򷵻�ʱ�ظ�
	void SetPro(char,int [10],int [10]);

	void XBack();//�����߿�������ظ�
	void YBack(char );//��תʱ�����߿�������ظ�

	int GetLeft();
	int GetTop();

	int GetBaseRow(int i);//����Tetris�д��׵��жϺ�Fix��¼״̬
	int GetColToRow(int i);//����Tetris�д��׵��жϺ�Fix��¼״̬

	void Eturn();//��ת����

	void PrintBlock();//��ӡ����

	void Down();//���ķ����������½�
	void MoveLeft();
	void MoveRight();
};