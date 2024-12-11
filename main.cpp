//------------------------------------------------------------------
//　2Dアクションゲーム　プログラム
//  開始日→2024/10/23
//------------------------------------------------------------------
#include"DxLib.h"
#include"screen.h"
#include"player.h"
#include"map.h"
#include"Boss.h"
#include"collision.h"

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

	// DxLib初期化
	SetGraphMode(ScreenWidth, ScreenHeight, 16);
	ChangeWindowMode(false);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	Player player;
	Map map;
	Boss boss;
	Soul soul;

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
		CREAR
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
	InitPlayerAttackCollision(Col_playerAttack_L, Col_playerAttack_R);
	InitBossAttackCollision(Col_bossAttack1_L, Col_bossAttack1_R,Col_bossAttack2);


	int nowCount, prevCount;
	nowCount = prevCount = GetNowCount();

	int timer = 0;

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		// deltaTime計測
		float deltaTime;
		nowCount = GetNowCount();
		deltaTime = (nowCount - prevCount) / 1000.0f;

		Update();	//Fps更新

		timer++;
		switch (sceneSelect.mode)
		{
		case GameMode::TITLE:
			//タイトル画面を表示
			SetFontSize(50);
			DrawString(ScreenWidth / 2 - 50 / 2 * 12 / 2, ScreenHeight / 3, "DARK SAMURAI", GetColor(255, 69, 0));
			//スタートボタンを点滅させる
			if (timer % 60 < 30)
			{
				SetFontSize(30);
				DrawString(ScreenWidth / 2 - 30 / 2 * 21 / 2, ScreenHeight * 2 / 3, "Press SPACE to start.", GetColor(238, 130, 238));
			}
			
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				sceneSelect.mode = GameMode::GAME;
				//------------------------------------------------------
				// 初期化
				//------------------------------------------------------
				InitPlayer(player);
				InitMap(map);
				InitBoss(boss);
				InitPlayerAttackCollision(Col_playerAttack_L, Col_playerAttack_R);
				InitBossAttackCollision(Col_bossAttack1_L, Col_bossAttack1_R, Col_bossAttack2);
			}
			break;

		case GameMode::SETTING:
			break;

		case GameMode::GAME:

			//------------------------------------------------------
			// 更新処理
			//------------------------------------------------------
			DrawMap(map);
			//プレイヤーの攻撃とボスの当たり判定
			player.HitAttack = UpdateHitPlayerAttack(Col_playerAttack_L, Col_playerAttack_R, player, boss);
			boss.HitAttack = UpdateHitBossAttack(Col_bossAttack1_L, Col_bossAttack1_R, player, boss);

			UpdatePlayerAttackCollision(Col_playerAttack_L, Col_playerAttack_R, player);
			UpdateBossAttackCollision(Col_bossAttack1_L, Col_bossAttack1_R, Col_bossAttack2, boss);

			UpdateAnimationPlayer(player, boss, map, deltaTime);
			UpdateBoss(boss, soul, player);
			UpdateAnimationBoss(boss, soul, deltaTime);
			//------------------------------------------------------
			// 描画処理
			//------------------------------------------------------		
			DrawPlayer(player);
			DrawBoss(boss, soul, player);
			DrawFps();
			DrawPlayerUI(player);
			DrawBossUI(boss);

			if (player.HitAttack)
			{
				DrawFormatString(50, 50, GetColor(255, 255, 255), "ヒットー");
			}
			if (boss.HitAttack)
			{
				DrawFormatString(50, 50, GetColor(0, 0, 255), "ヒットー");
			}
			//------------------------------------------------------
			if (player.HP <= 0)
			{
				sceneSelect.mode = GameMode::OVER;
			}
			if (boss.HP <= 0)
			{
				sceneSelect.mode = GameMode::CREAR;
			}

			break;

		case GameMode::OVER:
			//タイトル画面を表示
			SetFontSize(50);
			DrawString(ScreenWidth / 2 - 50 / 2 * 12 / 2, ScreenHeight / 3, "GAME OVER", GetColor(255, 0, 0));
			
			break;

		case GameMode::CREAR:
			//タイトル画面を表示
			SetFontSize(50);
			DrawString(ScreenWidth / 2 - 50 / 2 * 12 / 2, ScreenHeight / 3, "GAME CREAR", GetColor(0, 255, 0));
			break;
		default:
			break;
		}
		

		prevCount = nowCount;
		
		ScreenFlip();

		Wait();		//Fps待機
	}

	DxLib_End;
	return 0;

}
