#pragma once

enum BGMType
{
	Title,
	Game,
	Over,
	Clear
};

class BGM
{
private:
	int Title_handle;
	int Game_handle;
	int Over_handle;
	int Clear_handle;

public:

	void Init();

	void Play(BGMType bgm);

	void Stop();

};



