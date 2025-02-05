#include"DxLib.h"
#include"screen.h"
#include"player.h"
#include"map.h"
#include"Boss.h"
#include"collision.h"
#include"Debug.h"
#include"Effect.h"
#include"GameOver.h"
#include"GameTime.h"

void GameOver::Init()
{
    Graph = LoadGraph("img/font/GAME OVER.png");
    Scale = 0.0f;
    timer = 0.6f;
    StopTimer = 0.0f;

    QuakeTime = 0.0f;
    addPosX = 0.0f;
    addPosY = 0.0f;
    addFlag = false;

    AnimEnd = false;
    OverFlag = false;
}

void GameOver::Progress(Player& player,Timer* time, int fontHandle1, int fontHandle3)
{
    if (!OverFlag)
    {
        player.animNowType = Die_Animation;
        player.animNowPattern = 0;
        player.animPattern = DIE;
        player.animTimer = 0;
        OverFlag = true;
    }

    if (!AnimEnd && OverFlag)
    {
        DrawPlayer(player);
        StopTimer += 1.0f;
        if (StopTimer > 20.0f)
        {
            AnimationPlayer(player);
        }
        
    }
    
    if (AnimEnd && OverFlag)
    {
        Draw(time,fontHandle1,fontHandle3);
    }

}


void GameOver::Draw(Timer* time,int fontHandle1, int fontHandle3)
{
    if(Scale < 3.0f)
    {
        
        timer += 1.0f / 60.0f;
        if (timer > 0.5f)
        {
            Scale += 0.03f;
        }
    }
    
    DrawRotaGraph3(ScreenWidth / 2, ScreenHeight / 3, 201 / 2, 27 / 2, Scale, Scale, 0, Graph, TRUE, FALSE);
    SetFontSize(30);

    if (Scale >= 3.0f)
    {
        QuakeTime += 1.0f;
        if (QuakeTime > 10.0f)
        {
            QuakeTime = 0.0f;
            if (!addFlag)
            {
                addPosX = 0.5f;
                addPosY = 0.5f;
                addFlag = true;
            }
            else
            {
                addPosX = -0.5f;
                addPosY = -0.5f;
                addFlag = false;

            }
        }
        
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
        DrawBox(0, 230, 800, 400, GetColor(0,0,0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        time->DrawOverTime(fontHandle1);
        DrawFormatStringToHandle((ScreenWidth / 2 - 130) + addPosX, (ScreenHeight * 2 / 3) + addPosY, GetColor(236, 236, 236), fontHandle3, "Press BACK to TITLE.");

        //DrawString((ScreenWidth / 2 - 30 / 2 * 21 / 2) + addPosX, (ScreenHeight * 2 / 3) + addPosY, "Press BACK to TITLE.", GetColor(238, 238, 238));
    }
    
}


void GameOver::DrawPlayer(Player& player)
{
    DrawBox(0, 0, ScreenWidth, ScreenHeight, GetColor(50, 50, 50), TRUE);

    //キャラクターの描画
    if (!player.Graph_LR)
    {
        DrawGraph(static_cast<int>(player.pos.x - player.w), static_cast<int>(player.pos.y - player.w), player.PlayerAnimation[player.animNowIndex], TRUE);
    }
    if (player.Graph_LR)
    {
        DrawTurnGraph(static_cast<int>(player.pos.x - player.w), static_cast<int>(player.pos.y - player.h), player.PlayerAnimation[player.animNowIndex], TRUE);
    }
}

void GameOver::AnimationPlayer(Player& player)
{
    player.animTimer += 1.0f/60.0f;
    if (player.animTimer > 1.0f / 60.0f * 5)
    {
        player.animTimer = 0.0f;
        player.animNowPattern++;

        if (player.animNowPattern > player.animPattern - 1)
        {
            AnimEnd = true;
        }
    }

    // 添え字 = 一つのパターンのコマ数 + アニメーション種類 * １つのアニメーションのパターン枚数
    player.animNowIndex = player.animNowPattern + player.animNowType * PlayerImg_Xnum;
}