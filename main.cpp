//------------------------------------------------------------------
//�@2D�A�N�V�����Q�[���@�v���O����
//  �J�n����2024/10/23
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

static int mStartTime;      //����J�n����
static int mCount;          //�J�E���^
static float mFps;          //fps
static const int N = 60;	//���ς����T���v����
static const int FPS = 60;	//�ݒ肵��FPS


bool Update() {
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
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
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//�ҋ@
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	XINPUT_STATE input;
	// DxLib������
	SetGraphMode(ScreenWidth, ScreenHeight, 16);
	//ChangeWindowMode(true);
	ChangeWindowMode(false);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	Player player;
	Map map;
	Boss boss;
	Soul soul[MaxSoulNum];
	Effect bossEffect;
	Effect playerEffect;

	GameClear* clear = new GameClear;
	GameOver* over = new GameOver;
	Start* start = new Start;

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
	// ������
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

	int nowCount, prevCount;
	nowCount = prevCount = GetNowCount();

	int timer = 0;

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		//�R���g���[���[�̓��͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD1, &input);

   		


		// deltaTime�v��
		float deltaTime;
		nowCount = GetNowCount();
		deltaTime = (nowCount - prevCount) / 1000.0f;

		Update();	//Fps�X�V

		timer++;
		switch (sceneSelect.mode)
		{
		case GameMode::TITLE:
			DrawMap(map);

			//�^�C�g����ʂ�\��
			SetFontSize(50);
			DrawString(ScreenWidth / 2 - 50 / 2 * 12 / 2, ScreenHeight / 4, "DARK SAMURAI", GetColor(0, 0, 0));
			//�X�^�[�g�{�^����_�ł�����
			if (timer % 60 < 30)
			{
				SetFontSize(30);
				DrawString(ScreenWidth / 2 - 30 / 2 * 21 / 2, ScreenHeight * 2 / 3, "Press START to start.", GetColor(238, 238, 238));
			}
			
			if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[XINPUT_BUTTON_START])
			{
				sceneSelect.mode = GameMode::GAME;
				//------------------------------------------------------
				// ������
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

			}
			break;

		case GameMode::SETTING:
			break;

		case GameMode::GAME:
			//------------------------------------------------------
			// GAME���[�h���Ă΂�čŏ��ɍs������
			//------------------------------------------------------
			if (!start->StartFlag)
			{
				start->Progress(player,boss,map);
			}

			//------------------------------------------------------
			// �X�V����
			//------------------------------------------------------
			DrawMap(map);
			if (start->StartFlag)
			{
				//�v���C���[�̍U���ƃ{�X�̓����蔻��
				player.HitAttack = UpdateHitPlayerAttack(Col_playerAttack_L, Col_playerAttack_R, player, boss);
				boss.HitAttack = UpdateHitBossAttack(Col_bossAttack1_L, Col_bossAttack1_R, player, boss);

				UpdatePlayerAttackCollision(Col_playerAttack_L, Col_playerAttack_R, player);
				UpdateBossAttackCollision(Col_bossAttack1_L, Col_bossAttack1_R, Col_bossAttack2, boss);

				UpdateAnimationPlayer(player, boss, map, deltaTime, input, playerEffect);
				UpdateBoss(boss, soul, player, deltaTime);
				BossRushPreliminaryAction(bossEffect, boss);

				UpdateAnimationSoul(soul, deltaTime);
			}
			
				
			//------------------------------------------------------
			// �`�揈��
			//------------------------------------------------------		
			
			DrawBoss(boss);
			DrawSoul(soul);

			DrawPlayer(player);
			DrawFps();
			DrawPlayerUI(player);
			DrawBossUI(boss);
			DrawBossEfect(bossEffect, boss);

			SelectDrawManageUI(player, boss, soul);
			/*if (player.HitAttack)
			{
				DrawFormatString(50, 50, GetColor(255, 255, 255), "�q�b�g�[");
			}
			if (boss.HitAttack)
			{
				DrawFormatString(50, 50, GetColor(0, 0, 255), "�q�b�g�[");
			}*/
			//------------------------------------------------------
			if (player.HP <= 0)
			{
				sceneSelect.mode = GameMode::OVER;
			}
			if (boss.HP <= 0)
			{
				sceneSelect.mode = GameMode::CLEAR;
			}

			//------------------------------------------------------
			// �f�o�b�N�p
			//------------------------------------------------------
			if (CheckHitKey(KEY_INPUT_G))
			{
				sceneSelect.mode = GameMode::OVER;
			}
			if (CheckHitKey(KEY_INPUT_H))
			{
				sceneSelect.mode = GameMode::CLEAR;
			}
			//DrawBossPosition(boss);

			break;

		case GameMode::OVER:
			
			over->Progress(player);
			

			if (CheckHitKey(KEY_INPUT_R) || input.Buttons[XINPUT_BUTTON_BACK])
			{
				sceneSelect.mode = GameMode::TITLE;
			}
			break;

		case GameMode::CLEAR:

			clear->Progress(player, boss, map,deltaTime);
			if (clear->GetStopTimer() > 50.0f)
			{
				UpdateAnimationPlayer(player, boss, map, deltaTime, input, playerEffect);
			}
			
			
			
			DrawPlayer(player);
			if (CheckHitKey(KEY_INPUT_R) || input.Buttons[XINPUT_BUTTON_BACK])
			{
				sceneSelect.mode = GameMode::TITLE;
			}
			
			break;
		default:
			break;
		}
		

		prevCount = nowCount;
		
		ScreenFlip();

		Wait();		//Fps�ҋ@
	}
	
	delete start;
	delete over;
	delete clear;
	DxLib_End;
	return 0;

}
