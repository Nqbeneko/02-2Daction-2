#include"DxLib.h"
#include"GameTime.h"
#include"screen.h"
#include"player.h"

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
	if (GameTime / 60.0f < 1)
	{
		if ((GameTime - (float)((int)GameTime / 60) * 60) < 10)
		{
			DrawFormatStringToHandle(650, 10, GetColor(185, 194, 196), fontHandle, "0:0%.2f", (GameTime - (float)((int)GameTime / 60) * 60));
		}
		else
		{
			DrawFormatStringToHandle(650, 10, GetColor(185, 194, 196), fontHandle, "0:%.2f", (GameTime - (float)((int)GameTime / 60) * 60));
		}
		
	}
	else
	{
		if ((GameTime - (float)((int)GameTime / 60) * 60) < 10)
		{
			DrawFormatStringToHandle(650, 10, GetColor(185, 194, 196), fontHandle, "%d:0%.2f", (int)GameTime / 60, (GameTime - (float)((int)GameTime / 60) * 60));
		}
		else
		{
			DrawFormatStringToHandle(650, 10, GetColor(185, 194, 196), fontHandle, "%d:%.2f", (int)GameTime / 60, (GameTime - (float)((int)GameTime / 60) * 60));
		}		
	}
	
	//DrawFormatStringToHandle(40, 30, GetColor(255, 255, 255), fontHandle, "%f", GameTime);

}

void Timer::DrawClearTimeandRank(int fontHandle, Player& player)
{
	//DrawFormatStringToHandle(230, 250, GetColor(236, 236, 236), fontHandle, "TIME %d:%d", (int)GameTime / 60, (int)GameTime % 60);
	if (GameTime / 60.0f < 1)
	{
		if ((GameTime - (float)((int)GameTime / 60) * 60) < 10)
		{
			DrawFormatStringToHandle(250, 290, GetColor(236, 236, 236), fontHandle, "TIME : 0m 0%.2fs", (GameTime - (float)((int)GameTime / 60) * 60));
		}
		else
		{
			DrawFormatStringToHandle(250, 290, GetColor(236, 236, 236), fontHandle, "TIME : 0m %.2fs", (GameTime - (float)((int)GameTime / 60) * 60));
		}

	}
	else
	{
		if ((GameTime - (float)((int)GameTime / 60) * 60) < 10)
		{
			DrawFormatStringToHandle(250, 290, GetColor(236, 236, 236), fontHandle, "TIME : %dm 0%.2fs", (int)GameTime / 60, (GameTime - (float)((int)GameTime / 60) * 60));
		}
		else
		{
			DrawFormatStringToHandle(250, 290, GetColor(236, 236, 236), fontHandle, "TIME : %dm %.2fs", (int)GameTime / 60, (GameTime - (float)((int)GameTime / 60) * 60));
		}
	}
	DrawFormatStringToHandle(247, 250, GetColor(236, 236, 236), fontHandle, "RANK : ");
	TimeRank(fontHandle,player);
}

void Timer::DrawOverTime(int fontHandle)
{
	//DrawFormatStringToHandle(320, 250, GetColor(177,20,29), fontHandle, "TIME %d:%d", (int)GameTime / 60, (int)GameTime % 60);

	if (GameTime / 60.0f < 1)
	{
		if ((GameTime - (float)((int)GameTime / 60) * 60) < 10)
		{
			DrawFormatStringToHandle(250, 250, GetColor(177, 20, 29), fontHandle, "TIME : 0m 0%.2fs", (GameTime - (float)((int)GameTime / 60) * 60));
		}
		else
		{
			DrawFormatStringToHandle(250, 250, GetColor(177, 20, 29), fontHandle, "TIME : 0m %.2fs", (GameTime - (float)((int)GameTime / 60) * 60));
		}

	}
	else
	{
		if ((GameTime - (float)((int)GameTime / 60) * 60) < 10)
		{
			DrawFormatStringToHandle(250, 250, GetColor(177, 20, 29), fontHandle, "TIME : %dm 0%.2fs", (int)GameTime / 60, (GameTime - (float)((int)GameTime / 60) * 60));
		}
		else
		{
			DrawFormatStringToHandle(250, 250, GetColor(177, 20, 29), fontHandle, "TIME : %dm %.2fs", (int)GameTime / 60, (GameTime - (float)((int)GameTime / 60) * 60));
		}
	}

}


void Timer::TimeRank(int fontHandle, Player& player)
{
	if (GameTime <= 30.0f && player.HP >= 5)
	{
		//Sランク
		DrawFormatStringToHandle(400, 250, GetColor(255, 215, 89), fontHandle, "S");
	}
	else if (GameTime <= 90.0f && player.HP >= 3)
	{
		//Aランク
		DrawFormatStringToHandle(400, 250, GetColor(206,0,221), fontHandle, "A");
	}
	else if (GameTime <= 180.0f && player.HP >= 1)
	{
		//Bランク
		DrawFormatStringToHandle(400, 250, GetColor(0, 95, 185), fontHandle, "B");
	}
	else if (player.HP >= 1)
	{
		//Cランク
		DrawFormatStringToHandle(400, 250, GetColor(87, 200, 0), fontHandle, "C");
	}
}