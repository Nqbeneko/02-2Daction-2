#include "DxLib.h"
#include "SE.h"

void SE::Init()
{
	//システム音
	enter_handle = LoadSoundMem("img/SE/enter12.mp3");
	ChangeVolumeSoundMem(250, enter_handle);

	//　プレイヤー
	Attack1_handle = LoadSoundMem("img/SE/Attack1.mp3");
	Attack2_handle = LoadSoundMem("img/SE/Attack2.mp3");
	Dash_handle = LoadSoundMem("img/SE/Dash.mp3");
	Run_handle = LoadSoundMem("img/SE/Run.mp3");
	Die_handle = LoadSoundMem("img/SE/damaged5.mp3");

	

	//　ボス
	Appear_handle = LoadSoundMem("img/SE/boss_Appear.mp3");
	Deth_handle = LoadSoundMem("img/SE/crash.mp3");
	AttackScythe_handle = LoadSoundMem("img/SE/boss_attackScythe.mp3");
	Rush_handle = LoadSoundMem("img/SE/boss_Rush.mp3");
	Summon_handle = LoadSoundMem("img/SE/boss_Summon.mp3");
	Soul_handle = LoadSoundMem("img/SE/soul_flame2.mp3");



}

void SE::PlaySystem()
{
	PlaySoundMem(enter_handle, DX_PLAYTYPE_BACK);
	

}

void SE::Play(SEnumber num)
{
	switch (num)
	{
	case Attack1se:
		if (CheckSoundMem(Attack1_handle) == 0)
		{
			PlaySoundMem(Attack1_handle, DX_PLAYTYPE_BACK);
		}
		break;
	case Attack2se:
		if (CheckSoundMem(Attack2_handle) == 0)
		{
			PlaySoundMem(Attack2_handle, DX_PLAYTYPE_BACK);
		}
		break;

	case Dashse:
		if (CheckSoundMem(Dash_handle) == 0)
		{
			PlaySoundMem(Dash_handle, DX_PLAYTYPE_BACK);
		}
		break;

	case Runse:
		if (CheckSoundMem(Run_handle) == 0)
		{
			PlaySoundMem(Run_handle, DX_PLAYTYPE_BACK);
		}
		break;
	case Diese:
		if (CheckSoundMem(Die_handle) == 0)
		{
			PlaySoundMem(Die_handle, DX_PLAYTYPE_BACK);
		}
		break;
	default:
		break;
	}


}

void SE::PlayBoss(BossSEnum num)
{
	switch (num)
	{
	case AppearSE:
		if (CheckSoundMem(Appear_handle) == 0)
		{
			PlaySoundMem(Appear_handle, DX_PLAYTYPE_BACK);
		}
		break;
	case DethSE:
		if (CheckSoundMem(Deth_handle) == 0)
		{
			PlaySoundMem(Deth_handle, DX_PLAYTYPE_BACK);
		}
		break;
	case AttackScytheSE:
		if (CheckSoundMem(AttackScythe_handle) == 0)
		{
			PlaySoundMem(AttackScythe_handle, DX_PLAYTYPE_BACK);
		}
		break;
	case RushSE:
		if (CheckSoundMem(Rush_handle) == 0)
		{
			PlaySoundMem(Rush_handle, DX_PLAYTYPE_BACK);
		}
		break;
	case SummonSE:
		if (CheckSoundMem(Summon_handle) == 0)
		{
			PlaySoundMem(Summon_handle, DX_PLAYTYPE_BACK);
		}
		break;
	case SoulSE:
		if (CheckSoundMem(Soul_handle) == 0)
		{
			PlaySoundMem(Soul_handle, DX_PLAYTYPE_BACK);
		}
		break;
	default:
		break;
	}
}

void SE::StopSystem()
{
	StopSoundMem(enter_handle);

}


void SE::Stop(SEnumber num)
{
	switch (num)
	{
	case Attack1se:
		StopSoundMem(Attack1_handle);
		break;
	case Attack2se:
		StopSoundMem(Attack2_handle);
		break;
	case Dashse:
		StopSoundMem(Dash_handle);
		break;
	case Runse:
		StopSoundMem(Run_handle);
		break;
	case Diese:
		StopSoundMem(Die_handle);
		break;
	default:
		break;
	}
}

void SE::StopBoss(BossSEnum num)
{
	switch (num)
	{
	case AppearSE:
		StopSoundMem(Appear_handle);

		break;
	case DethSE:
		StopSoundMem(Deth_handle);

		break;
	case AttackScytheSE:
		StopSoundMem(AttackScythe_handle);

		break;
	case RushSE:
		StopSoundMem(Rush_handle);

		break;
	case SummonSE:
		StopSoundMem(Summon_handle);

		break;
	case SoulSE:
		StopSoundMem(Soul_handle);

		break;

	default:
		break;
	}
}


void SE::AllStopPlayer()
{
	//プレイヤー
	StopSoundMem(Attack1_handle);
	StopSoundMem(Attack2_handle);
	StopSoundMem(Dash_handle);
	StopSoundMem(Run_handle);
	StopSoundMem(Die_handle);

	
}

void SE::AllStopBoss()
{
	//ボス
	StopSoundMem(Appear_handle);
	StopSoundMem(Deth_handle);
	StopSoundMem(Attack1_handle);
	StopSoundMem(AttackScythe_handle);
	StopSoundMem(Rush_handle);
	StopSoundMem(Summon_handle);
	StopSoundMem(Soul_handle);
}

void SE::SetAllLargeVolume()
{
	//プレイヤー
	ChangeVolumeSoundMem(255, Attack1_handle);
	ChangeVolumeSoundMem(255, Attack2_handle);
	ChangeVolumeSoundMem(250, Dash_handle);
	ChangeVolumeSoundMem(230, Run_handle);
	ChangeVolumeSoundMem(230, Die_handle);

	//ボス
	ChangeVolumeSoundMem(250, Appear_handle);
	ChangeVolumeSoundMem(200, Deth_handle);
	ChangeVolumeSoundMem(250, AttackScythe_handle);
	ChangeVolumeSoundMem(250, Rush_handle);
	ChangeVolumeSoundMem(250, Summon_handle);
	ChangeVolumeSoundMem(250, Soul_handle);
}

void SE::SetAllLowVolume()
{
	ChangeVolumeSoundMem(100, Attack1_handle);
	ChangeVolumeSoundMem(100, Attack2_handle);
	ChangeVolumeSoundMem(100, Dash_handle);
	ChangeVolumeSoundMem(100, Run_handle);

	ChangeVolumeSoundMem(100, Appear_handle);

	ChangeVolumeSoundMem(100, AttackScythe_handle);
	ChangeVolumeSoundMem(100, Rush_handle);
	ChangeVolumeSoundMem(100, Summon_handle);
	ChangeVolumeSoundMem(100, Soul_handle);

	ChangeVolumeSoundMem(250, enter_handle);
}


void SE::Delete()
{
	DeleteSoundMem(enter_handle);
	
	DeleteSoundMem(Attack1_handle);
	DeleteSoundMem(Attack2_handle);
	DeleteSoundMem(Dash_handle);
	DeleteSoundMem(Run_handle);

	DeleteSoundMem(Appear_handle);
	DeleteSoundMem(Deth_handle);
	DeleteSoundMem(AttackScythe_handle);
	DeleteSoundMem(Rush_handle);
	DeleteSoundMem(Summon_handle);
	DeleteSoundMem(Soul_handle);
}