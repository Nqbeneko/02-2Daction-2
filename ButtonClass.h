#pragma once

enum Button
{
	Start,
	Tutorial,
	Quit,
	Retry,
};

class BUTTON
{
public:
	int Start_Button;
	int TUTORIAL_Button;
	int QUIT_Button;
	int RETRY_Button;

	void Init();
};