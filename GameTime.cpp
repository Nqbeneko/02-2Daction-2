#include"DxLib.h"
#include"GameTime.h"
#include"screen.h"

void Timer::Init()
{
	GameTime = 0.0f;
	RankNumber = 0;
}

void Timer::CountTime()
{
	GameTime += 1.0f / 60.0f;
}


void Timer::DrawTime(int fontHandle)
{
	DrawFormatStringToHandle(350,10, GetColor(185, 194, 196), fontHandle, "TIME %d:%d", (int)GameTime / 60, (int)GameTime % 60);
	//DrawFormatStringToHandle(40, 30, GetColor(255, 255, 255), fontHandle, "%f", GameTime);

}

void Timer::DrawClearTimeandRank(int fontHandle)
{
	DrawFormatStringToHandle(230, 250, GetColor(236, 236, 236), fontHandle, "TIME %d:%d", (int)GameTime / 60, (int)GameTime % 60);
	DrawFormatStringToHandle(430, 250, GetColor(236, 236, 236), fontHandle, "RANK");
	TimeRank(fontHandle);
}

void Timer::DrawOverTime(int fontHandle)
{
	DrawFormatStringToHandle(320, 250, GetColor(177,20,29), fontHandle, "TIME %d:%d", (int)GameTime / 60, (int)GameTime % 60);

}


void Timer::TimeRank(int fontHandle)
{
	if (GameTime <= 30.0f)
	{
		//Sランク
		DrawFormatStringToHandle(540, 250, GetColor(255, 215, 89), fontHandle, "S");
	}
	else if (GameTime <= 90.0f)
	{
		//Aランク
		DrawFormatStringToHandle(540, 250, GetColor(120,75,172), fontHandle, "A");
	}
	else if (GameTime <= 180.0f)
	{
		//Bランク
		DrawFormatStringToHandle(540, 250, GetColor(0, 95, 185), fontHandle, "B");
	}
	else if (GameTime >= 180.0f)
	{
		//Cランク
		DrawFormatStringToHandle(540, 250, GetColor(87, 200, 0), fontHandle, "C");
	}
}