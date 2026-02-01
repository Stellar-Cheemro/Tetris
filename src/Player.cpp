#include "Player.h"

Player::Player()
{
	scores = 0;
	level = 1;
}

void Player::AddScores(int add)
{
	scores += add;
}

