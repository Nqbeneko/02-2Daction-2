//------------------------------------------------------------------
//　2Dアクションゲーム　プログラム
//  開始日→2024/10/23
//------------------------------------------------------------------
#include "DxLib.h"
#include "screen.h"
#include "player.h"
#include "map.h"
#include "Boss.h"
#include "collision.h"
#include "Debug.h"
#include "Effect.h"
#include "GameOver.h"
#include "Start.h"
#include "GameClear.h"
#include "BGM.h"
#include "SE.h"
#include "TITLE.h"
#include "GameTime.h"
#include "Help.h"

static int mStartTime;      //測定開始時刻
static int mCount;          //カウンタ
static float mFps;          //fps
static const int N = 60;	//平均を取るサンプル数
static const int FPS = 60;	//設定したFPS


bool Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void DrawFps() {
	SetFontSize(10);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	XINPUT_STATE input;
	// DxLib初期化
	SetGraphMode(ScreenWidth, ScreenHeight, 16);
	//ChangeWindowMode(true);
	ChangeWindowMode(false);

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//フォントの設定
	AddFontResourceExA("img/BestTen-CRT.otf", FR_PRIVATE, NULL);

	int fontHandle1 = CreateFontToHandle("ベストテン-CRT", 36, 2,DX_FONTTYPE_NORMAL);
	int fontHandle2 = CreateFontToHandle("ベストテン-CRT", 20, 2,DX_FONTTYPE_NORMAL);
	int fontHandle3 = CreateFontToHandle("ベストテン-CRT", 26, 2,DX_FONTTYPE_NORMAL);

	Player player;
	Map map;
	Boss boss;
	Soul soul[MaxSoulNum];
	Effect bossEffect;
	Effect playerEffect;

	TITLE* title = new TITLE;
	GameClear* clear = new GameClear;
	GameOver* over = new GameOver;
	Start* start = new Start;

	BGM* bgm = new BGM;
	SE* se = new SE;

	Timer* time = new Timer;

	Help* help = new Help;

	Collision Col_playerAttack_L;
	Collision Col_playerAttack_R;
	Collision Col_bossAttack1_L;
	Collision Col_bossAttack1_R;
	Collision Col_bossAttack2;

	enum class GameMode
	{
		TITLE,
		SETTING,
		GAME,
		OVER,
		CLEAR
	};
	
	struct Scene
	{
		GameMode mode;
	};

	Scene sceneSelect;
	sceneSelect.mode = GameMode::TITLE;

	//------------------------------------------------------
	// 初期化
	//------------------------------------------------------
	InitPlayer(player);
	InitMap(map);
	InitBoss(boss);
	InitSoul(soul);
	InitPlayerAttackCollision(Col_playerAttack_L, Col_playerAttack_R);
	InitBossAttackCollision(Col_bossAttack1_L, Col_bossAttack1_R,Col_bossAttack2);
	InitBossEffect(bossEffect);
	InitPlayerEffect(playerEffect);
	over->Init();
	start->Init();
	clear->Init();
	bgm->Init();
	se->Init();
	title->Init();
	time->Init();
	help->Init();

	int nowCount, prevCount;
	nowCount = prevCount = GetNowCount();

	int timer = 0;

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		//コントローラーの入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD1, &input);


		// deltaTime計測
		float deltaTime;
		nowCount = GetNowCount();
		deltaTime = (nowCount - prevCount) / 1000.0f;

		Update();	//Fps更新

		timer++;
		
		
		int num = -1;
	
			
		switch (sceneSelect.mode)
		{
		case GameMode::TITLE:

			DrawMap(map);
			if (!GetMovieStateToGraph(title->MoveGraph))
			{
				bgm->Play(BGMType::Title);
			}
			else
			{
				bgm->Stop();
				if (CheckHitKey(KEY_INPUT_F) || input.Buttons[XINPUT_BUTTON_A])
				{
					PauseMovieToGraph(title->MoveGraph);

				}
			}

			//タイトル画面を表示
			/*SetFontSize(50);
			DrawString(ScreenWidth / 2 - 50 / 2 * 12 / 2, ScreenHeight / 4, "NIGHT REAPER", GetColor(0, 0, 0));*/

			//スタートボタンを点滅させる
			if (timer % 30 < 20)
			{
				
				//DrawString(ScreenWidth / 2 - 30 / 2 * 21 / 2, ScreenHeight * 2 / 3 + 60, "Press START to start.", GetColor(238, 238, 238));
				SetFontSize(1000);
				DrawStringToHandle(ScreenWidth / 2 - 150, ScreenHeight * 2 / 3 + 60, "Press START to GAMEstart.", GetColor(238, 238, 238), fontHandle3);
			}
			
			title->Progress();

			if ((CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[XINPUT_BUTTON_START]) && !GetMovieStateToGraph(title->MoveGraph))
			{
				sceneSelect.mode = GameMode::GAME;
				se->PlaySystem();
				//------------------------------------------------------
				// 初期化
				//------------------------------------------------------
				InitPlayer(player);
				InitMap(map);
				InitBoss(boss);
				InitSoul(soul);
				InitPlayerAttackCollision(Col_playerAttack_L, Col_playerAttack_R);
				InitBossAttackCollision(Col_bossAttack1_L, Col_bossAttack1_R, Col_bossAttack2);
				InitBossEffect(bossEffect);
				InitPlayerEffect(playerEffect);
				over->Init();
				start->Init();
				clear->Init();
				bgm->Stop();
				time->Init();
				se->SetAllLargeVolume();
				PauseMovieToGraph(title->MoveGraph);
			}
			
			break;

		case GameMode::SETTING:
			break;

		case GameMode::GAME:
			bgm->Play(BGMType::Game);
			
			//------------------------------------------------------
			// GAMEモードが呼ばれて最初に行う処理
			//------------------------------------------------------
			if (!start->StartFlag)
			{
				start->Progress(player,boss,map);
			}

			//------------------------------------------------------
			// 更新処理
			//------------------------------------------------------
			DrawMap(map);
			if (start->StartFlag)
			{
				time->CountTime();
				//プレイヤーの攻撃とボスの当たり判定
				player.HitAttack = UpdateHitPlayerAttack(Col_playerAttack_L, Col_playerAttack_R, player, boss);
				boss.HitAttack = UpdateHitBossAttack(Col_bossAttack1_L, Col_bossAttack1_R, player, boss);

				UpdatePlayerAttackCollision(Col_playerAttack_L, Col_playerAttack_R, player);
				UpdateBossAttackCollision(Col_bossAttack1_L, Col_bossAttack1_R, Col_bossAttack2, boss);

				UpdateAnimationPlayer(player, boss, map, deltaTime, input, playerEffect,se,
										Col_playerAttack_L, Col_playerAttack_R);
				UpdateBoss(boss, soul, player, deltaTime,se);
				BossRushPreliminaryAction(bossEffect, boss);

				UpdateAnimationSoul(soul, deltaTime);
			}
			
				
			//------------------------------------------------------
			// 描画処理
			//------------------------------------------------------		
			
			DrawBoss(boss);
			DrawSoul(soul);

			DrawPlayer(player);
			DrawFps();
			DrawPlayerUI(player);
			DrawBossUI(boss);
			DrawBossEfect(bossEffect, boss);

			SelectDrawManageUI(player, boss, soul);

			time->DrawTime(fontHandle3);
			help->DrawHelp(fontHandle2);
			/*if (player.HitAttack)
			{
				DrawFormatString(50, 50, GetColor(255, 255, 255), "ヒットー");
			}
			if (boss.HitAttack)
			{
				DrawFormatString(50, 50, GetColor(0, 0, 255), "ヒットー");
			}*/
			//------------------------------------------------------
			if (player.HP <= 0)
			{
				sceneSelect.mode = GameMode::OVER;
				bgm->Stop();
				se->AllStopBoss();
				se->AllStopPlayer();
				se->SetAllLowVolume();
			}
			if (boss.HP <= 0)
			{
				sceneSelect.mode = GameMode::CLEAR;
				bgm->Stop();
				se->AllStopBoss();
				se->AllStopPlayer();
				se->SetAllLowVolume();

			}

			//------------------------------------------------------
			// デバック用
			//------------------------------------------------------
			if (CheckHitKey(KEY_INPUT_G))
			{
				sceneSelect.mode = GameMode::OVER;
				bgm->Stop();
				se->AllStopBoss();
				se->AllStopPlayer();
				se->SetAllLowVolume();

			}
			if (CheckHitKey(KEY_INPUT_H))
			{
				sceneSelect.mode = GameMode::CLEAR;
				bgm->Stop();
				se->AllStopBoss();
				se->AllStopPlayer();
				se->SetAllLowVolume();

			}
			//DrawBossPosition(boss);

			break;

		case GameMode::OVER:
			DrawMap(map);
			
			DrawBoss(boss);
			DrawBossEfect(bossEffect, boss);
			DrawSoul(soul);


			over->Progress(player,time, fontHandle1,fontHandle3,se);
			
			if (over->GetAnimEnd())
			{
				UpdateBoss(boss, soul, player, deltaTime,se);
				BossRushPreliminaryAction(bossEffect, boss);
				UpdateAnimationSoul(soul, deltaTime);
				bgm->Play(BGMType::Over);
			}

			if (CheckHitKey(KEY_INPUT_R) || input.Buttons[XINPUT_BUTTON_BACK])
			{
				sceneSelect.mode = GameMode::TITLE;
				bgm->Stop();
				se->AllStopBoss();
				se->AllStopPlayer();
				se->PlaySystem();
				title->timer = 0.0f;
			}
			break;

		case GameMode::CLEAR:
			
			clear->Progress(player, boss, map,deltaTime,time,fontHandle1,fontHandle3,se);
			
			if (clear->GetStopTimer() > 50.0f)
			{
				UpdateAnimationPlayer(player, boss, map, deltaTime, input, playerEffect,se,
					Col_playerAttack_L, Col_playerAttack_R);
				bgm->Play(BGMType::Clear);
				
			}
			
			
			
			if (CheckHitKey(KEY_INPUT_R) || input.Buttons[XINPUT_BUTTON_BACK])
			{
				sceneSelect.mode = GameMode::TITLE;
				bgm->Stop();
				se->AllStopBoss();
				se->AllStopPlayer();
				se->PlaySystem();
				title->timer = 0.0f;

			}
			
			break;
		default:
			break;
		}
		

		prevCount = nowCount;
		
		ScreenFlip();

		Wait();		//Fps待機
	}
	
	se->Delete();
	title->Delete();

	delete start;
	delete over;
	delete clear;
	delete title;
	delete bgm;
	delete se;
	
	DxLib_End;
	return 0;

}
