#include"DxLib.h"
#include"screen.h"
#include"TITLE.h"

void TITLE::Init()
{
    Graph = LoadGraph("img/font/TITLE2.png");
    MoveGraph = LoadGraph("img/gameVideo.mov");
    timer = 0.0f;
}


void TITLE::Progress()
{
    Draw();
    PlayMove();
}

void TITLE::Draw()
{
    DrawRotaGraph3(ScreenWidth / 2, ScreenHeight / 2 - 80, 200 / 2, 64 / 2, 3, 3, 0, Graph, TRUE, FALSE);
    //DrawRotaGraph3(ScreenWidth / 2, ScreenHeight / 2 + 150, 600 / 2, 145 / 2, 0.3, 0.3, 0, ButtonGraph[0], TRUE, FALSE);
}

void TITLE::PlayMove()
{
    if (!GetMovieStateToGraph(MoveGraph))
    {
        //“®‰æ‚ÌÄ¶ˆÊ’u‚ğ‚O‚É–ß‚·
        SeekMovieToGraph(MoveGraph, 0);
        timer += 1.0f;
    }
    
    if (timer >= 300.0f || GetMovieStateToGraph(MoveGraph))
    {
        //“®‰æ‚ğÄ¶‚·‚é
        PlayMovieToGraph(MoveGraph);
        DrawExtendGraph(0, 0,800,480, MoveGraph, FALSE);
        timer = 0.0f;
    }
   
}

void TITLE::Delete()
{
    DeleteGraph(Graph);
    DeleteGraph(MoveGraph);

}