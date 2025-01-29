#include"DxLib.h"
#include"screen.h"
#include"player.h"
#include"map.h"
#include"Boss.h"
#include"collision.h"
#include"Debug.h"
#include"Effect.h"
#include"GameOver.h"
#include"GameClear.h"

void GameClear::Init()
{
	Clear = false;
	AnimationEnd = false;

	Graph = LoadGraph("img/font/GAME CLEAR.png", TRUE);
	StopTimer = 0;
}

void GameClear::Progress(Player& player, Boss& boss, Map& map, float deltaTime)
{
	if (!Clear)
	{
		
		boss.animNowPattern = 0;
		boss.animTimer = 0.0f;
		boss.state = BossState::Dead;
		boss.FlashingBoss = false;
		Clear = true;
		AnimationEnd = false;
	}

	DrawBox(0, 0, ScreenWidth, ScreenHeight, GetColor(225, 225, 225), TRUE);

	
	if (!AnimationEnd && Clear)
	{
		
		DrawDeadBoss(boss);
		StopTimer += 1.0f;
		if (StopTimer >= 50.0f)
		{
			boss.animNowType = Deth;
			boss.animPattern = DethAnimBoss;
			UpdateAnimationBoss(boss, deltaTime);
			if (boss.animNowPattern == boss.animPattern)
			{
				AnimationEnd = true;
			}
		}

	}

	if (AnimationEnd && Clear)
	{
		//SetFontSize(50);
		//DrawString(ScreenWidth / 2 - 50 / 2 * 12 / 2, ScreenHeight / 3, "GAME CLEAR", GetColor(0, 255, 0));
		DrawRotaGraph3(ScreenWidth / 2, ScreenHeight / 3, 250 / 2, 32 / 2, 3, 3, 0, Graph, TRUE, FALSE);
		SetFontSize(30);
		DrawString(ScreenWidth / 2 - 30 / 2 * 21 / 2, ScreenHeight * 2 / 3, "Press BACK to TITLE.", GetColor(10, 10, 10));


	}


}


void GameClear::DrawDeadBoss(Boss& boss)
{
	if (boss.RightMove)
	{
		DrawRotaGraph3(static_cast<int>(boss.pos.x), static_cast<int>(boss.pos.y), boss.w / 2, boss.h / 2, 2.5, 2.5, 0, boss.BossGraph[boss.animNowType][boss.animNowPattern], TRUE, TRUE);
	}
	if (!boss.RightMove)
	{
		DrawRotaGraph3(static_cast<int>(boss.pos.x), static_cast<int>(boss.pos.y), boss.w / 2, boss.h / 2, 2.5, 2.5, 0, boss.BossGraph[boss.animNowType][boss.animNowPattern], TRUE, FALSE);
	}
}
