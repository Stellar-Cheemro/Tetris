#include"Music.h"

int Music::modol = 0;
int Music::isPause = 0;
int Music::isCycle = 0;
int Music ::isRand = 0;
int Music::origin = 1;
Music::Music()
{
	modol = 0;
	MID = 4;

	isRandBack = 0;

	isPlaying = 1;
}
void Music::PlayMusic()
{


	switch (this->modol)
	{
	case 0:
		if (!isPause)
		{
			mciSendString("pause mp3", NULL, 0, NULL);
			isPause = 1;
			isPlaying = 0;
		}
		else
		{
			mciSendString("resume mp3", NULL, 0, NULL);
			isPause = 0;
			isPlaying = 1;
		}
		break;
	case 1:
		isPause = 0;
		origin = 1;
		OpenMusic();
		mciSendString("play mp3 repeat", NULL, 0, NULL);
		isPlaying = 1;
		isCycle = 1;
		isRand = 0;
		break;
	case 2:
		origin = 2;
		isPause = 0;
		isPlaying = 1;
		if (!isRandBack)
		{
			isRand = 1;
			while (isRand)
			{
				srand(time(NULL));
				SetMID(rand() % 10);
				OpenMusic();

				mciSendString("play mp3 repeat", NULL, 0, NULL);
				break;
			}
		}
		else
		{
			isRand = 1;
			isRandBack = 0;

			OpenMusic();
			mciSendString("play mp3 repeat", NULL, 0, NULL);
		}
	}
}

void Music::SetRand(int r,int rb)
{
	isRand = r;
	isRandBack = rb;
}
void Music::SetMID(int M)
{
	MID = M;
}
void Music::SetModol(int M)
{
	modol = M;
}

void Music::OpenMusic()
{
	if (isPlaying)
	{
		mciSendString("close mp3", NULL, 0, NULL);
	}
	switch (MID)
	{
	case 0:
		mciSendString("open \"res\\Music\\Siberian_Song.mp3\" alias mp3", NULL, 0, NULL);
		break;
	case 1:
		mciSendString("open \"res\\Music\\Landing_Guy.mp3\" alias mp3", NULL, 0, NULL);
		break;
	case 2:
		mciSendString("open \"res\\Music\\His_Theme.mp3\" alias mp3", NULL, 0, NULL);
		break;
	case 3:
		mciSendString("open \"res\\Music\\Baby_Don_not_cry.mp3\" alias mp3", NULL, 0, NULL);
		break;
	case 4:
		mciSendString("open \"res\\Music\\Delta_Heavy.mp3\" alias mp3", NULL, 0, NULL);
		break;
	case 5:
		mciSendString("open \"res\\Music\\Canon.mp3\" alias mp3", NULL, 0, NULL);
		break;
	case 6:
		mciSendString("open \"res\\Music\\Flower_Dance.mp3\" alias mp3", NULL, 0, NULL);
		break;
	case 7:
		mciSendString("open \"res\\Music\\Damascus.mp3\" alias mp3", NULL, 0, NULL);
		break;
	case 8:
		mciSendString("open \"res\\Music\\Dawn.mp3\" alias mp3", NULL, 0, NULL);
		break;
	case 9:
		mciSendString("open \"res\\Music\\Crotian_Rhapsody.mp3\" alias mp3", NULL, 0, NULL);
		break;
	}
}
void Music::Silence()
{
	SetModol(0);
	PlayMusic();
}
