#pragma once

struct Player;

class Timer
{
private:
	int Rank[4];
	int RankNumber;
	float GameTime;

public:
	void Init();

	void CountTime();

	void DrawTime(int fontHandle);

	void DrawClearTimeandRank(int fontHandle,Player& player);

	void DrawOverTime(int fontHandle);

	void TimeRank(int fontHandle,Player& player);
};
