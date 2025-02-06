#include"DxLib.h"
#include "screen.h"
#include "player.h"
#include "Boss.h"
#include "collision.h"

//プレイヤーの攻撃当たり判定初期化
void InitPlayerAttackCollision(Collision& playerCol_L, Collision& playerCol_R)
{
    playerCol_L.PosLeft = 0;
    playerCol_L.PosRight = 0;
    playerCol_L.PosTop = 0;
    playerCol_L.PosBottom = 0;

    playerCol_R.PosLeft = 0;
    playerCol_R.PosRight = 0;
    playerCol_R.PosTop = 0;
    playerCol_R.PosBottom = 0;

}
//初期化
void InitBossAttackCollision(Collision& boss1_L, Collision& boss1_R, Collision& boss2)
{
    boss1_L.PosLeft = 0;
    boss1_L.PosRight = 0;
    boss1_L.PosTop = 0;
    boss1_L.PosBottom = 0;

    boss1_R.PosLeft = 0;
    boss1_R.PosRight = 0;
    boss1_R.PosTop = 0;
    boss1_R.PosBottom = 0;

    boss2.PosLeft = 0;
    boss2.PosRight = 0;
    boss2.PosTop = 0;
    boss2.PosBottom = 0;
}
//プレイヤーの攻撃当たり判定更新
void UpdatePlayerAttackCollision(Collision& playerCol_L, Collision& playerCol_R, Player& player)
{
    if ((player.AttackFlag || player.AttackFlag_2) && player.Graph_LR)
    {
        playerCol_L.PosLeft     = player.pos.x - 32.0f;
        playerCol_L.PosRight    = player.pos.x;
        playerCol_L.PosTop      = player.pos.y - 16.0;
        playerCol_L.PosBottom   = player.pos.y + 16.0f;
        //DrawBox(playerCol_L.PosLeft, playerCol_L.PosTop, playerCol_L.PosRight, playerCol_L.PosBottom, GetColor(0, 0, 255), FALSE);
    }
    if ((player.AttackFlag || player.AttackFlag_2) && !player.Graph_LR)
    {
        playerCol_R.PosLeft     = player.pos.x;
        playerCol_R.PosRight    = player.pos.x + 32.0f;
        playerCol_R.PosTop      = player.pos.y - 16.0f;
        playerCol_R.PosBottom   = player.pos.y + 16.0f;
       // DrawBox(playerCol_R.PosLeft, playerCol_R.PosTop, playerCol_R.PosRight, playerCol_R.PosBottom, GetColor(0, 0, 255), FALSE);
    }
    
}

//ボスの攻撃当たり判定更新
void UpdateBossAttackCollision(Collision& boss1_L, Collision& boss1_R, Collision& boss2, Boss& boss)
{
    if (boss.RightMove && boss.AttackFlag)
    {
        boss1_L.PosLeft = boss.pos.x - 110.0f;
        boss1_L.PosRight = boss.pos.x + 60.0f;
        boss1_L.PosTop = boss.pos.y - 50.0f;
        boss1_L.PosBottom = boss.pos.y + 60.0f;
        //DrawBox(boss1_L.PosLeft, boss1_L.PosTop, boss1_L.PosRight, boss1_L.PosBottom, GetColor(0, 0, 255), FALSE);
    }
    if (!boss.RightMove && boss.AttackFlag)
    {
        boss1_R.PosLeft = boss.pos.x - 60.0f;
        boss1_R.PosRight = boss.pos.x + 110.0f;
        boss1_R.PosTop = boss.pos.y - 50.0f;
        boss1_R.PosBottom = boss.pos.y + 60.0f;
        //DrawBox(boss1_R.PosLeft, boss1_R.PosTop, boss1_R.PosRight, boss1_R.PosBottom, GetColor(0, 0, 255), FALSE);
    }

    /*if (boss.AttackFlag)
    {
        boss2.PosLeft = boss.pos.x - 60.0f;
        boss2.PosRight = boss.pos.x + 60.0f;
        boss2.PosTop = boss.pos.y - 60.0f;
        boss2.PosBottom = boss.pos.y + 60.0f;
    }*/
}

//敵とプレイヤーの当たり判定
bool UpdateHitBossRush(Boss& boss, Player& player)
{

    //ボスの当たり判定位置
    float bossPosLeft   = boss.pos.x - 50.0f;
    float bossPosRight  = boss.pos.x + 50.0f;
    float bossPosTop    = boss.pos.y - 50.0f;
    float bossPosBottom = boss.pos.y + 70.0f;
    //プレイヤーの当たり判定位置
    float playerPosLeft     = player.pos.x - 10.0f;
    float playerPosRight    = player.pos.x + 10.0f;
    float playerPosTop      = player.pos.y - 16.0f;
    float playerPosBottom   = player.pos.y + 16.0f;

    //ボスの当たり判定
    //DrawBox(static_cast<int>(bossPosLeft), static_cast<int>(bossPosTop),static_cast<int>(bossPosRight), static_cast<int>(bossPosBottom), GetColor(0, 255, 0), FALSE);

    if (((bossPosLeft < playerPosLeft && playerPosLeft < bossPosRight) ||
        (bossPosLeft > playerPosLeft && bossPosLeft < playerPosRight)) &&
        ((bossPosTop <= playerPosTop && playerPosTop < bossPosBottom) ||
            (bossPosTop > playerPosTop && bossPosTop < playerPosBottom)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//プレイヤーの攻撃と敵の当たり判定
bool UpdateHitPlayerAttack(Collision& playerCol_L, Collision& playerCol_R, Player& player, Boss& boss)
{
    float targetPosLeft     = boss.pos.x - 25.0f;
    float targetPosRight    = boss.pos.x + 25.0f;
    float targetPosTop      = boss.pos.y - 50.0f;
    float targetPosBottom   = boss.pos.y + 70.0f;
    if ((player.AttackFlag || player.AttackFlag_2) && player.Graph_LR) {
        if (((targetPosLeft <= playerCol_L.PosLeft && playerCol_L.PosLeft < targetPosRight) ||
            (targetPosLeft > playerCol_L.PosLeft && targetPosLeft < playerCol_L.PosRight)) &&
            ((targetPosTop <= playerCol_L.PosTop && playerCol_L.PosTop < targetPosBottom) ||
                (targetPosTop > playerCol_L.PosTop && targetPosTop < playerCol_L.PosBottom)))
        {
            return true;
        }
        return false;
    }

    if ((player.AttackFlag || player.AttackFlag_2) && !player.Graph_LR) {
        if (((targetPosLeft <= playerCol_R.PosLeft && playerCol_R.PosLeft < targetPosRight) ||
            (targetPosLeft > playerCol_R.PosLeft && targetPosLeft < playerCol_R.PosRight)) &&
            ((targetPosTop <= playerCol_R.PosTop && playerCol_R.PosTop < targetPosBottom) ||
                (targetPosTop > playerCol_R.PosTop && targetPosTop < playerCol_R.PosBottom)))
        {
            return true;
        }
        return false;
    }
}

bool UpdateHitBossAttack(Collision& boss1_L, Collision& boss1_R, Player& player, Boss& boss)
{
    float targetPosLeft = player.pos.x - 10.0f;
    float targetPosRight = player.pos.x + 10.0f;
    float targetPosTop = player.pos.y - 16.0f;
    float targetPosBottom = player.pos.y + 16.0f;

    if (boss.AttackFlag && !boss.RightMove)
    {
        if (((targetPosLeft <= boss1_R.PosLeft && boss1_R.PosLeft < targetPosRight) ||
            (targetPosLeft > boss1_R.PosLeft && targetPosLeft < boss1_R.PosRight)) &&
            ((targetPosTop <= boss1_R.PosTop && boss1_R.PosTop < targetPosBottom) ||
                (targetPosTop > boss1_R.PosTop && targetPosTop < boss1_R.PosBottom)))
        {
            return true;
        }
        return false;
    }

    if (boss.AttackFlag && boss.RightMove)
    {
        if (((targetPosLeft <= boss1_L.PosLeft && boss1_L.PosLeft < targetPosRight) ||
            (targetPosLeft > boss1_L.PosLeft && targetPosLeft < boss1_L.PosRight)) &&
            ((targetPosTop <= boss1_L.PosTop && boss1_L.PosTop < targetPosBottom) ||
                (targetPosTop > boss1_L.PosTop && targetPosTop < boss1_L.PosBottom)))
        {
            return true;
        }
        return false;
    }
}

bool UpdateHitBossShot(Soul soul[], Player& player)
{
    float soulPosLeft[4];
    float soulPosRight[4];
    float soulPosTop[4];
    float soulPosBottom[4];

    for (int i = 0; i < MaxSoulNum; i++)
    {
        //ボスの当たり判定位置
        soulPosLeft[i] = soul[i].pos.x - soulCollminusW;
        soulPosRight[i] = soul[i].pos.x + soulCollplusW;
        soulPosTop[i] = soul[i].pos.y - soulCollminusH;
        soulPosBottom[i] = soul[i].pos.y + soulCollplusH;
    }
    
    //プレイヤーの当たり判定位置
    float playerPosLeft = player.pos.x - 10.0f;
    float playerPosRight = player.pos.x + 10.0f;
    float playerPosTop = player.pos.y - 16.0f;
    float playerPosBottom = player.pos.y + 16.0f;

    for (int i = 0; i < MaxSoulNum; i++)
    {
        if (soul[i].PresenceFlag && !player.DashFlag)
        {
            if (((soulPosLeft[i] < playerPosLeft && playerPosLeft < soulPosRight[i]) ||
                (soulPosLeft[i] > playerPosLeft && soulPosLeft[i] < playerPosRight)) &&
                ((soulPosTop[i] <= playerPosTop && playerPosTop < soulPosBottom[i]) ||
                    (soulPosTop[i] > playerPosTop && soulPosTop[i] < playerPosBottom)))
            {
                soul[i].PresenceFlag = false;
                soul[i].ShotFlag = false;
                return true;
            }
        }
        
    }
    return false;
}