#include<cmath>
#include"DxLib.h"
#include"player.h"
#include"Boss.h"
#include"screen.h"

const int BossHP = 50;
const float ANGLE = 45.0f;
const float BossSpeed = 2.0f;

const int BossHpPositionX = ScreenWidth / 2 - ((BossHP * 6) / 2);
const int BossHpPositionY = 430;

const int BossHpLength = BossHP * 6 + 1;

bool OneHit1 = false;
bool OneHit2 = false;

void InitBoss(Boss& boss)
{
    LoadDivGraph("img/idle2.png", IdleAnimBoss, IdleAnimBossX, IdleAnimBossY, 100, 100, boss.BossGraph[0]);
    LoadDivGraph("img/attacking.png", AttackAnimBoss, AttackAnimBossX, AttackAnimBossY, 100, 100, boss.BossGraph[1]);
    LoadDivGraph("img/skill1.png", SkillAnimBoss, SkillAnimBossX, SkillAnimBossY, 100, 100, boss.BossGraph[2]);
    LoadDivGraph("img/summon.png", SummonAnimBoss, SummonAnimBossX, SummonAnimBossY, 100, 100, boss.BossGraph[3]);

    boss.w = BossChipSize;
    boss.h = BossChipSize;
	boss.pos = VGet(668 + boss.w * 0.5f, 220 + boss.h * 0.5f, 0);
	boss.direction = VGet(0, 0, 0);
    boss.center = VGet(ScreenWidth / 2, 0, 0);

    boss.HP = BossHP;

    boss.Angle = ANGLE;
    boss.radius = 0;
    boss.MoveArcFlag = false;

    boss.AttackFlag = false;
    boss.RigorTime = 0;


    boss.RightMove = false;
    boss.moveSpeed = BossSpeed;
    boss.animTimer = 0;
    boss.animNowType = Idle;
    boss.animNowIndex = 0;
    boss.animNowPattern = 0;
    boss.animPattern = IdleAnimBoss;
    boss.animPastType = Idle;

   
}

void UpdateBoss(Boss& boss, Soul& soul, Player& player)
{
    VECTOR direction = VGet(0, 0, 0);
    //MoveArc(boss);
    MoveAttack(boss, player);

    if (player.pos.x > boss.pos.x && boss.RigorTime <= 0)
    {
        boss.RightMove = false;
    }
    else if (player.pos.x < boss.pos.x && boss.RigorTime <= 0)
    {
        boss.RightMove = true;
    }

    //------------------------------------
    // ボスHP管理
    //-----------------------------------
    
    if (player.AttackFlag && player.HitAttack && !OneHit1)
    {
        boss.HP -= 1;
        OneHit1 = true;
    }
    if (!player.AttackFlag)
    {
        OneHit1 = false;
    }

    if (player.AttackFlag_2 && player.HitAttack && !OneHit2)
    {
        boss.HP -= 1;
        OneHit2 = true;
    }
    if (!player.AttackFlag_2)
    {
        OneHit2 = false;
    }
    if (boss.HP <= 0)
    {
        boss.HP = 0;
    }
}

void UpdateAnimationBoss(Boss& boss, Soul& soul, float deltaTime)
{

    //-------------------------------------------------------------------
    //アニメーションが変更されたらそのアニメーションの最初から描画
    //-------------------------------------------------------------------
    if (boss.animPastType != boss.animNowType)
    {
        boss.animPastType = boss.animNowType;
        boss.animNowPattern = 0;
    }


    //ボスアニメーション
    boss.animTimer += deltaTime;
    if (boss.animTimer > 1.0f / boss.animPattern)
    {

        boss.animTimer = 0.0f;
        boss.animNowPattern++;
        if (boss.animNowPattern == boss.animPattern)
        {
            boss.animNowPattern = 0;
        }
    }
    //周りの魂アニメーション
    soul.animTimer += deltaTime;
    if (soul.animTimer > 1.0f / soul.animPattern)
    {

        soul.animTimer = 0.0f;
        soul.animNowPattern++;
        if (soul.animNowPattern == soul.animPattern)
        {
            soul.animNowPattern = 0;
        }
    }

    boss.animNowIndex = boss.animNowPattern;
}

void DrawBoss(Boss& boss, Soul& soul,Player&player)
{
  
    if (boss.RightMove)
    {
        DrawRotaGraph3(static_cast<int>(boss.pos.x), static_cast<int>(boss.pos.y), boss.w / 2, boss.h / 2, 2, 2, 0, boss.BossGraph[boss.animNowType][boss.animNowPattern], TRUE, TRUE);
    }
    if (!boss.RightMove)
    {
        DrawRotaGraph3(static_cast<int>(boss.pos.x), static_cast<int>(boss.pos.y), boss.w / 2, boss.h / 2, 2, 2, 0, boss.BossGraph[boss.animNowType][boss.animNowPattern], TRUE, FALSE);
    }

    DrawBox(static_cast<int>(boss.pos.x - 100.0f), static_cast<int>(boss.pos.y - 50.0f), static_cast<int>(boss.pos.x + 100.0f), static_cast<int>(boss.pos.y + 50.0f), GetColor(255, 0, 0), FALSE);
    
    //DrawBox(static_cast<int>(boss.pos.x - 80.0f), static_cast<int>(boss.pos.y - 50.0f), static_cast<int>(boss.pos.x + 80.0f), static_cast<int>(boss.pos.y + 50.0f), GetColor(255, 125, 0), FALSE);
    DrawBox(static_cast<int>(boss.pos.x - 25.0f), static_cast<int>(boss.pos.y - 35.0f), static_cast<int>(boss.pos.x + 25.0f), static_cast<int>(boss.pos.y + 35.0f), GetColor(0, 255, 0), FALSE);

    //DrawCircle(boss.center.x, boss.center.y, 10, GetColor(255, 0, 0), TRUE);
    //DrawLine(boss.center.x, boss.center.y, boss.pos.x, boss.pos.y, GetColor(255, 255, 255), TRUE);
  

}

void DrawBossUI(Boss& boss)
{
    //ボスHPの表示
    DrawBox(BossHpPositionX - 1, BossHpPositionY - 1, BossHpPositionX + BossHpLength,BossHpPositionY + 11, GetColor(0, 0, 0), TRUE);
    DrawBox(BossHpPositionX, BossHpPositionY, BossHpPositionX + (boss.HP * 6), BossHpPositionY + 10, GetColor(255, 0, 0), TRUE);
    //名前の表示
    SetFontSize(20);
    DrawFormatString(BossHpPositionX + BossHpLength / 2 - 20, BossHpPositionY - 20, GetColor(255, 255, 255), "BOSS");

}

void MoveArc(Boss& boss)
{
    //--------------------
    // 弧を描く移動
    //--------------------
   /* VECTOR direction = VGet(0, 0, 0);

    VECTOR vec = VGet(0, 1, 0);

    if (boss.Angle <= 45)
    {
        boss.MoveArcFlag = true;
    }
    if (boss.Angle >= 135)
    {
        boss.MoveArcFlag = false;
    }

    boss.radius = boss.Angle * DX_PI_F / 180.0f;
    MATRIX rotZ = MGetRotZ(boss.radius);
    direction = VTransform(vec, rotZ);

    if (VSize(direction) != 0)
    {
        direction = VNorm(direction);
    }

    VECTOR velocity = VScale(direction, boss.moveSpeed);

    boss.pos = VAdd(boss.pos, velocity);
   
    if (boss.MoveArcFlag)
    {
        boss.Angle += 0.4f;
    }
    if (!boss.MoveArcFlag)
    {
        boss.Angle -= 0.4f;
    }*/
    boss.radius = boss.Angle * DX_PI_F / 180.0f;

    boss.pos.x = boss.center.x + cos(boss.radius) * 450;
    boss.pos.y = boss.center.y + sin(boss.radius) * 300;

    if (boss.Angle > 135)
    {
        boss.MoveArcFlag = true;
    }
    else if (boss.Angle < 45)
    {
        boss.MoveArcFlag = false;
    }

    if (boss.MoveArcFlag)
    {
        boss.Angle -= 0.5f;
    }
    if (!boss.MoveArcFlag)
    {
        boss.Angle += 0.5f;
    }
}

void MoveAttack(Boss& boss, Player& player)
{
    VECTOR EnemyToPlayer = VSub(player.pos, boss.pos);

    if (boss.RigorTime <= 0)
    {
        boss.direction = VNorm(EnemyToPlayer);

        VECTOR velocity = VScale(boss.direction, boss.moveSpeed);

        boss.pos = VAdd(boss.pos, velocity);
    }
    

    //一定範囲内にプレイヤーが入ったら攻撃をする
    if (boss.RigorTime <= 0 && (player.pos.x - boss.pos.x) < 100 && (player.pos.x - boss.pos.x) > -100 && (player.pos.y - boss.pos.y) < 50 && (player.pos.y - boss.pos.y) > -50)
    {
        boss.AttackFlag = true;
        boss.RigorTime = 200;
    }

    //アニメーションの変更
    if (boss.AttackFlag)
    {
        boss.animNowType = Attack;
        boss.animPattern = AttackAnimBoss;
    }

    if (boss.AttackFlag && boss.animNowPattern == boss.animPattern - 1)
    {
        boss.animNowType = Idle;
        boss.animPattern = IdleAnimBoss;
        boss.AttackFlag = false;
    }

    //硬直時間を減らす
    if (boss.RigorTime > 0)
    {
        boss.RigorTime -= 1;
    }
}

void MoveSkill(Boss& boss, Player& player)
{
    VECTOR EnemyToPlayer = VSub(player.pos, boss.pos);

}

void ControlHP(Boss& boss)
{

}