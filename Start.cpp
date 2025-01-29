#include"DxLib.h"
#include"screen.h"
#include"player.h"
#include"map.h"
#include"Boss.h"
#include"collision.h"
#include"Debug.h"
#include"Effect.h"
#include"GameOver.h"
#include"Start.h"

void Start::Init()
{
    PlayerSet = false;
    BossSet = false;
    StartFlag = false;
}

void Start::Progress(Player& player, Boss& boss, Map& map)
{
    if (!PlayerSet)
    {
        player.animNowType = Run_Animation;
        player.animPattern = RUN;
        PlayerSet = true;
    }
    else if(PlayerSet && !BossSet)
    {
        player.pos.x += 2.0f;
        if (player.pos.x == 210.0f)
        {
            BossSet = true;
            StartFlag = true;
            map.MapChips[10][0].chipKind = 40;
        }
    }
    AnimationPlayer(player);
}


void Start::AnimationPlayer(Player& player)
{
    player.animTimer += 1.0f / 60.0f;
    if (player.animTimer > 1.0f / 60.0f * 8)
    {
        player.animTimer = 0.0f;
        player.animNowPattern++;

        if (player.animNowPattern == player.animPattern - 1)
        {
            player.animNowPattern = 0;
        }
    }

    // 添え字 = 一つのパターンのコマ数 + アニメーション種類 * １つのアニメーションのパターン枚数
    player.animNowIndex = player.animNowPattern + player.animNowType * PlayerImg_Xnum;
}
