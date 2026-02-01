#pragma once

#include<windows.h>
#include<iostream>
#include<mmsystem.h>
#include<stdlib.h>
#include<ctime>
#include<graphics.h>

using namespace std;

#pragma comment(lib, "Winmm.lib")

class Music
{
private:
	int MID;//播放音乐的序号

	int isPlaying;//用于切换音乐与播放方式时关闭mp3


	int isRandBack;//是否随机播放时主动切换音乐]

protected:
	static int modol;//播放方式
public:
	static int isPause;//是否静音，用于防止静音时主动切换音乐
	static int isCycle;//用于检测是否在循环
	static int isRand;//是否是随机
	static int origin;//记录原来状态
	Music();
	void PlayMusic();//播放音乐

	void SetRand(int r,int rb);
	//设置isRand和isRandBack用于Tetris中在随机播放时切换音乐

	void SetMID(int M);
	void SetModol(int M);

	void OpenMusic();
	//根据MID加载音乐


	void Silence();
	//静音
};
