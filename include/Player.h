#pragma once

#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<vector>

using namespace std;

class Player
{
protected:
	int Idex;//存档序号
	int scores;//存档分数
	int level;//存档等级

public:
	Player();
	void AddScores(int);//增加分数
};