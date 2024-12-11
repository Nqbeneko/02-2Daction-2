//------------------------------------------------------------------
//�@2D�A�N�V�����Q�[���@�v���O����
//  �J�n����2024/10/23
//------------------------------------------------------------------
#include"DxLib.h"
#include"screen.h"
#include"player.h"
#include"map.h"
#include"Boss.h"
#include"collision.h"

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

	// DxLib������
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
	// ������
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
		// deltaTime�v��
		float deltaTime;
		nowCount = GetNowCount();
		deltaTime = (nowCount - prevCount) / 1000.0f;

		Update();	//Fps�X�V

		timer++;
		switch (sceneSelect.mode)
		{
		case GameMode::TITLE:
			//�^�C�g����ʂ�\��
			SetFontSize(50);
			DrawString(ScreenWidth / 2 - 50 / 2 * 12 / 2, ScreenHeight / 3, "DARK SAMURAI", GetColor(255, 69, 0));
			//�X�^�[�g�{�^����_�ł�����
			if (timer % 60 < 30)
			{
				SetFontSize(30);
				DrawString(ScreenWidth / 2 - 30 / 2 * 21 / 2, ScreenHeight * 2 / 3, "Press SPACE to start.", GetColor(238, 130, 238));
			}
			
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				sceneSelect.mode = GameMode::GAME;
				//------------------------------------------------------
				// ������
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
			// �X�V����
			//------------------------------------------------------
			DrawMap(map);
			//�v���C���[�̍U���ƃ{�X�̓����蔻��
			player.HitAttack = UpdateHitPlayerAttack(Col_playerAttack_L, Col_playerAttack_R, player, boss);
			boss.HitAttack = UpdateHitBossAttack(Col_bossAttack1_L, Col_bossAttack1_R, player, boss);

			UpdatePlayerAttackCollision(Col_playerAttack_L, Col_playerAttack_R, player);
			UpdateBossAttackCollision(Col_bossAttack1_L, Col_bossAttack1_R, Col_bossAttack2, boss);

			UpdateAnimationPlayer(player, boss, map, deltaTime);
			UpdateBoss(boss, soul, player);
			UpdateAnimationBoss(boss, soul, deltaTime);
			//------------------------------------------------------
			// �`�揈��
			//------------------------------------------------------		
			DrawPlayer(player);
			DrawBoss(boss, soul, player);
			DrawFps();
			DrawPlayerUI(player);
			DrawBossUI(boss);

			if (player.HitAttack)
			{
				DrawFormatString(50, 50, GetColor(255, 255, 255), "�q�b�g�[");
			}
			if (boss.HitAttack)
			{
				DrawFormatString(50, 50, GetColor(0, 0, 255), "�q�b�g�[");
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
			//�^�C�g����ʂ�\��
			SetFontSize(50);
			DrawString(ScreenWidth / 2 - 50 / 2 * 12 / 2, ScreenHeight / 3, "GAME OVER", GetColor(255, 0, 0));
			
			break;

		case GameMode::CREAR:
			//�^�C�g����ʂ�\��
			SetFontSize(50);
			DrawString(ScreenWidth / 2 - 50 / 2 * 12 / 2, ScreenHeight / 3, "GAME CREAR", GetColor(0, 255, 0));
			break;
		default:
			break;
		}
		

		prevCount = nowCount;
		
		ScreenFlip();

		Wait();		//Fps�ҋ@
	}

	DxLib_End;
	return 0;

}
