#include "Block.h"
#include<iostream>

using namespace std;

Block::Block()
{
	//游戏参数初始化
	Left = 14 * BlockSize;
	Top =  2 * BlockSize;

}

Block::~Block()
{
}

void Block::SetType(int a)
{
	this->type = a;
}

int Block::GetType()
{
	return this->type;
}

void Block::SetTheme(int theme)
{
	BaseBlock::theme = theme;
}



void Block::SetBaseBlock()
{
	switch (BaseBlock::theme)
	{
	case 0:
		loadimage(&BlockRes, "res\\Blocks\\Rain\\Blocks.jpg", BlockSize * 7, BlockSize);//加载方块图片（7方块相连）
		break;
	case 1:
		cout << 1;
	}

	//切割出7种基元图片
	SetWorkingImage(&BlockRes);
	for (int i(0); i < 7; i++)
	{
		getimage(&BlockBase[i], i * BlockSize, 0, BlockSize, BlockSize);
	}
	SetWorkingImage(NULL);
}

int Block::GetRow(int i)
{
	return BaseRow[i];
}

int Block::GetCol(int i)
{
	return ColToRow[i];
}

void Block::SetPro(int type)
{
	BaseBlock::SetPro(type);
	for (int i(0); i < 4; i++)
	{
	x[i] = Top + BaseRow[i] * BlockSize;
	y[i] = Left + ColToRow[i] * BlockSize;
	}
}

void Block::SetPro(char,int BackRow[10],int BackCol[10])
{
	for (int i(0); i < 4; i++)
	{
		BaseRow[i] = BackRow[i];
		ColToRow[i] = BackCol[i];
	}
	for (int i(0); i < 4; i++)
	{
		x[i] = Top + BaseRow[i] * BlockSize;
		y[i] = Left + ColToRow[i] * BlockSize;
	}
	
}


void Block::XBack()
{
	for (int i(0); i < 4; i++)
	{
		x[i] = Top + (--BaseRow[i]) * BlockSize;
	}
}

void Block::YBack(char i)
{
	if (i=='L')
	{
		for (int i(0); i < 4; i++)
		{
			y[i] = Left + (++ColToRow[i]) * BlockSize;
		}
	}
	else if (i == 'R')
	{
		for (int i(0); i < 4; i++)
		{
			y[i] = Left + (--ColToRow[i]) * BlockSize;
		}
	}
}

int Block::GetLeft()
{
	return Left;
}

int Block::GetTop()
{
	return Top;
}


int Block::GetBaseRow(int i)
{
	return BaseRow[i];
}

int Block::GetColToRow(int i)
{
	return ColToRow[i];
}

//void Block::SetBaseRow(int i, int value)
//{
//	BaseRow[i]=value;
//}
//
//void Block::SetColToRow(int i, int value)
//{
//	ColToRow[i]=value;
//}
//
//void Block::SetX(int i, int value)
//{
//	x[i] = value;
//}
//
//void Block::SetY(int i, int value)
//{
//	y[i] = value;
//}

void Block::Eturn()
{
	//旋转公式
	int Centre[2];
	Centre[0] = BaseRow[1];
	Centre[1] = ColToRow[1];
	int BaseRowBack[4], ColToRowBack[4];
	for (int i(0); i < 4; i++)
	{
		BaseRowBack[i] = BaseRow[i];
		ColToRowBack[i] = ColToRow[i];
	}
	for (int i(0); i < 4; i++)
	{
		ColToRow[i] = Centre[1] + BaseRowBack[i] - Centre[0];
		BaseRow[i] = Centre[0] - ColToRowBack[i] + Centre[1];
	}
	for (int i(0); i < 4; i++)
	{
		x[i] = Top + BaseRow[i] * BlockSize;
		y[i] = Left + ColToRow[i] * BlockSize;
	}
}



void Block::PrintBlock()
{
	for (int i(0); i < 4; i++)
	{
		putimage(y[i], x[i], &BlockBase[this->type-1]);
	}
}

void Block::Down()
{
	for (int i(0); i < 4; i++)
	{
		x[i] = Top + (++BaseRow[i]) * BlockSize;
	}
}

void Block::MoveLeft()
{
	for (int i(0); i < 4; i++)
	{
		y[i] = Left + (--ColToRow[i]) * BlockSize;
	}
}

void Block::MoveRight()
{
	for (int i(0); i < 4; i++)
	{
		y[i] = Left + (++ColToRow[i]) * BlockSize;
	}
}
