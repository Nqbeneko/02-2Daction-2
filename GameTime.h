#pragma once

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

	void DrawClearTimeandRank(int fontHandle);

	void DrawOverTime(int fontHandle);

	void TimeRank(int fontHandle);
};
