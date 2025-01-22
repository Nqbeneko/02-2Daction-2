#include"DxLib.h"
#include"screen.h"
#include"player.h"
#include"Boss.h"
#include"collision.h"
#include"Efect.h"

void InitBossEfect(Efect& efect)
{
    efect.animNowIndex = 0;
    efect.animNowPattern = 0;
    efect.animNowType = 0;
    efect.animPastType = 0;
    efect.animPattern = 7;
    efect.animTimer = 0;
    LoadDivGraph("img/efect/whiteEfect.png", 7, 7, 1, 64, 64, efect.Graph[0]);
}

void BossRushPreliminaryAction(Efect& efect, Boss& boss)
{
    efect.animTimer += 1.0f/60.0f;
    if (efect.animTimer > 0.083f)
    {

        efect.animTimer = 0.0f;
        efect.animNowPattern++;
        if (efect.animNowPattern == efect.animPattern)
        {
            efect.animNowPattern = 0;
        }
    }
    efect.animNowIndex = efect.animNowPattern;

    
}

void DrawBossEfect(Efect& efect, Boss& boss)
{
    if (boss.Rush_PreliminaryActionTimer > 0)
    {
        DrawRotaGraph3(boss.pos.x + 7.0f, boss.pos.y - 38.0f, 64 / 2, 64 / 2, 1, 1, 0, efect.Graph[0][efect.animNowIndex], TRUE, FALSE);
    }
}