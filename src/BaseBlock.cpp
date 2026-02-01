#include"BaseBlock.h"

int BaseBlock::BlockSize = 40;
int BaseBlock::theme = 0;
BaseBlock::BaseBlock()
{
    switch (BaseBlock::theme)
    {
    case 0:
        loadimage(&BlockRes, "res\\Blocks\\Rain\\Blocks.jpg", BlockSize * 7, BlockSize);//���ط���ͼƬ��7����������

        //�и��?7�ֻ�ԪͼƬ
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * BlockSize, 0, BlockSize, BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 1:
        loadimage(&BlockRes, "res\\Blocks\\Snow\\Blocks.jpg", BlockSize * 7, BlockSize);//���ط���ͼƬ��7����������

        //�и��?7�ֻ�ԪͼƬ
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * BlockSize, 0, BlockSize, BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 2:
        loadimage(&BlockRes, "res\\Blocks\\Dawn\\Blocks.jpg", BlockSize * 7, BlockSize);//���ط���ͼƬ��7����������

        //�и��?7�ֻ�ԪͼƬ
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * BlockSize, 0, BlockSize, BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    }
}

BaseBlock::~BaseBlock()
{
}

void BaseBlock::BlockReload()
{
    switch (BaseBlock::theme)
    {
    case 0:
        loadimage(&BlockRes, "res\\Blocks\\Rain\\Blocks.jpg", BlockSize * 7, BlockSize);//���ط���ͼƬ��7����������

        //�и��?7�ֻ�ԪͼƬ
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * BlockSize, 0, BlockSize, BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 1:
        loadimage(&BlockRes, "res\\Blocks\\Snow\\Blocks.jpg", BlockSize * 7, BlockSize);//���ط���ͼƬ��7����������

        //�и��?7�ֻ�ԪͼƬ
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * BlockSize, 0, BlockSize, BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 2:
        loadimage(&BlockRes, "res\\Blocks\\Dawn\\Blocks.jpg", BlockSize * 7, BlockSize);//���ط���ͼƬ��7����������

        //�и��?7�ֻ�ԪͼƬ
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * BlockSize, 0, BlockSize, BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    }
}


void BaseBlock::SetPro(int type)  //��������
{
    int TypeMatrix[7][4] =    //7�ַ������;���
    {
        3, 5, 7, 6, // L������
        2, 3, 5, 7, // L��
        3, 5, 4, 7, // T��
        2, 4, 5, 7, // Z��ͻ��
        3, 5, 4, 6, // Z��ͻ��
        1, 3, 5, 7, // 1��
        2, 3, 4, 5, // �ĸ�������
    };

    for (int i (0); i < 4; i++)      //��ö�Ӧ���ͷ�����Ч����?
    {
        BaseRow[i] = TypeMatrix[type-1][i] / 2;
        ColToRow[i] = TypeMatrix[type-1][i] % 2;
    }
}
