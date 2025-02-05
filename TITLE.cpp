#include"DxLib.h"
#include"screen.h"
#include"TITLE.h"

void TITLE::Init()
{
    Graph = LoadGraph("img/font/TITLE2.png");
}


void TITLE::Progress()
{
    Draw();
}

void TITLE::Draw()
{
    DrawRotaGraph3(ScreenWidth / 2, ScreenHeight / 2 - 80, 200 / 2, 64 / 2, 3, 3, 0, Graph, TRUE, FALSE);
    //DrawRotaGraph3(ScreenWidth / 2, ScreenHeight / 2 + 150, 600 / 2, 145 / 2, 0.3, 0.3, 0, ButtonGraph[0], TRUE, FALSE);
}