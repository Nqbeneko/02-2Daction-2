#include"DxLib.h"
#include"Help.h"

void Help::Init()
{
	Graph[0] = LoadGraph("img/button/A.png");
	Graph[1] = LoadGraph("img/button/X.png");
	Graph[2] = LoadGraph("img/button/RB.png");
	Graph[3] = LoadGraph("img/button/L_Stick.png");

}



void Help::DrawHelp(int fontHandle)
{
	DrawRotaGraph3(45, 15, 128 / 2, 128 / 2, 0.2, 0.2, 0, Graph[0], TRUE, FALSE);
	DrawRotaGraph3(45, 40, 128 / 2, 128 / 2, 0.2, 0.2, 0, Graph[1], TRUE, FALSE);
	DrawRotaGraph3(45, 65, 128 / 2, 128 / 2, 0.2, 0.2, 0, Graph[2], TRUE, FALSE);
	DrawRotaGraph3(45, 90, 128 / 2, 128 / 2, 0.2, 0.2, 0, Graph[3], TRUE, FALSE);

	DrawFormatStringToHandle(60, 0, GetColor(185, 194, 196), fontHandle, "ÉWÉÉÉìÉv");
	DrawFormatStringToHandle(60, 27, GetColor(185, 194, 196), fontHandle, "çUåÇ");
	DrawFormatStringToHandle(60, 50, GetColor(185, 194, 196), fontHandle, "âÒî");
	DrawFormatStringToHandle(60, 77, GetColor(185, 194, 196), fontHandle, "à⁄ìÆ");




}