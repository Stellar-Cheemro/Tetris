#include "Tetris.h"

int Tetris::CountDown = 50000;
int Tetris::DState = 0;
int Tetris::CState = 0;

void Tetris::RankOut(int rank, int RID, int Rscores)
{
    setbkmode(TRANSPARENT);//设置背景透面
    settextcolor(RGB(141, 225, 87));//设置颜色，参数用RGB
    settextstyle(Block::BlockSize, Block::BlockSize/2, "Aptos Black");//设置大小、字体

    char num[10] = {};
    string st = to_string(Rscores);
    strcpy_s(num, st.c_str());

    char id[9] = {};
    string ID;
    switch (RID)
    {
    case 0 :
        ID = "存档一:";
        break;
    case 1:
        ID = "存档二:";
        break;
    case 2:
        ID = "存档三:";
        break;
    case 3:
        ID = "存档四:";
        break;
    case 4:
        ID = "存档五:";
        break;
    }
    strcpy_s(id, ID.c_str());
    switch (rank)
    {
    case 0:
        outtextxy(RankL, RankT, id);
        outtextxy(RankL+6* BaseBlock::BlockSize, RankT, num);
        break;
    case 1:
        outtextxy(RankL, RankT+BaseBlock::BlockSize, id);
        outtextxy(RankL + 6 * BaseBlock::BlockSize, RankT + BaseBlock::BlockSize, num);
        break;
    case 2:
        outtextxy(RankL, RankT+BaseBlock::BlockSize*2, id);
        outtextxy(RankL + 6 * BaseBlock::BlockSize, RankT + BaseBlock::BlockSize*2, num);
        break;
    }
}

Tetris::Tetris()
{

    //初始化基本参数、
    SetTheme(0);//主题
    Rate = 1; Quick = 1;
    NextL = Block::BlockSize * 35, NextT = Block::BlockSize * 1;
    ScoreL = Block::BlockSize * 32, ScoreT = Block::BlockSize * 6.5;
    LevelL = Block::BlockSize * 35, LevelT = Block::BlockSize * 10.5;
    RankL = Block::BlockSize * 31, RankT = Block::BlockSize * 14;
    TipL = Block::BlockSize * 32, TipT = Block::BlockSize * 19;

    Idex = 0;
    
    //界面切换
    AtPD = 0;
    At2010 = 1, At2014 = 0;
    AtGame=0;
    AtStart=1, StartDraw=1;
    AtTell = 0 ;
    AtDCM=0,DCMP = 0,AtDCC = 0;
    AtOver = 0;
    AtChange = 0;
    AtPause=0;
    AtMusic=0;
    AtPM=0;
    AtQuit = 0;

    //初始化基元方块
    switch (BaseBlock::theme)
    {
    case 0:
        loadimage(&BlockRes, "res\\Blocks\\Rain\\Blocks.jpg", Block::BlockSize * 7, Block::BlockSize);//加载方块图片（7方块相连）

        //切割出7种基元图片
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * Block::BlockSize, 0, Block::BlockSize, Block::BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 1:
        loadimage(&BlockRes, "res\\Blocks\\Snow\\Blocks.jpg", Block::BlockSize * 7, Block::BlockSize);//加载方块图片（7方块相连）

        //切割出7种基元图片
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * Block::BlockSize, 0, Block::BlockSize, Block::BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 2:
        loadimage(&BlockRes, "res\\Blocks\\Dawn\\Blocks.jpg", Block::BlockSize * 7, Block::BlockSize);//加载方块图片（7方块相连）

        //切割出7种基元图片
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * Block::BlockSize, 0, Block::BlockSize, Block::BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    }
    //初始化gamestate
    for (int i (0); i < 20; i++)
    {
        vector<int> row;
        for (int j (0); j < 10; j++)
        {
            row.push_back(0);
        }
        GameState.push_back(row);
    }
    //初始化gamestate2014
    for (int i(0); i < 20; i++)
    {
        vector<int> row;
        for (int j(0); j < 14; j++)
        {
            row.push_back(0);
        }
        GameState2014.push_back(row);
    }


    //初始化方块
    Next = new Block;
    Cur = Next;
    Next = new Block;
    BaseBlock* block[2] = { Cur,Next };

    //初始化Cur和Next的参数（type）
    srand(time(NULL));
    Cur->SetType(rand() % 7 + 1);//最小1，便于GameState里与0区分
    block[0]->SetPro(Cur->GetType());
    Next->SetType(rand() % 7 + 1);
    block[1]->SetPro(Next->GetType());
}

Tetris::~Tetris()
{
}



void Tetris::ToStart()
{
    FullScreen();
    loadimage(&Start, "res\\Start\\开始界面.png", 1920,1080);//加载开始界面
    putimage(0, 0, &Start);
    MM.PlayMusic();
}

void Tetris::ToDCM()
{
    //加载图片
    for (int i(0); i < 5; i++)
    {
        switch (i)
        {
        case 0:
            loadimage(&DCM[i], "res\\Document\\存档一.png", 1920, 1080);
            break;
        case 1:
            loadimage(&DCM[i], "res\\Document\\存档二.png", 1920, 1080);
            break;
        case 2:
            loadimage(&DCM[i], "res\\Document\\存档三.png", 1920, 1080);
            break;
        case 3:
            loadimage(&DCM[i], "res\\Document\\存档四.png", 1920, 1080);
            break;
        case 4:
            loadimage(&DCM[i], "res\\Document\\存档五.png", 1920, 1080);
            break;
        }
    }

    //画出第一个图片
    putimage(0, 0, &DCM[DState]);

    char key;
    if (AtDCM)
    {
        while (1)
        {
            if (AtDCM)
            {
                key = _getch();
                if (key ==75||key=='A'||key=='a')
                {
                    if (DState != 0)
                    {
                        DState -= 1;
                    }
                    else
                    {
                        DState = 4;
                    }
                }
                if (key ==77||key=='D'||key=='d')
                {
                    if (DState != 4)
                    {
                        DState += 1;
                    }
                    else
                    {
                        DState = 0;
                    }
                }
                if (key == 27)
                {
                    AtDCM = 0;
                    DCMP = 1;
                    AtPD = 1;
                    break;
                }
                if (key == 13)
                {
                    AtDCM = 0;
                    AtDCC = 1;
                    break;
                }
                putimage(0, 0, &DCM[DState]);
            }
        }
    }
    To();
}

void Tetris::To()
{

    if (AtStart)
    {
        ToStart();
    }
    if (AtTell)
    {
        ToTell();
    }
    if (AtDCM)
    {
        ToDCM();
    }
    if (AtDCC)
    {
        ToDCC();
    }
    if (AtGame)
    {
        ToGame();
    }
    if (AtPD)
    {
        ToPD();
    }
    if (AtPause)
    {
        ToPause();
    }
    if (AtOver)
    {
        ToOver();
    }
    if(AtChange)
    {
        ToChange();
    }
    if (AtMusic)
    {
        ToMusic();
    }
    if (AtPM)
    {
        ToPM();
    }
    if (AtQuit)
    {
        ToQuit();
    }
}

void Tetris::ResetPro()
{
    switch (BaseBlock::theme)
    {
    case 0:
        loadimage(&BlockRes, "res\\Blocks\\Rain\\Blocks.jpg", Block::BlockSize * 7, Block::BlockSize);//加载方块图片（7方块相连）

        //切割出7种基元图片
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * Block::BlockSize, 0, Block::BlockSize, Block::BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 1:
        loadimage(&BlockRes, "res\\Blocks\\Snow\\Blocks.jpg", Block::BlockSize * 7, Block::BlockSize);//加载方块图片（7方块相连）

        //切割出7种基元图片
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * Block::BlockSize, 0, Block::BlockSize, Block::BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 2:
        loadimage(&BlockRes, "res\\Blocks\\Dawn\\Blocks.jpg", Block::BlockSize * 7, Block::BlockSize);//加载方块图片（7方块相连）

        //切割出7种基元图片
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * Block::BlockSize, 0, Block::BlockSize, Block::BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    }
}

void Tetris::ToGame()
{
    DCMP = 0;//从存档类操作种出来
    if (AtGame)//确定要进入游戏界面
    {
        BGReset();//画出背景
        char key;
        while (1)//CD逐渐减少，小于0方块降落，实现自主降落与加速降落
        {

            if (!_kbhit())
            {
                
                for (; ; Tetris::CountDown = Tetris::CountDown - 1*Rate*Quick)
                {
                    if (_kbhit())
                    {
                        break;
                    }
                    if (Tetris::CountDown <= 0)
                    {
                        Down();
                        OutFix();//固定方块
                        ResetCD();
                        break;
                    }
                }
            }
            SetQuick(1);//没有按速降键（S）等时速度恢复
            if (_kbhit())
            {
                if (AtGame)
                {
                    key = _getch();
                }
                if (key == 27)//暂停进入暂停界面
                {
                    AtGame = 0;
                    AtPause = 1;
                    break;
                }
                else
                {
                    KeyToDo(key);//对游戏本体操作进行处理
                    OutFix();
                }
            }
        }
    }
    To();//如若要进行界面切换，则进行切换
}

void Tetris::FullScreen()
{
    int rW = GetSystemMetrics(SM_CXSCREEN); // 屏幕宽度 像素
    int rH = GetSystemMetrics(SM_CYSCREEN); // 屏幕高度 像素

    HWND hwnd = initgraph(rW, rH); // 初始化绘图窗口并获取窗口句柄

    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE); // 获取窗口信息
    // 设置窗口信息 最大化 取消标题栏及边框
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);// 直接修改窗口样式

    SetWindowPos(hwnd, HWND_TOP, 0, 0, rW, rH, 0);
}

void Tetris::ToQuit()
{
    if (!DCMP)
    {
        //加载图片
        for (int i(0); i < 2; i++)
        {
            switch (i)
            {
            case 0:
                loadimage(&Quit[i], "res\\Document\\是.png", 720, 480);
                break;
            case 1:
                loadimage(&Quit[i], "res\\Document\\否.png", 720, 480);
                break;
            }
        }

        //画出第一个图片
        putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &Quit[0]);

        int State(0);
        char key;
        if (AtQuit)
        {
            while (1)
            {
                if (AtQuit)
                {
                    key = _getch();
                    if (key == 75 || key == 'A' || key == 'a')
                    {
                        if (State != 0)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 1;
                        }
                    }
                    if (key == 77 || key == 'D' || key == 'd')
                    {
                        if (State != 1)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 0;
                        }
                    }
                    if (key == 13)
                    {
                        AtQuit = 0;
                        switch (State)
                        {
                        case 0:
                            DC();
                            closegraph();
                            break;
                        case 1:
                            closegraph();
                            break;

                        }
                        break;
                    }
                    putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &Quit[State]);
                }
            }
        }
    }
    else
    {
        closegraph();
    }
    To();
}

void Tetris::CStateReset()
{
    CState = 0;
}
void Tetris::To2010()
{
    if (At2014)
    { }
    else
    {
        //复制gamestate
        for (int i(0); i < 20; i++)
        {
            for (int j(0); j < 10; j++)
            {
                GameState[i][j] = GameState2014[i][j + 2];
            }
        }
    }
}
void Tetris::To2014()
{
    if(At2010)
    { }
    else
    {
        //复制gamestate2014
        //左右各两行定义为0
        for (int i(0); i < 20; i++)
        {
            GameState2014[i][0] = 0;
            GameState2014[i][1] = 0;
            GameState2014[i][12] = 0;
            GameState2014[i][13] = 0;
        }
        //复制中间进度
        for (int i(0); i < 20; i++)
        {
            for (int j(2); j < 12; j++)
            {
                GameState2014[i][j] = GameState[i][j-2];
            }
        }
    }
}


void Tetris::Again()
{
    //初始化参数
    level = 1;
    scores = 0;
    Rate = 1;
    CountDown = 50000;

    if (At2010)
    {
        //初始化gamestate
        for (int i(0); i < 20; i++)
        {
            for (int j(0); j < 10; j++)
            {
                GameState[i][j] = 0;
            }
        }
    }
    else if(At2014)
    { 
        //初始化gamestate2014
        for (int i(0); i < 20; i++)
        {
            for (int j(0); j < 14; j++)
            {
                GameState2014[i][j] = 0;
            }
        }
    }
    //初始化方块
    Next = new Block;
    Cur = Next;
    Next = new Block;
    BaseBlock* block[2] = { Cur,Next };

    //初始化Cur和Next的参数（type）
    srand(time(NULL));
    Cur->SetType(rand() % 7 + 1);//最小1，便于GameState里与0区分
    block[0]->SetPro(Cur->GetType());
    Next->SetType(rand() % 7 + 1);
    block[1]->SetPro(Next->GetType());


}
void Tetris::SetEdge()
{
    //根据目前主题加载所用到的三个边界基础
    switch (BaseBlock::theme)
    {
    case 0:
        loadimage(&L12, "res\\Edges\\Rain\\L12.png", Block::BlockSize * 12, Block::BlockSize);
        loadimage(&L16, "res\\Edges\\Rain\\L16.png", Block::BlockSize * 16, Block::BlockSize);
        loadimage(&E27, "res\\Edges\\Rain\\E27.png", Block::BlockSize, Block::BlockSize * 27);
        break;
    case 1:
        loadimage(&L12, "res\\Edges\\Snow\\L12.png", Block::BlockSize * 12, Block::BlockSize);
        loadimage(&L16, "res\\Edges\\Snow\\L16.png", Block::BlockSize * 16, Block::BlockSize);
        loadimage(&E27, "res\\Edges\\Snow\\E27.png", Block::BlockSize, Block::BlockSize * 27);
        break;
    case 2:
        loadimage(&L12, "res\\Edges\\Dawn\\L12.png", Block::BlockSize * 12, Block::BlockSize);
        loadimage(&L16, "res\\Edges\\Dawn\\L16.png", Block::BlockSize * 16, Block::BlockSize);
        loadimage(&E27, "res\\Edges\\Dawn\\E27.png", Block::BlockSize, Block::BlockSize * 27);
        break;
    }

    //根据当前棋盘大小进行主体边框放置
    if (At2010)
    {
        //放置主体边框
        putimage(Block::BlockSize * 9, Block::BlockSize * 6, &E27);
        putimage(Block::BlockSize * 20, Block::BlockSize * 6, &E27);
        putimage(Block::BlockSize * 9, Block::BlockSize * 26, &L12);
    }
    else if(At2014)
    {
        putimage(Block::BlockSize * 7, Block::BlockSize * 6, &E27);
        putimage(Block::BlockSize * 22, Block::BlockSize * 6, &E27);
        putimage(Block::BlockSize * 7, Block::BlockSize * 26, &L16);
    }

    //放置右操作提醒
    putimage(Block::BlockSize * 30, 0, &E27);
    putimage(Block::BlockSize * 41, 0, &E27);
    putimage(Block::BlockSize * 30, 0, &L12);
    putimage(Block::BlockSize * 30, Block::BlockSize * 5, &L12);
    putimage(Block::BlockSize * 30, Block::BlockSize * 9, &L12);
    putimage(Block::BlockSize * 30, Block::BlockSize * 13, &L12);
    putimage(Block::BlockSize * 30, Block::BlockSize * 17, &L12);
    putimage(Block::BlockSize * 30, Block::BlockSize * 26, &L12);
}


void Tetris::ResetCD()
{
    Tetris::CountDown = (50000-3000*level) / Rate;
}

void Tetris::SetQuick(int i)
{
    Quick = i;
}


void Tetris::SetGS()
{
    //根据当前游戏进度与棋盘大小对游戏本体降落区进行绘制
    if (At2010)
    {
        int Left = Cur->GetLeft() - 4 * Block::BlockSize;//坐标
        int Top = Cur->GetTop() + 4 * Block::BlockSize;
        for (int i(0); i < 20; i++)
        {
            for (int j(0); j < 10; j++)
            {
                if (GameState[i][j] != 0)
                {
                    //根据降落区数据进行种类判断再绘制
                    putimage(Left + j * Block::BlockSize, Top + i * Block::BlockSize, &BlockBase[GameState[i][j] - 1]);
                }
            }
        }
    }
    else if (At2014)
    {
        int Left = Cur->GetLeft() - 4 * Block::BlockSize;
        int Top = Cur->GetTop() + 4 * Block::BlockSize;
        for (int i(0); i < 20; i++)
        {
            for (int j(0); j < 14; j++)
            {
                if (GameState2014[i][j] != 0)
                {
                    putimage(Left + (j-2) * Block::BlockSize, Top + i * Block::BlockSize, &BlockBase[GameState2014[i][j] - 1]);
                }
            }
        }
    }
}

void Tetris::ToOver()
{    //加载图片
    for (int i(0); i < 3; i++)
    {
        switch (i)
        {
        case 0:
            loadimage(&Over[i], "res\\Over\\退出.png", 720, 480);
            break;
        case 1:
            loadimage(&Over[i], "res\\Over\\重开.png", 720, 480);
            break;
        case 2:
            loadimage(&Over[i], "res\\Over\\换档.png", 720, 480);
            break;
        }
    }
    //画出第一个图片
    int State = 0;
    putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &Over[State]);

    char key;
    if (AtOver)
    {
        while (1)
        {
            if (AtOver)
            {
                key = _getch();
                if (key == 75 || key == 'A' || key == 'a')
                {
                    if (State != 0)
                    {
                        State -= 1;
                    }
                    else
                    {
                        State = 2;
                    }
                }
                if (key == 77 || key == 'D' || key == 'd')
                {
                    if (State != 2)
                    {
                        State += 1;
                    }
                    else
                    {
                        State = 0;
                    }
                }
                if (key == 27)
                {
                    AtOver = 0;
                    AtPause = 1;
                    break;
                }
                if (key == 13)
                {
                    AtOver = 0;
                    switch (State)
                    {
                    case 0:
                        AtQuit = 1;
                        break;
                    case 1:
                        Again();
                        AtGame = 1;
                        break;
                    case 2:
                        AtChange = 1;
                        break;
                    }
                    break;
                }
                putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &Over[State]);
            }
        }
    }
    To();
}

void Tetris::ToChange()
{
    //加载图片
    for (int i(0); i < 2; i++)
    {
        switch (i)
        {
        case 0:
            loadimage(&Change[i], "res\\Change\\是.png", 720, 480);
            break;
        case 1:
            loadimage(&Change[i], "res\\Change\\否.png", 720, 480);
            break;
        }
    }

    //画出第一个图片
    putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &Change[0]);

    char key;

    int State(0);
    if (AtChange)
    {
        while (1)
        {
            if (AtChange)
            {
                key = _getch();
                if (key == 75 || key == 'A' || key == 'a')
                {
                    if (State != 0)
                    {
                        State -= 1;
                    }
                    else
                    {
                        State = 1;
                    }
                }
                if (key == 77 || key == 'D' || key == 'd')
                {
                    if (State != 1)
                    {
                        State += 1;
                    }
                    else
                    {
                        State = 0;
                    }
                }
                if (key == 27)
                {
                    AtChange = 0;
                    AtPause = 1;
                    break;
                }
                if (key == 13)
                {
                    AtChange = 0;
                    AtDCM = 1;
                    break;
                }
                putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &Change[State]);
            }
        }
    }
    if (!State)
    {
        DC();
    }
    else
    {
        DCReset();
    }
    To();
}
void Tetris::ToPD()
{
    //加载图片
    for (int i(0); i < 3; i++)
    {
        switch (i)
        {
        case 0:
            loadimage(&PD[i], "res\\PD\\返回.png", 720, 480);
            break;
        case 1:
            loadimage(&PD[i], "res\\PD\\退出.png", 720, 480);
            break;
        case 2:
            loadimage(&PD[i], "res\\PD\\音乐设置.png", 720, 480);
            break;
        }
    }

    //画出第一个图片
    putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &PD[0]);

    char key;
    int State = 0;

    if (AtPD)
    {
        while (1)
        {
            if (AtPD)
            {
                key = _getch();
                if (key == 75 || key == 'A' || key == 'a')
                {
                    if (State != 0)
                    {
                        State -= 1;
                    }
                    else
                    {
                        State = 2;
                    }
                }
                if (key == 77 || key == 'D' || key == 'd')
                {
                    if (State != 2)
                    {
                        State += 1;
                    }
                    else
                    {
                        State = 0;
                    }
                }
                if (key == 27)
                {
                    AtPD = 0;
                    AtDCM = 1;
                    break;
                }
                if (key == 13)
                {
                    AtPD = 0;
                    switch (State)
                    {
                    case 0:
                        AtDCM = 1;
                        break;
                    case 1:
                        AtQuit = 1;
                        DCMP = 1;
                        break;
                    case 2:
                        AtMusic = 1;
                        break;
                    }
                    break;
                }
                putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &PD[State]);
            }
        }
    }
    To();
}
//换档时是否保存
void Tetris::SetBG()
{
    //根据主题设置背景
    switch (BaseBlock::theme)
    {
    case 0:
        loadimage(&Background, "res\\Background\\Rain\\End.jpg", 1920, 1080);
        loadimage(&MBG[0], "res\\Background\\Rain\\Rain.jpg", 480, 840);
        loadimage(&MBG[1], "res\\Background\\Rain\\Rain.jpg", 640, 840);

        putimage(0, 0, &Background);
        if (At2010)
        {
            putimage(BaseBlock::BlockSize*9, BaseBlock::BlockSize * 6, &MBG[0]);
        }
        else if (At2014)
        {
            putimage(BaseBlock::BlockSize * 7, BaseBlock::BlockSize * 6, &MBG[1]);
        }
        break;
    case 1:
        loadimage(&Background, "res\\Background\\Snow\\Tibet.jpg", 1920, 1080);
        loadimage(&MBG[0], "res\\Background\\Snow\\Snow.jpg", 480, 840);
        loadimage(&MBG[1], "res\\Background\\Snow\\Snow.jpg", 640, 840);

        putimage(0, 0, &Background);
        if (At2010)
        {
            putimage(BaseBlock::BlockSize * 9, BaseBlock::BlockSize * 6, &MBG[0]);
        }
        else if (At2014)
        {
            putimage(BaseBlock::BlockSize * 7, BaseBlock::BlockSize * 6, &MBG[1]);
        }
        break;
    case 2:
        loadimage(&Background, "res\\Background\\Dawn\\Dawn.jpg", 1920, 1080);
        loadimage(&MBG[0], "res\\Background\\Dawn\\Human.jpg", 480, 840);
        loadimage(&MBG[1], "res\\Background\\Dawn\\Human.jpg", 640, 840);

        putimage(0, 0, &Background);
        //根据棋盘大小绘制MBG[0]或者MBG[1]
        if (At2010)
        {
            putimage(BaseBlock::BlockSize * 9, BaseBlock::BlockSize * 6, &MBG[0]);
        }
        else if (At2014)
        {
            putimage(BaseBlock::BlockSize * 7, BaseBlock::BlockSize * 6, &MBG[1]);
        }
        break;
    }

}

void Tetris::KeyToDo(char key)
{

    switch (key)
    {
    case 'S':
    case 's':
    case 80 : 
        SetQuick(3000);
        break;
    case 'A':
    case 'a':
    case 75 :
        MoveLeft();
        break;
    case 'D':
    case 'd':
    case 77:
        MoveRight();
        break;
    case 'Q':
    case 'q':
        Qturn(Cur->GetType());
        break;
    case 'E':
    case 'e':
        Eturn(Cur->GetType());
        break;
    }
}

bool Tetris::IsBottom()
{
    for (int i(0); i < 4; i++)
    {
        if (Cur->GetBaseRow(i) == 24)
            return true;
    }
    return false;
}

bool Tetris::OutIsBottom()
{
    {
        for (int i(0); i < 4; i++)
        {
            if (Cur->GetBaseRow(i) == 23)
                return true;
        }
        return false;
    }
}

bool Tetris::BydBottom()
{
    for (int i(0); i < 4; i++)
    {
        if (Cur->GetBaseRow(i) >= 24)
            return true;
    }
    return false;
}

void Tetris::PrintTip()
{
    setbkmode(TRANSPARENT);
    settextcolor(RGB(141, 225, 87));
    settextstyle(Block::BlockSize, Block::BlockSize/2, "Aptos Black");
    char num[20] = {};
    //打印暂停
    string C = "ESC  ：暂停";
    strcpy_s(num, C.c_str());
    outtextxy(TipL, TipT, num);

    //打印左移
    string  A= "A、←：左移";
    strcpy_s(num, A.c_str());
    outtextxy(TipL, TipT + BaseBlock::BlockSize, num);

    //打印右移
    string D = "D、→：右移";
    strcpy_s(num, D.c_str());
    outtextxy(TipL, TipT + BaseBlock::BlockSize*2, num);

    //打印速降
    string S = "S、↓：加速下落";
    strcpy_s(num, S.c_str());
    outtextxy(TipL, TipT + BaseBlock::BlockSize*3, num);

    //打印顺时针
    string Q = "Q    ：顺时针旋转";
    strcpy_s(num, Q.c_str());
    outtextxy(TipL, TipT + BaseBlock::BlockSize * 4, num);

    //打印逆时针
    string E = "E    ：逆时针旋转";
    strcpy_s(num, E.c_str());
    outtextxy(TipL, TipT + BaseBlock::BlockSize * 5, num);
}

bool Tetris::IsEdge()
{
    if (At2010)
    {
        for (int i(0); i < 4; i++)
        {
            if (Cur->GetColToRow(i) == -4 || Cur->GetColToRow(i) == 5)
            {
                return true;
            }
        }
        return false;
    }
    else if (At2014)
    { 
        for (int i(0); i < 4; i++)
        {
            if (Cur->GetColToRow(i) == -6 || Cur->GetColToRow(i) == 7)
            {
                return true;
            }
        }
        return false;
    }
}

bool Tetris::BydEdge()
{
    if (At2010)
    {
        for (int i(0); i < 4; i++)
        {
            if (Cur->GetColToRow(i) <= -5 || Cur->GetColToRow(i) >= 6)
            {
                return true;
            }
        }
        return false;
    }
    if (At2014)
    {
        for (int i(0); i < 4; i++)
        {
            if (Cur->GetColToRow(i) <= -7 || Cur->GetColToRow(i) >= 8)
            {
                return true;
            }
        }
        return false;
    }
}

bool Tetris::IsTouch()
{
    if (At2010)
    {
        for (int i(0); i < 4; i++)
        {
            if (Cur->GetBaseRow(i) >= 4 && Cur->GetBaseRow(i) < 24)
            {
                if (GameState[Cur->GetBaseRow(i) - 4][Cur->GetColToRow(i) + 4] != 0)
                    return true;
            }
        }
        return false;
    }
    else if (At2014)
    {
        for (int i(0); i < 4; i++)
        {
            if (Cur->GetBaseRow(i) >= 4 && Cur->GetBaseRow(i) < 24)
            {
                if (GameState2014[Cur->GetBaseRow(i) - 4][Cur->GetColToRow(i) + 6] != 0)
                    return true;
            }
        }
        return false;
    }
}

int Tetris::Clean()
{

    int CleanIdex[20] = { 1, };//记录每行状态，判定是否消除
    for (int i(0); i < 20; i++)
    {
        CleanIdex[i] = 1;
    }

    for (int i(0); i < 20; i++)
    {
        if (At2010)
        {
            for (int j(0); j < 10; j++)
            {
                if (GameState[i][j] == 0)//一行里有0值代表未被填满，不清除
                {
                    CleanIdex[i] = 0;
                    break;
                }
            }
        }
        else if(At2014)
        {
            for (int j(0); j < 14; j++)
            {
                if (GameState2014[i][j] == 0)
                {
                    CleanIdex[i] = 0;
                    break;
                }
            }
        }
    }

    //对每行进行判定与消除填补
    int CleanNum(0);//记录共消除几行
    for (int i(1); i < 20; i++)  //从上往下覆盖
    {
        if (CleanIdex[i] == 1)
        {
            for (int i1(i - 1); i1 >= 0; i1--)
            {
                if (At2010)
                {
                    for (int j(0); j < 10; j++)
                    {
                        GameState[i1 + 1][j] = GameState[i1][j];
                    }
                }
                else if (At2014)
                {
                    for (int j(0); j < 14; j++)
                    {
                        GameState2014[i1 + 1][j] = GameState2014[i1][j];
                    }
                }
            }
            if (At2010)
            {
                for (int j(0); j < 10; j++)
                {
                    GameState[0][j] = 0;
                }
            }
            else if (At2014)
            {
                for (int j(0); j < 14; j++)
                {
                    GameState2014[0][j] = 0;
                }
            }
            CleanNum++;
        }
    }
    if (At2010)//根据一次消掉多少行进行加分
    {
        switch (CleanNum)
        {
        case 0:return 0;
        case 1:return 10 * level * level / 3;
        case 2:return 30 * level * level / 3;
        case 3:return 80 * level * level / 3;
        case 4:return 200 * level * level / 3;
        }
    }
    else if (At2014)
    {
        switch (CleanNum)
        {
        case 0:return 0;
        case 1:return 10 * level * level / 2;
        case 2:return 30 * level * level / 2;
        case 3:return 80 * level * level / 2;
        case 4:return 200 * level * level / 2;
        }
    }
}


void Tetris::Down()
{
    //备份数据以备超框、接触、触底等情况返回原样
    int BackRow[4], BackCol[4];
    for (int i(0); i < 3; i++)
    {
        BackRow[i] = Cur->GetRow(i);
        BackCol[i] = Cur->GetCol(i);
    }
    if (BydEdge())//超框返回
    {
        Cur->SetPro('r', BackRow, BackCol);
    }

    Cur->Down();
    if (IsBottom() || IsTouch())
    {
        Cur->XBack();//触底或者接触返回
        Fix();//固定
        if (!AtOver)//游戏未结束，将预告方块加载到现在方块并重得预告方块
        {
            BGReset();
            Trans();
        }
        else
        {
            To();//游戏结束，进入结束界面
        }
    }
    else
    {
        BGReset();
    }
}

void Tetris::MoveLeft()
{

    Cur->MoveLeft();
    if (BydEdge()||IsBottom() || IsTouch())
    {
        Cur->YBack('L');
    }
    else
    {
        BGReset();
    }
}

void Tetris::MoveRight()
{

    Cur->MoveRight();
    if (BydEdge() || IsBottom() || IsTouch())
    {
        Cur->YBack('R');
    }
    else
    {
        BGReset();
    }
}

void Tetris::Qturn(int type)
{
    if (type == 7) {}
    else
    {
        int BackRow[4], BackCol[4];
        for (int i(0); i < 4; i++)
        {
            BackRow[i] = Cur->GetRow(i);
            BackCol[i] = Cur->GetCol(i);
        }
        for (int i(0); i < 3; i++)
        {
            Cur->Eturn();
        }
        if (BydEdge() || IsTouch() || BydBottom())//超框返回
        {
            Cur->SetPro('r', BackRow, BackCol);
        }
        else
        {
            BGReset();
            Cur->PrintBlock();
        }
    }
    
}

void Tetris::Eturn(int type)
{
    if (type == 7) {}//方块不进行旋转
    else 
    {
        int BackRow[4], BackCol[4];
        for (int i(0); i < 4; i++)
        {
            BackRow[i] = Cur->GetRow(i);
            BackCol[i] = Cur->GetCol(i);
        }

        Cur->Eturn();

        if (BydEdge() || IsTouch() || BydBottom())//超框返回
        {
            Cur->SetPro('r', BackRow, BackCol);
        }
        else
        {
            BGReset();
            Cur->PrintBlock();
        }
    }

}

void Tetris::Fix()
{
    int check(0);
    for (int j(0); j < 4; j++)
    {
        if (Cur->GetBaseRow(j) < 4)
        {
            check = 1;
            AtOver = true;
            AtGame = 0;
            break;
        }
    }
    if (At2010)
    {
        if (!check)
        {
            for (int i(0); i < 4; i++)
            {
                GameState[Cur->GetBaseRow(i) - 4][Cur->GetColToRow(i) + 4] = Cur->GetType();
            }
        }
    }
    else if (At2014)
    {
        if (!check)
        {
            for (int i(0); i < 4; i++)
            {
                GameState2014[Cur->GetBaseRow(i) - 4][Cur->GetColToRow(i) + 6] = Cur->GetType();
            }
        }
    }
}

void Tetris::OutFix()
{
    if (OutIsBottom())
    {
        Fix();
        BGReset();
        Trans();
    }
    scores += Clean();//判断是否清行
    LevelUp();
}

void Tetris::LevelUp()
{
    if (level<10&&scores > 150*(level*level/2+1))
    {
        level +=1;
        CountDown -= 3000/Rate;//等级提高，减少倒计时
    }
}


void Tetris::DC()
{

    ofstream dc;

    switch (DState)
    {
    case 0:
        dc.open("Document\\存档一.txt", ios::out | ios::binary | ios::trunc);
        break;
    case 1:
        dc.open("Document\\存档二.txt", ios::out | ios::binary | ios::trunc);
        break;
    case 2:
        dc.open("Document\\存档三.txt", ios::out | ios::binary | ios::trunc);
        break;
    case 3:
        dc.open("Document\\存档四.txt", ios::out | ios::binary | ios::trunc);
        break;
    case 4:
        dc.open("Document\\存档五.txt", ios::out | ios::binary | ios::trunc);
        break;
    }
    //存档序号、分数、等级、游戏进度
    dc.write((char*)&Idex, sizeof(Idex));
    dc.write((char*)&BaseBlock::theme, sizeof(BaseBlock::theme));
    dc.write((char*)&At2010, sizeof(At2010));
    dc.write((char*)&At2014, sizeof(At2014));
    dc.write((char*)&Rate, sizeof(Rate));
    dc.write((char*)&scores, sizeof(scores));
    dc.write((char*)&level, sizeof(level));
    if (At2010)
    {
        for (int i(0); i < 20; i++)
        {
            for (int j(0); j < 10; j++)
            {
                dc.write((char*)&GameState[i][j], sizeof(GameState[i][j]));
            }
        }
    }
    else if (At2014)
    {
        for (int i(0); i < 20; i++)
        {
            for (int j(0); j < 14; j++)
            {
                dc.write((char*)&GameState2014[i][j], sizeof(GameState2014[i][j]));
            }
        }
    }

    //记录当前方块和预告方块
    int CBackRow[4], CBackCol[4],Ctype;
    int NBackRow[4], NBackCol[4],Ntype;

    Ctype = Cur->GetType();
    Ntype = Next->GetType();

    for (int i(0); i < 4; i++)
    {
        CBackRow[i] = Cur->GetBaseRow(i);
        CBackCol[i] = Cur->GetColToRow(i);
        NBackRow[i] = Next->GetBaseRow(i);
        NBackCol[i] = Next->GetColToRow(i);
    }

    //当前方块
    dc.write((char*)&Ctype, sizeof(Ctype));
    for (int i(0); i < 5; i++)
    {
    dc.write((char*)&CBackRow[i], sizeof(CBackRow[i]));
    }
    for (int i(0); i < 5; i++)
    {
        dc.write((char*)&CBackCol[i], sizeof(CBackCol[i]));
    }

    //预告方块
    dc.write((char*)&Ntype, sizeof(Ntype));
    for (int i(0); i < 5; i++)
    {
        dc.write((char*)&NBackRow[i], sizeof(NBackRow[i]));
    }
    for (int i(0); i < 5; i++)
    {
        dc.write((char*)&NBackCol[i], sizeof(NBackCol[i]));
    }

    dc.close();
}

void Tetris::RD()
{
    ifstream rd;
    switch (DState)
    {
    case 0:
        rd.open("Document\\存档一.txt");
        break;
    case 1:
        rd.open("Document\\存档二.txt");
        break;
    case 2:
        rd.open("Document\\存档三.txt");
        break;
    case 3:
        rd.open("Document\\存档四.txt");
        break;
    case 4:
        rd.open("Document\\存档五.txt");
        break;
    }
    rd.read((char*)&Idex, sizeof(Idex));

    int theme;
    rd.read((char*)&theme, sizeof(theme));
    SetTheme(theme);

    rd.read((char*)&At2010, sizeof(At2010));

    rd.read((char*)&At2014, sizeof(At2014));

    rd.read((char*)&Rate, sizeof(Rate));

    rd.read((char*)&scores, sizeof(scores));

    rd.read((char*)&level, sizeof(level));

    if (At2010)
    {
        for (int i(0); i < 20; i++)
        {
            for (int j(0); j < 10; j++)
            {
                rd.read((char*)&GameState[i][j], sizeof(GameState[i][j]));
            }
        }
    }
    else if (At2014)
    {
        for (int i(0); i < 20; i++)
        {
            for (int j(0); j < 14; j++)
            {
                rd.read((char*)&GameState2014[i][j], sizeof(GameState2014[i][j]));
            }
        }
    }

    int CBackRow[10]={}, CBackCol[10]={}, Ctype;
    int NBackRow[10]={}, NBackCol[10]={}, Ntype;

    //当前方块
    rd.read((char*)&Ctype, sizeof(Ctype));
    for (int i(0); i < 5; i++)
    {
        rd.read((char*)&CBackRow[i], sizeof(CBackRow[i]));
    }
    for (int i(0); i < 5; i++)
    {
        rd.read((char*)&CBackCol[i], sizeof(CBackCol[i]));
    }

    //预告方块
    rd.read((char*)&Ntype, sizeof(Ntype));
    for (int i(0); i < 5; i++)
    {
        rd.read((char*)&NBackRow[i], sizeof(NBackRow[i]));
    }
    for (int i(0); i < 5; i++)
    {
        rd.read((char*)&NBackCol[i], sizeof(NBackCol[i]));
    }
    Cur->SetType(Ctype);
    Next->SetType(Ntype);
    Cur->SetPro('r', CBackRow, CBackCol);
    Next->SetPro('r', NBackRow, NBackCol);

    ResetPro();
    rd.close();
}

void Tetris::DCReset()
{
    ofstream dc;

    switch (DState)
    {
    case 0:
        dc.open("Document\\存档一.txt", ios::out | ios::binary | ios::trunc);
        break;
    case 1:
        dc.open("Document\\存档二.txt", ios::out | ios::binary | ios::trunc);
        break;
    case 2:
        dc.open("Document\\存档三.txt", ios::out | ios::binary | ios::trunc);
        break;
    case 3:
        dc.open("Document\\存档四.txt", ios::out | ios::binary | ios::trunc);
        break;
    case 4:
        dc.open("Document\\存档五.txt", ios::out | ios::binary | ios::trunc);
        break;
    }
    //存档序号、分数、等级、游戏进度初始化

    int I(DState),  T(0),A1(1),A2(0),R(1), S(0), L(1);
    
    vector<vector<int>> GS;
    //初始化GS
    for (int i(0); i < 20; i++)
    {
        vector<int> row;
        for (int j(0); j < 10; j++)
        {
            row.push_back(0);
        }
        GS.push_back(row);
    }

    dc.write((char*)&I, sizeof(I));
    dc.write((char*)&T, sizeof(T));
    dc.write((char*)&A1, sizeof(A1));
    dc.write((char*)&A2, sizeof(A2));
    dc.write((char*)&R, sizeof(R));
    dc.write((char*)&S, sizeof(S));
    dc.write((char*)&L, sizeof(L));

    for (int i(0); i < 20; i++)
    {
        for (int j(0); j < 10; j++)
        {
            dc.write((char*)&GS[i][j], sizeof(GS[i][j]));
        }
    }

    //初始化方块
    DCNext = new Block;
    DCCur = DCNext;
    DCNext = new Block;
    BaseBlock* block[2] = { DCCur,DCNext };

    //初始化Cur和Next的参数（type）
    srand(time(NULL));
    DCCur->SetType(rand() % 7 + 1);//最小1，便于GameState里与0区分
    block[0]->SetPro(DCCur->GetType());
    DCNext->SetType(rand() % 7 + 1);
    block[1]->SetPro(DCNext->GetType());
    //记录当前方块和预告方块
    int CBackRow[4], CBackCol[4], Ctype;
    int NBackRow[4], NBackCol[4], Ntype;

    Ctype = DCCur->GetType();
    Ntype = DCNext->GetType();

    for (int i(0); i < 4; i++)
    {
        CBackRow[i] = Cur->GetBaseRow(i);
        CBackCol[i] = Cur->GetColToRow(i);
        NBackRow[i] = Next->GetBaseRow(i);
        NBackCol[i] = Next->GetColToRow(i);
    }

    //当前方块
    dc.write((char*)&Ctype, sizeof(Ctype));
    for (int i(0); i < 5; i++)
    {
        dc.write((char*)&CBackRow[i], sizeof(CBackRow[i]));
    }
    for (int i(0); i < 5; i++)
    {
        dc.write((char*)&CBackCol[i], sizeof(CBackCol[i]));
    }

    //预告方块
    dc.write((char*)&Ntype, sizeof(Ntype));
    for (int i(0); i < 5; i++)
    {
        dc.write((char*)&NBackRow[i], sizeof(NBackRow[i]));
    }
    for (int i(0); i < 5; i++)
    {
        dc.write((char*)&NBackCol[i], sizeof(NBackCol[i]));
    }

    dc.close();
}


void Tetris::BGReset()
{

    
    BeginBatchDraw();//开始绘制
    
    cleardevice();//清屏
    SetBG();//绘制背景
    SetEdge();//绘制边框
    SetGS();//绘制进度

    PrintCur();//打印当前方块
    PrintNext();//打印预告方块

    PrintScore();//打印分数
    PrintLevel();//打印等级
    PrintTip();//打印操作提示
    PrintRank();//打印排行榜

    EndBatchDraw();//绘制结束

}

void Tetris::PrintCur()
{
    Cur->PrintBlock();
}

void Tetris::ToPause()
{
    //加载图片
    for (int i(0); i < 6; i++)
    {
        switch (i)
        {
        case 0:
            loadimage(&Pause[i], "res\\Pause\\返回游戏.png", 720, 480);
            break;
        case 1:
            loadimage(&Pause[i], "res\\Pause\\参数设置.png", 720, 480);
            break;
        case 2:
            loadimage(&Pause[i], "res\\Pause\\音乐设置.png", 720, 480);
            break;
        case 3:
            loadimage(&Pause[i], "res\\Pause\\退出.png", 720, 480);
            break;
        case 4:
            loadimage(&Pause[i], "res\\Pause\\重开.png", 720, 480);
            break;
        case 5:
            loadimage(&Pause[i], "res\\Pause\\换档.png", 720, 480);
            break;
        }
    }
    //画出第一个图片
    int State = 0;
    putimage(BaseBlock::BlockSize*12, BaseBlock::BlockSize * 7, &Pause[State]);

    char key;
    if (AtPause)
    {
        while (1)
        {
            if (AtPause)
            {
                key = _getch();
                if (key == 75 || key == 'A' || key == 'a')
                {
                    if (State >= 0 && State <= 2)
                    {
                        if (State != 0)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 2;
                        }
                    }
                    else if (State >= 3 && State <= 5)
                    {
                        if (State != 3)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 5;
                        }
                    }
                }
                if (key == 77 || key == 'D' || key == 'd')
                {
                    if (State >= 0 && State <= 2)
                    {
                        if (State != 2)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 0;
                        }
                    }
                    else if (State >= 3 && State <= 5)
                    {
                        if (State != 5)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 3;
                        }
                    }
                }
                if (key ==  80|| key == 'S' || key == 's')
                {
                    if (State >= 0 && State <= 2)
                    {
                        switch (State)
                        {
                        case 0:
                            State = 3;
                            break;
                        case 1:
                            State = 4;
                            break;
                        case 2:
                            State = 5;
                            break;
                        }
                    }
                    else if (State >= 3 && State <= 5)
                    {
                        switch (State)
                        {
                        case 3:
                            State = 0;
                            break;
                        case 4:
                            State = 1;
                            break;
                        case 5:
                            State = 2;
                            break;
                        }
                    }
                }
                if (key == 72 || key == 'W' || key == 'w')
                {
                    if (State >= 0 && State <= 2)
                    {
                        switch (State)
                        {
                        case 0:
                            State = 3;
                            break;
                        case 1:
                            State = 4;
                            break;
                        case 2:
                            State = 5;
                            break;
                        }
                    }
                    else if (State >= 3 && State <= 5)
                    {
                        switch (State)
                        {
                        case 3:
                            State = 0;
                            break;
                        case 4:
                            State = 1;
                            break;
                        case 5:
                            State = 2;
                            break;
                        }
                    }
                }
                if (key == 27)
                {
                    AtPause = 0;
                    AtQuit = 1;
                    break;
                }
                if (key == 13)
                {
                    AtPause = 0;
                    switch (State)
                    {
                    case 0:
                        AtGame = 1;
                        break;
                    case 1:
                        AtPM = 1;
                        break;
                    case 2:
                        AtMusic = 1;
                        break;
                    case 3:
                            AtQuit = 1;
                            break;
                    case 4:
                        Again();
                        AtGame = 1;
                        break;
                    case 5:
                        AtChange = 1;
                        break;

                    }
                    break;
                }
                putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &Pause[State]);
            }
        }
    }
    To();
}

void Tetris::ToTell()
{
    //加载图片
    loadimage(&Tell, "res\\Tell\\选项说明.png", 1920, 1080);
    putimage(0, 0, &Tell);
    char key;
    if (AtTell)
    {
        while (1)
        {
            if (AtTell)
            {
                key = _getch();
                if (key == 27)
                {
                    AtTell = 0;
                    DCMP = 1;
                    AtPD = 1;
                    break;
                }
                if (key == 13)
                {
                    AtTell = 0;
                    AtDCM = 1;
                    break;
                }
            }
        }
    }
    To();
}

void Tetris::ToPM()
{
    //加载图片
    for (int i(0); i < 8; i++)
    {
        switch (i)
        {
        case 0:
            loadimage(&PM[i], "res\\PM\\Rain.png", 720, 480);
            break;
        case 1:
            loadimage(&PM[i], "res\\PM\\Snow.png", 720, 480);
            break;
        case 2:
            loadimage(&PM[i], "res\\PM\\Dawn.png", 720, 480);
            break;
        case 3:
            loadimage(&PM[i], "res\\PM\\2010.png", 720, 480);
            break;
        case 4:
            loadimage(&PM[i], "res\\PM\\2014.png", 720, 480);
            break;
        case 5:
            loadimage(&PM[i], "res\\PM\\1.png", 720, 480);
            break;
        case 6:
            loadimage(&PM[i], "res\\PM\\2.png", 720, 480);
            break;
        case 7:
            loadimage(&PM[i], "res\\PM\\3.png", 720, 480);
            break;
        }
    }
    //画出第一个图片
    int State = 0;
    putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &PM[State]);

    char key;
    if (AtPM)
    {
        while (1)
        {
            if (AtPM)
            {
                key = _getch();
                if (key == 75 || key == 'A' || key == 'a')
                {
                    if (State >= 0 && State <= 2)
                    {
                        if (State != 0)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 2;
                        }
                    }
                    else if (State >= 3 && State <= 4)
                    {
                        if (State != 3)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 4;
                        }
                    }
                    else 
                    {
                        if (State != 5)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 7;
                        }
                    }
                }
                if (key == 77 || key == 'D' || key == 'd')
                {
                    if (State >= 0 && State <= 2)
                    {
                        if (State != 2)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 0;
                        }
                    }
                    else if (State >= 3 && State <= 4)
                    {
                        if (State != 4)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 3;
                        }
                    }
                    else 
                    {
                        if (State != 7)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 5;
                        }
                    }
                }
                if (key == 80 || key == 'S' || key == 's')
                {
                    if (State >= 0 && State <= 2)
                    {
                        switch (State)
                        {
                        case 0:
                            State = 3;
                            break;
                        case 1:
                            State = 4;
                            break;
                        case 2:
                            State = 3;
                            break;
                        }
                    }
                    else if (State >= 3 && State <= 4)
                    {
                        switch (State)
                        {
                        case 3:
                            State = 5;
                            break;
                        case 4:
                            State = 6;
                            break;
                        }
                    }
                    else 
                    {
                        switch (State)
                        {
                        case 5:
                            State = 0;
                            break;
                        case 6:
                            State = 1;
                            break;
                        case 7:
                            State = 2;
                            break;
                        }
                    }
                }
                if (key == 72 || key == 'W' || key == 'w')
                {
                    if (State >= 0 && State <= 2)
                    {
                        switch (State)
                        {
                        case 0:
                            State = 5;
                            break;
                        case 1:
                            State = 6;
                            break;
                        case 2:
                            State = 7;
                            break;
                        }
                    }
                    else if (State >= 3 && State <= 4)
                    {
                        switch (State)
                        {
                        case 3:
                            State = 0;
                            break;
                        case 4:
                            State = 1;
                            break;
                        }
                    }
                    else if (State >= 5 && State <= 7)
                    {
                        switch (State)
                        {
                        case 5:
                            State = 3;
                            break;
                        case 6:
                            State = 4;
                            break;
                        case 7:
                            State = 3;
                            break;
                        }
                    }
                }
                if (key == 27)
                {
                    AtPM = 0;
                    AtPause = 1;
                    break;
                }
                if (key == 13)
                {
                    AtPM = 0;
                    AtPause = 1;
                    switch (State)
                    {
                    case 0:
                        SetTheme(0);
                        Cur->BlockReload();
                        Next->BlockReload();
                        break;
                    case 1:
                        SetTheme(1);
                        Cur->BlockReload();
                        Next->BlockReload();
                        break;
                    case 2:
                        SetTheme(2);
                        Cur->BlockReload();
                        Next->BlockReload();
                        break;
                    case 3:
                        At2010 = 1;
                        At2014 = 0;
                        To2010();
                        break;
                    case 4:
                        At2014 = 1;
                        At2010 = 0;
                        To2014();
                        break;
                    case 5:
                        Rate = 1;
                        ResetCD();
                        break;
                    case 6:
                        Rate = 2;
                        ResetCD();
                        break;
                    case 7:
                        Rate = 3;
                        ResetCD();
                        break;
                    }
                    break;
                }
                putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &PM[State]);
            }
        }
    }
    To();

}

void Tetris::ToMusic()
{
    int isESC = 0;

    //加载图片
    for (int i(0); i < 13; i++)
    {
        switch (i)
        {
        case 0:
            loadimage(&Music[i], "res\\Music\\Draw\\随机播放.png", 720, 480);
            break;
        case 1:
            loadimage(&Music[i], "res\\Music\\Draw\\单曲循环.png", 720, 480);
            break;
        case 2:
            loadimage(&Music[i], "res\\Music\\Draw\\静音.png", 720, 480);
            break;
        case 3:
            loadimage(&Music[i], "res\\Music\\Draw\\SS.png", 720, 480);
            break;
        case 4:
            loadimage(&Music[i], "res\\Music\\Draw\\LG.png", 720, 480);
            break;
        case 5:
            loadimage(&Music[i], "res\\Music\\Draw\\HT.png", 720, 480);
            break;
        case 6:
            loadimage(&Music[i], "res\\Music\\Draw\\BDC.png", 720, 480);
            break;
        case 7:
            loadimage(&Music[i], "res\\Music\\Draw\\DH.png", 720, 480);
            break;
        case 8:
            loadimage(&Music[i], "res\\Music\\Draw\\C.png", 720, 480);
            break;
        case 9:
            loadimage(&Music[i], "res\\Music\\Draw\\FD.png", 720, 480);
            break;
        case 10:
            loadimage(&Music[i], "res\\Music\\Draw\\Damascus.png", 720, 480);
            break;
        case 11:
            loadimage(&Music[i], "res\\Music\\Draw\\Dawn.png", 720, 480);
            break;
        case 12:
            loadimage(&Music[i], "res\\Music\\Draw\\CR.png", 720, 480);
            break;
        }
    }
    //画出第一个图片
    int State = 0;
    putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &Music[State]);

    char key;
    if (AtMusic)
    {
        while (1)
        {
            if (AtMusic)
            {
                key = _getch();
                if (key == 75 || key == 'A' || key == 'a')
                {
                    if (State >= 0 && State <= 2)
                    {
                        if (State != 0)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 2;
                        }
                    }
                    else if (State >= 3 && State <= 4)
                    {
                        if (State != 3)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 4;
                        }
                    }
                    else if(State>=5&&State<=7)
                    {
                        if (State != 5)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 7;
                        }
                    }
                    else if (State >= 8 && State <= 10)
                    {
                        if (State != 8)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 10;
                        }
                    }
                    else if (State >= 11 && State <= 12)
                    {
                        if (State != 11)
                        {
                            State -= 1;
                        }
                        else
                        {
                            State = 12;
                        }
                    }
                }
                if (key == 77 || key == 'D' || key == 'd')
                {
                    if (State >= 0 && State <= 2)
                    {
                        if (State != 2)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 0;
                        }
                    }
                    else if (State >= 3 && State <= 4)
                    {
                        if (State != 4)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 3;
                        }
                    }
                    else if(State>=5&&State<=7)
                    {
                        if (State != 7)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 5;
                        }
                    }
                    else if (State >= 8 && State <= 10)
                    {
                        if (State != 10)
                        {
                            State += 1;
                        }
                        else
                        {
                            State = 8;
                        }
                    }
                    else if(State >= 11 && State <= 12)
                        {
                            if (State != 12)
                            {
                                State += 1;
                            }
                            else
                            {
                                State = 11;
                            }
                        }
                    }
                }
                if (key == 80 || key == 'S' || key == 's')
                {
                    if (State >= 0 && State <= 2)
                    {
                        switch (State)
                        {
                        case 0:
                            State = 3;
                            break;
                        case 1:
                            State = 4;
                            break;
                        case 2:
                            State = 3;
                            break;
                        }
                    }
                    else if (State >= 3 && State <= 4)
                    {
                        switch (State)
                        {
                        case 3:
                            State = 6;
                            break;
                        case 4:
                            State = 7;
                            break;
                        }
                    }
                    else if(State>=5&&State<=7)
                    {
                        switch (State)
                        {
                        case 5:
                            State = 8;
                            break;
                        case 6:
                            State = 9;
                            break;
                        case 7:
                            State = 10;
                            break;
                        }
                    }
                    else if (State >= 8 && State <= 10)
                    {
                        switch (State)
                        {
                        case 8:
                            State = 11;
                            break;
                        case 9:
                            State = 12;
                            break;
                        case 10:
                            State = 11;
                            break;
                        }
                    }
                    else if (State >= 11 && State <= 12)
                    {
                        switch (State)
                        {
                        case 11:
                            State = 0;
                            break;
                        case 12:
                            State = 1;
                            break;
                        }
                    }
                }
                if (key == 72 || key == 'W' || key == 'w')
                {
                    if (State >= 0 && State <= 2)
                    {
                        switch (State)
                        {
                        case 0:
                            State = 11;
                            break;
                        case 1:
                            State = 12;
                            break;
                        case 2:
                            State = 11;
                            break;
                        }
                    }
                    else if (State >= 3 && State <= 4)
                    {
                        switch (State)
                        {
                        case 3:
                            State = 0;
                            break;
                        case 4:
                            State = 1;
                            break;
                        }
                    }
                    else if (State >= 5 && State <= 7)
                    {
                        switch (State)
                        {
                        case 5:
                            State = 3;
                            break;
                        case 6:
                            State = 3;
                            break;
                        case 7:
                            State = 4;
                            break;
                        }
                    }
                    else if (State >= 8 && State <= 10)
                    {
                        switch (State)
                        {
                        case 8:
                            State = 5;
                            break;
                        case 9:
                            State = 6;
                            break;
                        case 10:
                            State = 7;
                            break;
                        }
                    }
                    else if (State >= 11 && State <= 12)
                    {
                        switch (State)
                        {
                        case 11:
                            State = 8;
                            break;
                        case 12:
                            State = 9;
                            break;
                        }
                    }
                }
                if (key == 27)
                {
                    AtMusic = 0;
                    isESC = 1;
                    if (DCMP)
                    {
                        AtPD = 1;
                    }
                    else 
                    {
                        AtPause = 1;
                    }
                    break;
                }
                if (key == 13)
                {
                    AtMusic = 0;
                    if (DCMP)
                    {
                        AtPD = 1;
                    }
                    else
                    {
                        AtPause = 1;
                    }
                   
                    break;
                }
                putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &Music[State]);
               
            }
        }
    if (!isESC)
    {
        if (3 <= State && State <= 12)
        {
            if (Music::isRand)
            {
                MM.SetMID(State - 3);
                MM.SetRand(1, 1);
                MM.PlayMusic();
            }
            else if (!Music::isPause)
            {
                MM.SetMID(State - 3);
                MM.PlayMusic();
            }
        }
        else
        {
            switch (State)
            {
            case 0:
                MM.SetModol(2);
                MM.PlayMusic();
                break;
            case 1:
                MM.SetModol(1);
                MM.PlayMusic();
                break;
            case 2:
                MM.SetModol(0);
                MM.PlayMusic();
                MM.SetModol(Music::origin);
                break;
            }
        }
        
    }
    To();

}


void Tetris::PrintNext()
{
    //存储预告方块的信息
    int Row[4], Col[4];
    int X[4], Y[4];
    for (int i(0); i < 4; i++)
    {
        Row[i]=Next->GetRow(i);
        Col[i] = Next->GetCol(i);
    }
    for (int i(0); i < 4; i++)
    {
        X[i] = Row[i] * Block::BlockSize + NextT;
        Y[i] = Col[i] * Block::BlockSize + NextL;
    }

    //对方块进行预告，固定在右上角边框
    for (int i(0); i < 4; i++)
    {
        putimage(Y[i], X[i], &BlockBase[Next->GetType() - 1]);
    }
}

void Tetris::PrintScore()
{
    string s = "分数:";
    char l[7] = {};
    strcpy_s(l, s.c_str());
    setbkmode(TRANSPARENT);
    settextcolor(RGB(141, 225, 87));
    settextstyle(Block::BlockSize*2, Block::BlockSize/2, "Aptos Black");
    outtextxy(ScoreL - BaseBlock::BlockSize * 1, ScoreT, l);

    char num[10] = {};
    string st = to_string(scores);
    strcpy_s(num, st.c_str());
    setbkmode(TRANSPARENT);
    settextcolor(RGB(141,225,87));
    settextstyle(Block::BlockSize*2, Block::BlockSize, "Aptos Black");
    outtextxy(ScoreL+ BaseBlock::BlockSize * 2, ScoreT, num);

}

void Tetris::PrintLevel()
{
    string s = "Level:";
    char l[7] = {};
    strcpy_s(l, s.c_str());
    setbkmode(TRANSPARENT);
    settextcolor(RGB(0, 200, 250));
    settextstyle(Block::BlockSize * 2, Block::BlockSize, "Aptos Black");
    outtextxy(LevelL-BaseBlock::BlockSize*3, LevelT, l);

    char num[2] = {};
    string st = to_string(level);
    strcpy_s(num, st.c_str());
    setbkmode(TRANSPARENT);
    settextcolor(RGB(0, 200, 250));
    settextstyle(Block::BlockSize * 2, Block::BlockSize, "Aptos Black");
    outtextxy(LevelL+ BaseBlock::BlockSize * 3, LevelT, num);
}

void Tetris::PrintRank()
{
    ifstream rd;
    int n1, n2, n3, n4, n5;//5个无用int去掉score前面的五个数据
    for (int i(0); i < 5; i++)
    {
        switch (i)
        {
        case 0:
            rd.open("Document\\存档一.txt");
            break;
        case 1:
            rd.open("Document\\存档二.txt");
            break;
        case 2:
            rd.open("Document\\存档三.txt");
            break;
        case 3:
            rd.open("Document\\存档四.txt");
            break;
        case 4:
            rd.open("Document\\存档五.txt");
            break;
        }

        rd.read((char*)&RID[i], sizeof(RID[i]));

        rd.read((char*)&n1, sizeof(n1));

        rd.read((char*)&n2, sizeof(n2));

        rd.read((char*)&n3, sizeof(n3));

        rd.read((char*)&n4, sizeof(n4));

        rd.read((char*)&rank[i], sizeof(rank[i]));
        rd.close();
    }
    int rankback[5], RIDback[5];
    for (int i(0); i < 5; i++)
    {
        rankback[i] = rank[i], RIDback[i] = RID[i];
    }

    //冒泡排序，小的往前
    bool ischange = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (rank[j] > rank[j + 1]) {
                ischange = 1;
                int temp1 = rank[j],temp2 = RID[j];
                rank[j] = rank[j + 1];
                rank[j + 1] = temp1;
                RID[j] = RID[j + 1];
                RID[j + 1] = temp2;
            }
        }
        if (!ischange) 
        {
            break;
        }
        else 
        {
            ischange = false;
        }
    }

    //逐个输出前三名
    RankOut(0, RID[4], rank[4]);
    RankOut(1, RID[3], rank[3]);
    RankOut(2, RID[2], rank[2]);
}


void Tetris::SetTheme(int theme)
{
    Block::SetTheme(theme);

    //设置完主题后对各类图片进行重置
    switch (BaseBlock::theme)
    {
    case 0:
        loadimage(&BlockRes, "res\\Blocks\\Rain\\Blocks.jpg", Block::BlockSize * 7, Block::BlockSize);//加载方块图片（7方块相连）

        //切割出7种基元图片
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * Block::BlockSize, 0, Block::BlockSize, Block::BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 1:
        loadimage(&BlockRes, "res\\Blocks\\Snow\\Blocks.jpg", Block::BlockSize * 7, Block::BlockSize);//加载方块图片（7方块相连）

        //切割出7种基元图片
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * Block::BlockSize, 0, Block::BlockSize, Block::BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    case 2:
        loadimage(&BlockRes, "res\\Blocks\\Dawn\\Blocks.jpg", Block::BlockSize * 7, Block::BlockSize);//加载方块图片（7方块相连）

        //切割出7种基元图片
        SetWorkingImage(&BlockRes);
        for (int i(0); i < 7; i++)
        {
            getimage(&BlockBase[i], i * Block::BlockSize, 0, Block::BlockSize, Block::BlockSize);
        }
        SetWorkingImage(NULL);
        break;
    }
}

void Tetris::Trans()
{
    Cur = Next;//将预告方块加载到现在方块
    Next = new Block;//新创预告方块
    srand(time(NULL));
    Next->SetType(rand() % 7 + 1);
    //随机生成type并设置Next的属性
    Next->SetPro(Next->GetType());
}

void Tetris::ToDCC()
{
    //加载图片
    for (int i(0); i < 2; i++)
    {
        switch (i)
        {
        case 0:
            loadimage(&DCC[i], "res\\Document\\读取.png", 720, 480);
            break;
        case 1:
            loadimage(&DCC[i], "res\\Document\\重置.png", 720, 480);
            break;
        }
    }

    //画出第一个图片
    putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &DCC[0]);

    char key;

    if (AtDCC)
    {
        while (1)
        {
            if (AtDCC)
            {
                key = _getch();
                if (key == 75 || key == 'A' || key == 'a')
                {
                    if (CState != 0)
                    {
                        CState -= 1;
                    }
                    else
                    {
                        CState = 1;
                    }
                }
                if (key == 77 || key == 'D' || key == 'd')
                {
                    if (CState != 1)
                    {
                        CState += 1;
                    }
                    else
                    {
                        CState = 0;
                    }
                }
                if (key == 27)
                {
                    AtDCC = 0;
                    DCMP = 1;
                    AtPD = 1;
                    break;
                }
                if (key == 13)
                {
                    AtDCC = 0;
                    AtGame = 1;
                    break;
                }
                putimage(BaseBlock::BlockSize * 12, BaseBlock::BlockSize * 7, &DCC[CState]);
            }
        }
    }
    if(!CState)
    {
        RD();
        Cur->BlockReload();
        Next->BlockReload();
        CState = 0;
    }
    else 
    {
        CState = 0;
        DCReset();
        RD();
        SetTheme(0);
        Cur->BlockReload();
        Next->BlockReload();
        Again();

    }
    To();
}

int Tetris::Run()
{
    MM.SetModol(1);
    MM.SetMID(4);
    MM.PlayMusic();
    for (int stop(1); stop != 0;)
    {
        char pause;
        while (1)
        {
            if (AtStart)
            {
                if (StartDraw)
                {
                    ToStart();
                    StartDraw = 0;
                }
                pause = _getch();
            }
            if (pause == 13)
            {
                AtTell = 1;
                AtStart = 0;
            }
            break;
            if (pause == 27)
            {
                stop = 0;
                AtStart = 0;
                break;
            }
        }
        if (pause == 13)
        {
            To();
            return 0;
        }
        else if (pause == 27)
        {
            closegraph();
            return 0;
        }
    }
}