#pragma once

#include<windows.h>
#include<graphics.h>
#include<vector>
#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>

#include"BaseBlock.h"
#include"Block.h"
#include"Player.h"
#include"Music.h"

#pragma comment(lib, "Winmm.lib")

using namespace std;

class Tetris:public Player
{
private:

	Music MM;//音乐

	Block *Cur, *Next;//游戏进行时的方块
	Block* DCCur, * DCNext;//用于存档重置

	int rank[5], RID[5];//存档排名数组

	IMAGE Background;//游戏背景
	IMAGE MBG[2];//降落区背景
	//MBG[0]用于20*10，MBG[1]用于20*14

	IMAGE Start, Tell;//游戏开始贴图（Start）和选项说明贴图(Tell)

	IMAGE DCM[5], DCC[2];//存档界面
	//DCM：五个存存档进行选择，DCC：选择进入存档的方式（读取或者重写）

	IMAGE Pause[6], PD[3];//暂停界面
	//Pause：一般暂停图
	// PD：应用于存档界面的暂停图，防止在没有进行存档读取操作时返回游戏造成崩溃

	IMAGE Over[3];//游戏结束图片

	IMAGE Change[2];//换档时是否保存存档图片

	IMAGE PM[8];//设置参数界面（设置棋盘大小、速率、进入音乐界面）图片

	IMAGE Music[13];//音乐设置界面图片（音乐播放功能未完成）

	IMAGE Quit[2];//退出游戏时是否存档图片

	IMAGE L12, E27, L16;//边界图片
	IMAGE BlockRes;//整体图片（用来切割出7种基元图片）
	IMAGE BlockBase[7];//7种基元图片，一种类型方块对应一种图片


    vector<vector<int > > GameState;//20*10游戏进度
	vector<vector<int > > GameState2014;//20*14游戏进度

	//各数字位置
	int NextL, NextT;//预告下一个方块的坐标
	int ScoreL, ScoreT;//当前游戏分数的坐标
	int LevelL, LevelT;//当前游戏等级的坐标
	int RankL, RankT;//排名的坐标
	int TipL,TipT;//游戏操作提示的坐标

	bool AtStart, StartDraw;
	//用于判断在运行后是否已经画出开始界面，防止闪烁

	bool AtTell;
	//判断是否在选项说明界面

	//界面切换设置
	int At2010, At2014;
	//判断棋盘大小，使用int以写入存档使得排名功能读取正常

	bool AtGame;//判断是否在游戏进行界面

	bool AtDCM, AtDCC, DCMP;
	//检测是否在选档界面暂停，用于判断暂停时进入PD还是Pause;

	bool AtPause,AtPD;
	//判断暂停界面是哪一种

	bool AtChange;//换档时是否存档
	bool AtOver;//判断是否在游戏结束界面
	bool AtMusic;//判断是否在音乐设置界面
	bool AtPM;//判断是否在参数设置界面
	bool AtQuit;//判断是否在退出时存档与否的界面

	int Rate;//CD减少的速度倍率
	int Quick;//速降时的加大CD减少倍率

	static int CountDown;//方块下降
	static int DState,CState;
	
public:
	Tetris();
	~Tetris();

	void ResetCD();//重设CD
	void SetQuick(int i);//设置CD减少速度倍率

	void ResetPro();//在切换主题时重新设置Cur和Next的图片与现在的主题贴合

	void To();//根据At界面（如AtGame）进行切换界面
	void ToStart();//开始界面
	void ToTell();//说明操作
	void ToDCM();//选取存档 
	void ToDCC();//读档方式
	void ToGame();//游戏界面
	void ToPause();//暂停
	void ToPD();//换档界面暂停
	void ToOver();//游戏结束
	void ToChange();//换档时是否保存
	void ToMusic();//进入音乐设置界面
	void ToPM();//进入参数设置界面
	void ToQuit();//退出时是否存档

	void To2010();//棋盘大小切换
	void To2014();

	void CStateReset();//重置CState
	void Again();//重开重置进度

	void PrintCur();//打印Cur

	void Trans();//现在方块与下一方块交替

	void FullScreen();//全屏，在initial中
	void SetEdge();//放置边界，在SetBG中被使用
	void SetGS();//画出游戏进度
	void SetBG();//设置背景
	void PrintNext();//打印Next

	void PrintScore();//打印分数
	void PrintLevel();//打印难度
	void PrintRank();//整体打印排名，包括排序和逐个打印出
	void RankOut(int rank, int RID, int Rscores);//用于PrintRank内，单个打印出排名
	void PrintTip();//打印操作提示

	void BGReset();//背景重画（保留进度）
	void SetTheme(int theme);//设置主题
	void LevelUp();//判断分数是否到达标准以进行升级

	void KeyToDo(char);//处理S、A、D、Q、E以及开始时的ESC和回车键

	bool IsBottom();//判断是否触底,用于Fix
	bool OutIsBottom();//判断是否触底,用于OutFix()
	bool BydBottom();//在旋转中进行底框判定
	bool IsEdge();//判断是否接触左右边界
	bool BydEdge();//在旋转中进行左右边框判定
	bool IsTouch();//判断是否与其他方块相碰

	int Clean();//消行

	void Down();//方块下降
	void MoveLeft();//方块左移
	void MoveRight();//方块右移
	void Qturn(int);//顺时针旋转
	void Eturn(int);//逆时针旋转
	void Fix();//函数内部方块触底或者不能再下降时固定（在GameState和GameState2014里记录编号种类）

	void OutFix();//函数外部方块触底或者不能再下降时固定

	void DC();//保存存档
	void RD();//读取存档
	void DCReset();//存档重写

	int Run();//游戏主体
};


