#include"DxLib.h"
#include"screen.h"
#include"player.h"
#include"map.h"
#include"Boss.h"
#include"collision.h"
#include"Debug.h"

//-------------------------------
//デバック用
//-------------------------------
//ボス行動制御


void ControlBoss(Boss& boss)
{
    if (CheckHitKey(KEY_INPUT_1))
    {
        boss.state = BossState::Idele;
    }
    if (CheckHitKey(KEY_INPUT_2))
    {
        boss.state = BossState::AttackScythe;
    }
    if (CheckHitKey(KEY_INPUT_3))
    {
        boss.state = BossState::Rush;
    }
    if (CheckHitKey(KEY_INPUT_4))
    {

        boss.state = BossState::SummonSoul;
    }
    if (CheckHitKey(KEY_INPUT_5))
    {
        boss.state = BossState::Dead;
    }

    DrawFormatString(50, 50, GetColor(255, 0, 0), "%d", boss.RushCount);

}

void DrawBossPosition(Boss& boss)
{
    //中央
    DrawCircle(PositionMid_X, PositionMid_Y, 10, GetColor(0, 255, 0), FALSE);
    //中央上
    DrawCircle(PositionMidUp_X, PositionMidUp_Y, 10, GetColor(0, 255, 0), FALSE);
    //中央下
    DrawCircle(PositionMidDown_X, PositionMidDown_Y, 10, GetColor(0, 255, 0), FALSE);
    //中央左
    DrawCircle(PositionMidLeft_X, PositionMidLeft_Y, 10, GetColor(0, 255, 0), FALSE);
    //中央右
    DrawCircle(PositionMidRight_X, PositionMidRight_Y, 10, GetColor(0, 255, 0), FALSE);
    //左上
    DrawCircle(PositionUpLeft_X, PositionUpLeft_Y, 10, GetColor(0, 255, 0), FALSE);
    //右上
    DrawCircle(PositionUpRight_X, PositionUpRight_Y, 10, GetColor(0, 255, 0), FALSE);
    //左下
    DrawCircle(PositionDownLeft_X, PositionDownLeft_Y, 10, GetColor(0, 255, 0), FALSE);
    //右下
    DrawCircle(PositionDownRight_X, PositionDownRight_Y, 10, GetColor(0, 255, 0), FALSE);

    SetFontSize(10);
    DrawFormatString(300, 200, GetColor(255, 255, 255), "%d", boss.nextPos.LRM);
    DrawFormatString(310, 200, GetColor(255, 255, 255), "%d", boss.nextPos.Elevation);
    
    DrawFormatString(320, 200, GetColor(255, 255, 255), "%d", boss.nextPos.LRM);

    float size = VSize(boss.EnemyToTarget);
    DrawFormatString(330, 200, GetColor(255, 255, 255), "%f", size);

}

bool Flag = false;
bool Push =false;
int num = 0;

void SelectDrawManageUI(Player& player ,Boss& boss,Soul soul[])
{
    if (CheckHitKey(KEY_INPUT_I) && !Push)
    {
        Push = true;
        num += 1;
        if (num > 1)
        {
            Flag = false;
            num = 0;
        }
        else
        {
            Flag = true;
        }
    }
    else if(!CheckHitKey(KEY_INPUT_I))
    {
        Push = false;
    }


    if (Flag)
    {
        //プレイヤー攻撃の当たり判定
        DrawBox(player.pos.x - 32.0f, player.pos.y - 16.0f, player.pos.x + 32.0f, player.pos.y + 16.0f, GetColor(255, 125, 0), FALSE);
        //プレイヤーの当たり判定
        DrawBox(static_cast<int>(player.pos.x - PlayerCollisionX), static_cast<int>(player.pos.y - PlayerCollisionY), static_cast<int>(player.pos.x + PlayerCollisionX), static_cast<int>(player.pos.y + PlayerCollisionY), GetColor(0, 255, 0), FALSE);

        //ボスの攻撃変更のやつ
        DrawFormatString(60, 50, GetColor(255, 255, 255), "%d", boss.state);
        DrawFormatString(70, 50, GetColor(255, 255, 255), "%d", boss.SwitchingTime);

        //ボス通常攻撃の検知範囲
        DrawBox(static_cast<int>(boss.pos.x - 125.0f), static_cast<int>(boss.pos.y - 50.0f),
            static_cast<int>(boss.pos.x + 125.0f), static_cast<int>(boss.pos.y + 50.0f), GetColor(255, 0, 0), FALSE);
        //ボスの当たり判定
        DrawBox(static_cast<int>(boss.pos.x - 25.0f), static_cast<int>(boss.pos.y - 35.0f),
            static_cast<int>(boss.pos.x + 25.0f), static_cast<int>(boss.pos.y + 35.0f), GetColor(0, 255, 0), FALSE);

        DrawBossPosition(boss);

        //魂当たり判定
        for (int i = 0; i < MaxSoulNum; i++)
        {
            if (soul[i].PresenceFlag)
            {
                DrawBox(soul[i].pos.x - soulCollminusW, soul[i].pos.y - soulCollminusH, soul[i].pos.x + soulCollplusW, soul[i].pos.y + soulCollplusH, GetColor(255, 0, 0), FALSE);
            }
        }
    }
    
}
