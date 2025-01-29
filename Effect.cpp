#include"DxLib.h"
#include"screen.h"
#include"player.h"
#include"Boss.h"
#include"collision.h"
#include"Effect.h"

void InitBossEffect(Effect& effect)
{
    effect.animNowIndex = 0;
    effect.animNowPattern = 0;
    effect.animNowType = RushEyeEfect;
    effect.animPastType = 0;
    effect.animPattern = 7;
    effect.animTimer = 0;
    LoadDivGraph("img/efect/boss/whiteEfect.png", 7, 7, 1, 64, 64, effect.Graph[0]);
}

void InitPlayerEffect(Effect& playeffect)
{
    playeffect.animNowIndex = 0;
    playeffect.animNowPattern = 0;
    playeffect.animNowType = DashEffect;
    playeffect.animPastType = 0;
    playeffect.animPattern = DashPatternNum;
    playeffect.animTimer = 0;
    LoadDivGraph("img/efect/player/DashEffect.png", 16, 16, 1, 64, 64, playeffect.Graph[DashEffect]);

}

void BossRushPreliminaryAction(Effect& effect, Boss& boss)
{
    effect.animTimer += 1.0f/60.0f;
    if (effect.animTimer > 0.083f)
    {

        effect.animTimer = 0.0f;
        effect.animNowPattern++;
        if (effect.animNowPattern == effect.animPattern)
        {
            effect.animNowPattern = 0;
        }
    }
    effect.animNowIndex = effect.animNowPattern;

    
}

void UpdatePlayerDashEfect(Effect& effect, Player& player)
{
    effect.animTimer += 1.0f / 60.0f;
    if (effect.animTimer > 0.016f)
    {

        effect.animTimer = 0.0f;
        effect.animNowPattern++;
        if (effect.animNowPattern == effect.animPattern - 1)
        {
            effect.animNowPattern = 0;
        }
    }
    effect.animNowIndex = effect.animNowPattern;
}

void DrawBossEfect(Effect& effect, Boss& boss)
{
    if (boss.Rush_PreliminaryActionTimer > 0)
    {
        DrawRotaGraph3(boss.pos.x + 7.0f, boss.pos.y - 38.0f, 64 / 2, 64 / 2, 1, 1, 0, effect.Graph[0][effect.animNowIndex], TRUE, FALSE);
    }
}

void DrawPlayerDashEffect(Effect& effect, Player& player)
{
    if (!player.Graph_LR)
    {
        DrawRotaGraph3(player.pos.x - player.Distans, player.pos.y, 64 / 2, 64 / 2, 1, 1, 0, effect.Graph[0][effect.animNowIndex], TRUE, FALSE);
    }
    else if(player.Graph_LR)
    {
        DrawRotaGraph3(player.pos.x + player.Distans, player.pos.y, 64 / 2, 64 / 2, 1, 1, 0, effect.Graph[0][effect.animNowIndex], TRUE, TRUE);
    }
    
}
