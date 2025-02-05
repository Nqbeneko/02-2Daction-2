#include"DxLib.h"
#include"ButtonClass.h"

void BUTTON::Init()
{
	Start_Button = LoadGraph("img/button/START_button.png");
	TUTORIAL_Button = LoadGraph("img/button/TUTORIAL_button.png");
	QUIT_Button = LoadGraph("img/button/QUIT_button.png");
	RETRY_Button = LoadGraph("img/button/RETRY_button.png");
}