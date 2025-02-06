#pragma once

enum SEnumber
{
	Attack1se,
	Attack2se,
	Dashse,
	Runse,
	Diese
};

enum BossSEnum
{
	AppearSE,
	DethSE,
	AttackScytheSE,
	RushSE,
	SummonSE,
	SoulSE
};

class SE
{
private:
	//�V�X�e����
	int enter_handle;

	//�v���C���[
	int Attack1_handle;
	int Attack2_handle;
	int Dash_handle;
	int Run_handle;
	int Die_handle;

	//�{�X
	int Appear_handle;
	int Deth_handle;
	int AttackScythe_handle;
	int Rush_handle;
	int Summon_handle;
	int Soul_handle;


public:
	void Init();

	void Play(SEnumber num);

	void PlayBoss(BossSEnum num);

	void PlaySystem();

	void Stop(SEnumber num);

	void StopBoss(BossSEnum num);

	void StopSystem();

	void AllStopPlayer();

	void AllStopBoss();

	void SetAllLargeVolume();

	void SetAllLowVolume();

	void Delete();

};