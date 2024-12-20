#include<cmath>
#include"DxLib.h"
#include"player.h"
#include"Boss.h"
#include"screen.h"

const int BossHP = 30;
const float ANGLE = 45.0f;
const float BossSpeed = 2.0f;

const int BossHpPositionX = ScreenWidth / 2 - ((BossHP * 6) / 2);
const int BossHpPositionY = 430;

const int BossHpLength = BossHP * 6 + 1;

bool OneHit1 = false;
bool OneHit2 = false;

void InitBoss(Boss& boss)
{
    LoadDivGraph("img/Boss/idle2.png", IdleAnimBoss, IdleAnimBossX, IdleAnimBossY, 100, 100, boss.BossGraph[0]);
    LoadDivGraph("img/Boss/attacking.png", AttackAnimBoss, AttackAnimBossX, AttackAnimBossY, 100, 100, boss.BossGraph[1]);
    LoadDivGraph("img/Boss/skill1.png", SkillAnimBoss, SkillAnimBossX, SkillAnimBossY, 100, 100, boss.BossGraph[2]);
    LoadDivGraph("img/Boss/summon.png", SummonAnimBoss, SummonAnimBossX, SummonAnimBossY, 100, 100, boss.BossGraph[3]);
    LoadDivGraph("img/Boss/PreliminaryAction.png", IdleAnimBoss, IdleAnimBossX, IdleAnimBossY, 100, 100, boss.BossGraph[4]);

    boss.w = BossChipSize;
    boss.h = BossChipSize;
	boss.pos = VGet(668 + boss.w * 0.5f, 220 + boss.h * 0.5f, 0);
	boss.direction = VGet(0, 0, 0);
    boss.center = VGet(ScreenWidth / 2, 0, 0);
    boss.HP = BossHP;

    boss.state = BossState::Idele;

    // 行動が始まったかどうかのフラグ
    boss.Idle_ON = false;
    boss.Attack_ON = false;
    boss.Rush_ON = false;
    boss.Summon_ON = false;

    boss.EnemyToPlayer = VGet(0, 0, 0);

    

    boss.Angle = ANGLE;
    boss.radius = 0;
    boss.MoveArcFlag = false;

    //通常攻撃関連
   
    boss.AttackFlag = false;
    boss.HitAttack = false;
    boss.RigorTime = 0;
    boss.PreliminaryActionFlag = false;
    boss.PreliminaryActionTimer = 0;

    //突進攻撃関連
    boss.PastPlayerPos = VGet(0, 0, 0);
    boss.Conflict = false;
    boss.RushTimer = 0;
    boss.RushCount = 0;


    //アニメーション関連
    boss.RightMove = false;
    boss.moveSpeed = BossSpeed;
    boss.animTimer = 0;
    boss.animNowType = Idle;
    boss.animNowIndex = 0;
    boss.animNowPattern = 0;
    boss.animPattern = IdleAnimBoss;
    boss.animPastType = Idle;

   
}

void InitBoss(Boss& boss)
{

}

void UpdateBoss(Boss& boss, Soul& soul, Player& player, float deltaTime)
{
    VECTOR direction = VGet(0, 0, 0);

    BossState PastState = boss.state;

    ControlBoss(boss);

    if (PastState != boss.state)
    {
        boss.Idle_ON = false;
        boss.Attack_ON = false;
        boss.Rush_ON = false;
        boss.Summon_ON = false;
    }

    if (player.pos.x > boss.pos.x && boss.RigorTime <= 0)
    {
        boss.RightMove = false;
    }
    else if (player.pos.x < boss.pos.x && boss.RigorTime <= 0)
    {
        boss.RightMove = true;
    }
    
    switch (boss.state)
    {
    case BossState::Idele:
        UpdateBossIdle(boss, deltaTime);
        break;

    case BossState::Attack:
        UpdateBossAttack(boss, player, deltaTime);
        break;

    case BossState::Rush:
        
        
        UpdateBossRush(boss, player, deltaTime);
        break;

    case BossState::Summon:
        UpdateBossSummon(boss, deltaTime);
        break;

    case BossState::Dead:
        break;
    default:
        break;
    }
   



    //硬直時間を減らす
    if (boss.RigorTime > 0)
    {
        boss.RigorTime -= 1;
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

void UpdateAnimationBoss(Boss& boss, float deltaTime)
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

void UpdateBossIdle(Boss& boss, float deltaTime)
{
    if (!boss.Idle_ON)
    {
        boss.animNowType = Idle;
        boss.animPattern = IdleAnimBoss;
    }

    UpdateAnimationBoss(boss, deltaTime);

    
}

void UpdateBossAttack(Boss& boss, Player& player,float deltaTime)
{
    if (!boss.Attack_ON)
    {
        boss.animNowType = Idle;
        boss.animPattern = IdleAnimBoss;
        boss.Attack_ON = true;
    }

    boss.EnemyToPlayer = VSub(player.pos, boss.pos);

    if (boss.RigorTime <= 0)
    {
        boss.direction = VNorm(boss.EnemyToPlayer);

        VECTOR velocity = VScale(boss.direction, boss.moveSpeed);

        boss.pos = VAdd(boss.pos, velocity);
    }
    
    //一定範囲内にプレイヤーが入ったら攻撃をする
    //アニメーションの変更
    if (!boss.PreliminaryActionFlag && boss.RigorTime <= 0 && (player.pos.x - boss.pos.x) < 100 && (player.pos.x - boss.pos.x) > -100 && (player.pos.y - boss.pos.y) < 50 && (player.pos.y - boss.pos.y) > -50)
    {
        /*boss.AttackFlag = true;
        boss.RigorTime = 500;*/
        boss.RigorTime = 300;

        boss.PreliminaryActionFlag = true;
        boss.PreliminaryActionTimer = 60;
        boss.animNowType = PreliminaryAction;
        boss.animPattern = PreliminaryActionAnimBoss;
    }

    boss.PreliminaryActionTimer -= 1;
    if (boss.PreliminaryActionTimer <= 0)
    {
        boss.PreliminaryActionTimer = 0;
    }

    if (boss.PreliminaryActionFlag && boss.PreliminaryActionTimer <= 0)
    {
        boss.PreliminaryActionFlag = false;
        boss.AttackFlag = true;
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

    UpdateAnimationBoss(boss, deltaTime);

}

void UpdateBossRush(Boss& boss, Player& player, float deltaTime)
{
    if (!boss.Rush_ON && boss.RigorTime <= 0)
    {
        boss.EnemyToPlayer = VSub(player.pos, boss.pos);
        boss.PastPlayerPos = player.pos;
        boss.Rush_ON = true;
        boss.RushCount += 1;

        boss.animNowType = Skill;
        boss.animPattern = SkillAnimBoss;

        if (boss.RushCount > 2)
        {
            boss.state = BossState::Idele;
            boss.RushCount = 0;
        }
    }

    if (boss.Rush_ON && boss.RigorTime <= 0)
    {
        //正規化
        if (VSize(boss.EnemyToPlayer) > 0)
        {
            boss.direction = VNorm(boss.EnemyToPlayer);
        }
        //移動
        VECTOR velocity = VScale(boss.direction, boss.moveSpeed * 3);
        boss.pos = VAdd(boss.pos, velocity);
    }
    
    /*if (boss.pos.x < GameScreenWidthL || boss.pos.y < 0 || boss.pos.x > GameScreenWidthR || )
    {
       
        boss.Conflict = true;
        boss.Rush_ON = false;
    }*/

    if (boss.pos.x < GameScreenWidthL)
    {
        boss.pos.x = GameScreenWidthL + BossChipSize * 0.5f;
        boss.Conflict = true;
        //boss.Rush_ON = false;
    }
    else if (boss.pos.x > GameScreenWidthR)
    {
        boss.pos.x = GameScreenWidthR - BossChipSize * 0.5f;
        boss.Conflict = true;
        //boss.Rush_ON = false;
    }
    else if (boss.pos.y < 0)
    {
        boss.pos.y = BossChipSize * 0.5f;
        boss.Conflict = true;
        //boss.Rush_ON = false;
    }
    else if (boss.pos.y > GameScreenHeight)
    {
        boss.pos.y = GameScreenHeight - BossChipSize * 0.5f;
        boss.Conflict = true;
        //boss.Rush_ON = false;
    }

    if (boss.Conflict)
    {
        boss.RushTimer += 1;
        if (boss.RushTimer >= 5)
        {
            boss.animNowType = Idle;
            boss.animPattern = IdleAnimBoss;
            boss.RigorTime = 100;
            boss.RushTimer = 0;
            boss.Conflict = false;
            boss.Rush_ON = false;
        }
    }

    UpdateAnimationBoss(boss, deltaTime);


}

void UpdateBossSummon(Boss& boss, float deltaTime)
{


    UpdateAnimationBoss(boss, deltaTime);

}

void ControlHP(Boss& boss)
{

}

//デバック用
void ControlBoss(Boss& boss)
{
    if (CheckHitKey(KEY_INPUT_1))
    {
        boss.state = BossState::Idele;
    }
    if (CheckHitKey(KEY_INPUT_2))
    {
        boss.state = BossState::Attack;
    }
    if (CheckHitKey(KEY_INPUT_3))
    {
        boss.state = BossState::Rush;
    }
    if (CheckHitKey(KEY_INPUT_4))
    {
        boss.state = BossState::Summon;
    }
    if (CheckHitKey(KEY_INPUT_5))
    {
        boss.state = BossState::Dead;
    }

    DrawFormatString(50, 50, GetColor(255, 0, 0), "%d", boss.RushCount);

}