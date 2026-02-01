#pragma once

#include<graphics.h>

using namespace std;

class BaseBlock
{
public:
	static int BlockSize;//����С�����С
	static int theme;//����
protected:
	IMAGE BlockBase[7];//7�ֻ�ԪͼƬ
	IMAGE BlockRes;//����ͼƬ�������и��7�ֻ�ԪͼƬ��
	int BaseRow[4];//���������Ͷ�Ӧ��Ч����
	int ColToRow[4];//������Ӧ��Ч����

public:
	BaseBlock();
	~BaseBlock();
	void BlockReload();

	virtual void SetPro(int type);//��������
};