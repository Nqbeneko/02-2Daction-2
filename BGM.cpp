#include "DxLib.h"
#include "BGM.h"

void BGM::Init()
{

	Title_handle = LoadSoundMem("img/BGM/TITLE.wav");
	Game_handle = LoadSoundMem("img/BGM/Game.mp3");
	Over_handle = LoadSoundMem("img/BGM/OVER.mp3");
	Clear_handle = LoadSoundMem("img/BGM/CLEAR.wav");

	ChangeVolumeSoundMem(250, Title_handle);
	ChangeVolumeSoundMem(150, Game_handle);
	ChangeVolumeSoundMem(200, Over_handle);
	ChangeVolumeSoundMem(200, Clear_handle);

}

void BGM::Play(BGMType bgm)
{
	switch (bgm)
	{
	case Title:

		if (CheckSoundMem(Title_handle) == 0)
		{
			PlaySoundMem(Title_handle, DX_PLAYTYPE_LOOP);
		}
		break;
	case Game:
		if (CheckSoundMem(Game_handle) == 0)
		{
			PlaySoundMem(Game_handle, DX_PLAYTYPE_LOOP);
		}
		break;
	case Over:
		if (CheckSoundMem(Over_handle) == 0)
		{
			PlaySoundMem(Over_handle, DX_PLAYTYPE_LOOP);
		}
		break;
	case Clear:
		if (CheckSoundMem(Clear_handle) == 0)
		{
			PlaySoundMem(Clear_handle, DX_PLAYTYPE_LOOP);
		}
		break;
	default:
		break;
	}
	

}

void BGM::Stop()
{
	StopSoundMem(Title_handle);
	StopSoundMem(Game_handle);
	StopSoundMem(Over_handle);
	StopSoundMem(Clear_handle);

}