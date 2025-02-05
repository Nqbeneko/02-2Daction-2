#pragma once

enum SEnumber
{
	Attack1se,
	Attack2se,
	Dashse,
	Runse
};

class SE
{
private:
	int Attack1_handle;
	int Attack2_handle;
	int Dash_handle;
	int Run_handle;

public:
	void Init();

	void Play(SEnumber num);

	void Stop(SEnumber num);
};