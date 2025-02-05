#include "DxLib.h"
#include "SE.h"

void SE::Init()
{
	Attack1_handle = LoadSoundMem("img/SE/Attack1.mp3");
	Attack2_handle = LoadSoundMem("img/SE/Attack2.mp3");
	Dash_handle = LoadSoundMem("img/SE/Dash.mp3");

	ChangeVolumeSoundMem(150, Attack1_handle);
	ChangeVolumeSoundMem(150, Attack2_handle);
	ChangeVolumeSoundMem(70, Dash_handle);

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
	default:
		break;
	}


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

	default:
		break;
	}
}
