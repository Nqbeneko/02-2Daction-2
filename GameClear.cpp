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
#include"GameTime.h"
#include"SE.h"

void GameClear::Init()
{
	Clear = false;
	AnimationEnd = false;

	Graph = LoadGraph("img/font/GAME CLEAR.png", TRUE);
	StopTimer = 0;
}

void GameClear::Progress(Player& player, Boss& boss, Map& map, float deltaTime, Timer* time, int fontHandle1, int fontHandle3, SE* se)
{
	if (!Clear)
	{		
		boss.animNowPattern = 0;
		boss.animTimer = 0.0f;
		boss.state = BossState::Dead;
		boss.FlashingBoss = false;
		Clear = true;
		AnimationEnd = false;
		se->PlayBoss(BossSEnum::DethSE);
	}

    DrawMap(map);
	
	if (!AnimationEnd && Clear)
	{		
		
		//DrawBox(0, 0, ScreenWidth, ScreenHeight, GetColor(232, 232, 232), TRUE);
		DrawDeadBoss(boss);
		StopTimer += 1.0f;
		if (StopTimer >= 50.0f)
		{
			se->StopBoss(BossSEnum::DethSE); 
			boss.animNowType = Deth;
			boss.animPattern = DethAnimBoss;
			UpdateAnimationBoss(boss, deltaTime);
			if (boss.animNowPattern == boss.animPattern)
			{
				AnimationEnd = true;
				
			}
		}
		DrawPlayer(player);
	}

	if (AnimationEnd && Clear)
	{

		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
		DrawBox(0, 230, 800, 400, GetColor(0,0,0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawPlayer(player);

		time->DrawClearTimeandRank(fontHandle1,player);
		DrawRotaGraph3(ScreenWidth / 2, ScreenHeight / 3, 250 / 2, 32 / 2, 3, 3, 0, Graph, TRUE, FALSE);
		
		DrawFormatStringToHandle(270, 350, GetColor(236, 236, 236), fontHandle3, "Press BACK to TITLE.");
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
