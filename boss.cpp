#include<cmath>
#include"DxLib.h"
#include"player.h"
#include"Boss.h"
#include"screen.h"
#include"collision.h"
#include"Debug.h"


bool OneHit1 = false;
bool OneHit2 = false;

int SoulGraph[3][6];
int SoulStandbyTime;        // 画面上に出てから次が出てくるまでの時間

bool SoulPresenceAll = false;        //弾四つがすべて現れたかどうかのフラグ

void InitBoss(Boss& boss)
{
    //ボスモーション
    LoadDivGraph("img/Boss/idle2.png", IdleAnimBoss, IdleAnimBossX, IdleAnimBossY, 100, 100, boss.BossGraph[0]);
    LoadDivGraph("img/Boss/attacking.png", AttackAnimBoss, AttackAnimBossX, AttackAnimBossY, 100, 100, boss.BossGraph[1]);
    LoadDivGraph("img/Boss/skill1.png", SkillAnimBoss, SkillAnimBossX, SkillAnimBossY, 100, 100, boss.BossGraph[2]);
    LoadDivGraph("img/Boss/summon.png", SummonAnimBoss, SummonAnimBossX, SummonAnimBossY, 100, 100, boss.BossGraph[3]);
    LoadDivGraph("img/Boss/PreliminaryAction.png", IdleAnimBoss, IdleAnimBossX, IdleAnimBossY, 100, 100, boss.BossGraph[4]);
    //ダメージを受けたときのボスモーション
    LoadDivGraph("img/Boss/idle2_damageRed.png", IdleAnimBoss, IdleAnimBossX, IdleAnimBossY, 100, 100, boss.DamageGraph[0]);
    LoadDivGraph("img/Boss/attacking_damageRed.png", AttackAnimBoss, AttackAnimBossX, AttackAnimBossY, 100, 100, boss.DamageGraph[1]);
    LoadDivGraph("img/Boss/skill1_damageRed.png", SkillAnimBoss, SkillAnimBossX, SkillAnimBossY, 100, 100, boss.DamageGraph[2]);
    LoadDivGraph("img/Boss/summon_damageRed.png", SummonAnimBoss, SummonAnimBossX, SummonAnimBossY, 100, 100, boss.DamageGraph[3]);
    LoadDivGraph("img/Boss/idle2_damageRed.png", IdleAnimBoss, IdleAnimBossX, IdleAnimBossY, 100, 100, boss.DamageGraph[4]);


    boss.w = BossChipSize;
    boss.h = BossChipSize;
	boss.pos = VGet(668 + boss.w * 0.5f, 220 + boss.h * 0.5f, 0);
	boss.direction = VGet(0, 0, 0);
    boss.center = VGet(ScreenWidth / 2, 0, 0);
    boss.HP = BossHP;

    boss.state = BossState::Idele;

    //攻撃切り替え用
    boss.SwitchingTime = 0;
    boss.SwitchFlag = false;

    // 行動が始まったかどうかのフラグ
    boss.Idle_ON = false;
    boss.Attack_ON = false;
    boss.Rush_ON = false;
    boss.Summon_ON = false;

    boss.EnemyToTarget = VGet(0, 0, 0);

    boss.Angle = ANGLE;
    boss.radius = 0;
    boss.MoveArcFlag = false;

    //通常攻撃関連
   
    boss.AttackFlag = false;
    boss.HitAttack = false;
    boss.RigorTime = 0;
    boss.PreliminaryActionFlag = false;
    boss.PreliminaryActionTimer = 0;
    boss.AttackCount = 0;

    //突進攻撃関連
    boss.PastPlayerPos = VGet(0, 0, 0);
    boss.Conflict = false;
    boss.Rush_PreliminaryActionTimer = 0;
    boss.RushCount = 0;

    boss.TargetPos = VGet(0, 0, 0);
    boss.RushHomePos = false;
    //boss.RushDirection = false;
    boss.RushAttackNow = false;
    boss.SetNextTarget = false;

    //弾攻撃
    boss.SummonHomePos = false;
    boss.SummonEndCount = 0;

    boss.nextPos.Mid = VGet(PositionMid_X, PositionMid_Y, 0);
    boss.nextPos.MidUp = VGet(PositionMidUp_X, PositionMidUp_Y, 0);
    boss.nextPos.MidDown = VGet(PositionMidDown_X, PositionMidDown_Y, 0);
    boss.nextPos.MidLeft = VGet(PositionMidLeft_X, PositionMidLeft_Y, 0);
    boss.nextPos.MidRight = VGet(PositionMidRight_X, PositionMidRight_Y, 0);
    boss.nextPos.UpLeft = VGet(PositionUpLeft_X, PositionUpLeft_Y, 0);
    boss.nextPos.UpRight = VGet(PositionUpRight_X, PositionUpRight_Y, 0);
    boss.nextPos.DownLeft = VGet(PositionDownLeft_X, PositionDownLeft_Y, 0);
    boss.nextPos.DownRight = VGet(PositionDownRight_X, PositionDownRight_Y, 0);
    boss.nextPos.LRM = 0;
    boss.nextPos.Elevation = 0;

    //プレイヤーからの攻撃を受けたとき光るフラグ
    boss.FlashingBoss = false;

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

void InitSoul(Soul soul[])
{
    for (int i = 0; i < MaxSoulNum; i++)
    {
        soul[i].w = 50;
        soul[i].h = 50;
        soul[i].pos = VGet(0, 0, 0);
        soul[i].direction = VGet(0, 0, 0);
        soul[i].SoulToPlayer = VGet(0, 0, 0);

        SoulStandbyTime = 0;
        soul[i].ShotFlag = false;
        soul[i].PresenceFlag = false;
        soul[i].ReserveFlag = false;

        soul[i].animTimer = 0.0f;
        soul[i].animNowType = IdleSoul;
        soul[i].animNowPattern = 0;
        soul[i].animPattern = IdleAnimSoul;
        soul[i].animNowIndex = 0;
        soul[i].animPastType = IdleSoul;
    }

    LoadDivGraph("img/Soul/summonIdle.png", IdleAnimSoul, SoulIdleX, SoulIdleY, 50, 50, SoulGraph[0]);
    LoadDivGraph("img/Soul/summonAppear.png", AppearAinmSoul, SoulAppearX, SoulAppearY, 50, 50, SoulGraph[1]);
    LoadDivGraph("img/Soul/summonDeath.png", DethAnimSoul, SoulDethX, SoulDethY, 50, 50, SoulGraph[2]);

}

void UpdateBoss(Boss& boss, Soul soul[], Player& player, float deltaTime)
{
    VECTOR direction = VGet(0, 0, 0);

    int PastState = boss.state;
    int radNum = 0;

    ControlBoss(boss);

    if (boss.state == BossState::Idele)
    {
        if (boss.state == BossState::Idele && !boss.SwitchFlag && boss.SwitchingTime <= 0)
        {
            boss.SwitchingTime = 150;
        }
        

        if (boss.SwitchingTime > 0)
        {
            boss.SwitchingTime -= 1;
        }
        
        if(boss.SwitchingTime == 0)
        {
            boss.SwitchingTime = 0;
            boss.SwitchFlag = true;
        }


        if (boss.SwitchFlag)
        {
            radNum = GetRand(2);
            boss.state = radNum + 1;
            boss.SwitchFlag = false;
        }
        
    }

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

    case BossState::AttackScythe:
        UpdateBossAttack(boss, player, deltaTime);
        break;

    case BossState::Rush:
        UpdateBossRush(boss, player, deltaTime);
        break;

    case BossState::SummonSoul:
        UpdateBossSummon(boss, player, soul, deltaTime);
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
        boss.FlashingBoss = true;
        OneHit1 = true;
    }
    if (!player.AttackFlag)
    {
        
        OneHit1 = false;
    }

    if (player.AttackFlag_2 && player.HitAttack && !OneHit2)
    {
        boss.HP -= 1;
        boss.FlashingBoss = true;
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
        if (boss.FlashingBoss)
        {
            boss.FlashingBoss = false;
        }
    }
    boss.animNowIndex = boss.animNowPattern;
}

void DrawBoss(Boss& boss)
{
    if (!boss.FlashingBoss)
    {
        if (boss.RightMove)
        {
            DrawRotaGraph3(static_cast<int>(boss.pos.x), static_cast<int>(boss.pos.y), boss.w / 2, boss.h / 2, 2.5, 2.5, 0, boss.BossGraph[boss.animNowType][boss.animNowPattern], TRUE, TRUE);
        }
        if (!boss.RightMove)
        {
            DrawRotaGraph3(static_cast<int>(boss.pos.x), static_cast<int>(boss.pos.y), boss.w / 2, boss.h / 2, 2.5, 2.5, 0, boss.BossGraph[boss.animNowType][boss.animNowPattern], TRUE, FALSE);
        }
    }
    else
    {
        if (boss.RightMove)
        {
            DrawRotaGraph3(static_cast<int>(boss.pos.x), static_cast<int>(boss.pos.y), boss.w / 2, boss.h / 2, 2.5, 2.5, 0, boss.DamageGraph[boss.animNowType][boss.animNowPattern], TRUE, TRUE);
        }
        if (!boss.RightMove)
        {
            DrawRotaGraph3(static_cast<int>(boss.pos.x), static_cast<int>(boss.pos.y), boss.w / 2, boss.h / 2, 2.5, 2.5, 0, boss.DamageGraph[boss.animNowType][boss.animNowPattern], TRUE, FALSE);
        }
    }
   

    
    
    //DrawBox(static_cast<int>(boss.pos.x - 80.0f), static_cast<int>(boss.pos.y - 50.0f), static_cast<int>(boss.pos.x + 80.0f), static_cast<int>(boss.pos.y + 50.0f), GetColor(255, 125, 0), FALSE);

    //DrawCircle(boss.center.x, boss.center.y, 10, GetColor(255, 0, 0), TRUE);
    //DrawLine(boss.center.x, boss.center.y, boss.pos.x, boss.pos.y, GetColor(255, 255, 255), TRUE);
  

}

void DrawSoul(Soul soul[])
{
    for (int i = 0; i < MaxSoulNum; i++)
    {
        if (soul[i].PresenceFlag)
        {
            DrawRotaGraph3(static_cast<int>(soul[i].pos.x), static_cast<int>(soul[i].pos.y), soul[i].w * 0.5f, soul[i].h * 0.5f, 1.5f, 1.5f, 0, SoulGraph[soul[i].animNowType][soul[i].animNowIndex], TRUE, FALSE);
            
            
        }
    }
    
}

void DrawBossUI(Boss& boss)
{
    //ボスHPの表示
    DrawBox(BossHpPositionX - 1, BossHpPositionY - 1, BossHpPositionX + BossHpLength,BossHpPositionY + 11, GetColor(0, 0, 0), TRUE);
    DrawBox(BossHpPositionX, BossHpPositionY, BossHpPositionX + (boss.HP * 20), BossHpPositionY + 10, GetColor(255, 0, 0), TRUE);
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

    boss.EnemyToTarget = VSub(player.pos, boss.pos);

    if (boss.RigorTime <= 0)
    {
        boss.direction = VNorm(boss.EnemyToTarget);

        VECTOR velocity = VScale(boss.direction, boss.moveSpeed * 2);

        boss.pos = VAdd(boss.pos, velocity);
    }
    
    //一定範囲内にプレイヤーが入ったら攻撃をする
    //アニメーションの変更
    if (!boss.PreliminaryActionFlag && boss.RigorTime <= 0 && 
        (player.pos.x - boss.pos.x) < 125 && (player.pos.x - boss.pos.x) > -125 && 
        (player.pos.y - boss.pos.y) < 50 && (player.pos.y - boss.pos.y) > -50)
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
        boss.AttackCount += 1;
    }

    //硬直時間を減らす
    if (boss.RigorTime > 0)
    {
        boss.RigorTime -= 1;
    }
    
    if (boss.AttackCount > 2)
    {
        boss.state = BossState::Idele;
    }
    UpdateAnimationBoss(boss, deltaTime);

}

void UpdateBossRush(Boss& boss, Player& player, float deltaTime)
{
    if (!boss.Rush_ON)
    {
        boss.Rush_ON = true;
        boss.RushHomePos = false;
        boss.RushAttackNow = false;
        boss.SetNextTarget = false;
        boss.Rush_PreliminaryActionTimer = 0;
        boss.RushCount = 0;

        boss.nextPos.LRM = GetRand(1);
        boss.nextPos.Elevation = 2;
        DeterminePosition(boss);
    }

    //攻撃開始位置へ移動
    if (!boss.RushHomePos)
    {

        boss.EnemyToTarget = VSub(boss.TargetPos, boss.pos);
        //正規化
        if (VSize(boss.EnemyToTarget) > 0)
        {
            boss.direction = VNorm(boss.EnemyToTarget);
        }
        //移動
        VECTOR velocity = VScale(boss.direction, boss.moveSpeed * 2);
        boss.pos = VAdd(boss.pos, velocity);
        if (VSize(boss.EnemyToTarget) <= 10)
        {
            boss.Rush_PreliminaryActionTimer = 37;
            boss.RushHomePos = true;
        }
    }

    if (boss.Rush_PreliminaryActionTimer > 0)
    {
        boss.Rush_PreliminaryActionTimer -= 1;
    }
    else
    {
        boss.Rush_PreliminaryActionTimer == 0;
    }


    if (!boss.SetNextTarget && boss.RushHomePos && boss.Rush_PreliminaryActionTimer == 0)
    {
        switch (boss.RushCount)
        {
        case 0:
            if (boss.nextPos.LRM == 0)
            {
                boss.nextPos.LRM = 1;
                boss.nextPos.Elevation = 2;
                DeterminePosition(boss);
            }
            else if (boss.nextPos.LRM == 1)
            {
                boss.nextPos.LRM = 0;
                boss.nextPos.Elevation = 2;
                DeterminePosition(boss);
            }
            break;
        case 1:
            if (boss.nextPos.LRM == 0)
            {
                boss.nextPos.LRM = 1;
                boss.nextPos.Elevation = 1;
                DeterminePosition(boss);
            }
            else if (boss.nextPos.LRM == 1)
            {
                boss.nextPos.LRM = 0;
                boss.nextPos.Elevation = 1;
                DeterminePosition(boss);
            }
            break;
        case 2:
            if (boss.nextPos.LRM == 0)
            {
                boss.nextPos.LRM = 1;
                boss.nextPos.Elevation = 1;
                DeterminePosition(boss);
            }
            else if (boss.nextPos.LRM == 1)
            {
                boss.nextPos.LRM = 0;
                boss.nextPos.Elevation = 1;
                DeterminePosition(boss);
            }
            break;
        case 3:
            if (boss.nextPos.LRM == 0)
            {
                boss.nextPos.LRM = 1;
                boss.nextPos.Elevation = 2;
                DeterminePosition(boss);
            }
            else if (boss.nextPos.LRM == 1)
            {
                boss.nextPos.LRM = 0;
                boss.nextPos.Elevation = 2;
                DeterminePosition(boss);
            }
            break;
        default:
            break;
        }
        boss.animNowType = Skill;
        boss.animPattern = SkillAnimBoss;

        boss.SetNextTarget = true;
        boss.RushAttackNow = true;
        boss.RushCount++;
    }

    if (boss.RushAttackNow)
    {
        boss.EnemyToTarget = VSub(boss.TargetPos, boss.pos);
        //正規化
        if (VSize(boss.EnemyToTarget) > 0)
        {
            boss.direction = VNorm(boss.EnemyToTarget);
        }
        //移動
        VECTOR velocity = VScale(boss.direction, boss.moveSpeed * 5);
        boss.pos = VAdd(boss.pos, velocity);
        if (VSize(boss.EnemyToTarget) <= 10)
        {
            boss.RushAttackNow = false;
            boss.SetNextTarget = false;
        }
    }

    if (boss.RushCount > 4)
    {
        boss.state = BossState::Idele;
    }
    UpdateAnimationBoss(boss, deltaTime);
}

void DeterminePosition(Boss& boss)
{
    if (boss.nextPos.LRM == 0)   //左
    {
        switch (boss.nextPos.Elevation)
        {
        case 0:
            //boss.EnemyToPlayer = VSub(boss.nextPos.UpLeft,boss.pos);
            boss.TargetPos = boss.nextPos.UpLeft;
            break;
        case 1:
            //boss.EnemyToPlayer = VSub(boss.nextPos.MidLeft, boss.pos);
            boss.TargetPos = boss.nextPos.MidLeft;

            break;
        case 2:
            //boss.EnemyToPlayer = VSub(boss.nextPos.DownLeft, boss.pos);
            boss.TargetPos = boss.nextPos.DownLeft;

            break;
        default:
            break;
        }
    }
    else if (boss.nextPos.LRM == 1)  //右
    {
        switch (boss.nextPos.Elevation)
        {
        case 0:
            //boss.EnemyToPlayer = VSub(boss.nextPos.UpRight, boss.pos);
            boss.TargetPos = boss.nextPos.UpRight;

            break;
        case 1:
           // boss.EnemyToPlayer = VSub(boss.nextPos.MidRight, boss.pos);
            boss.TargetPos = boss.nextPos.MidRight;

            break;
        case 2:
            //boss.EnemyToPlayer = VSub(boss.nextPos.DownRight, boss.pos);
            boss.TargetPos = boss.nextPos.DownRight;

            break;
        default:
            break;
        }
    }
    else if (boss.nextPos.LRM == 2)  //中央
    {
        switch (boss.nextPos.Elevation)
        {
        case 0:
            //boss.EnemyToPlayer = VSub(boss.nextPos.UpRight, boss.pos);
            boss.TargetPos = boss.nextPos.MidUp;

            break;
        case 1:
            // boss.EnemyToPlayer = VSub(boss.nextPos.MidRight, boss.pos);
            boss.TargetPos = boss.nextPos.Mid;

            break;
        case 2:
            //boss.EnemyToPlayer = VSub(boss.nextPos.DownRight, boss.pos);
            boss.TargetPos = boss.nextPos.MidDown;

            break;
        default:
            break;
        }
    }
}

void UpdateBossSummon(Boss& boss, Player& player, Soul soul[], float deltaTime)
{
    if (!boss.Summon_ON)
    {
        InitSoul(soul);
        SoulPresenceAll = false;
        boss.nextPos.LRM = 2;
        boss.nextPos.Elevation = 1;
        boss.SummonHomePos = false;
        boss.Summon_ON = true;
        boss.animNowType = Summon;
        boss.animPattern = SummonAnimBoss;
        DeterminePosition(boss);
    }

    //攻撃開始位置へ移動
    if (!boss.SummonHomePos)
    {
        boss.EnemyToTarget = VSub(boss.TargetPos, boss.pos);
        //正規化
        if (VSize(boss.EnemyToTarget) > 0)
        {
            boss.direction = VNorm(boss.EnemyToTarget);
        }
        //移動
        VECTOR velocity = VScale(boss.direction, boss.moveSpeed * 2);
        boss.pos = VAdd(boss.pos, velocity);

        if (VSize(boss.EnemyToTarget) <= 10)
        {
            boss.SummonHomePos = true;
        }
    }

    if (boss.SummonHomePos)
    {
       
        UpdateSoul(soul, boss, player);
    }

    player.HitEnemy = UpdateHitBossShot(soul, player);

    controlHP(player, boss);
    UpdateAnimationBoss(boss, deltaTime);
}

void UpdateSoul(Soul soul[], Boss& boss, Player& player)
{
    //弾をボスの周りに出現させる
    for (int i = 0; i < MaxSoulNum; i++) 
    {
        if (!soul[i].PresenceFlag && SoulStandbyTime == 0 && !SoulPresenceAll)
        {
            switch (i)
            {
            case 0:
                soul[i].pos = VGet(boss.pos.x - 50, boss.pos.y - 50, 0);
                break;
            case 1:
                soul[i].pos = VGet(boss.pos.x + 50, boss.pos.y - 50, 0);
                break;
            case 2:
                soul[i].pos = VGet(boss.pos.x + 50, boss.pos.y + 50, 0);
                break;
            case 3:
                soul[i].pos = VGet(boss.pos.x - 50, boss.pos.y + 50, 0);
                break;
            default:
                break;
            }

            

            soul[i].animNowType = AppearSoul;
            soul[i].animPattern = AppearAinmSoul;

            SoulStandbyTime = 100;
            soul[i].PresenceFlag = true;
            break;             
        }

        if (soul[i].animNowType == AppearSoul && soul[i].animPattern - 1 == soul[i].animNowPattern)
        {
            soul[i].ReserveFlag = true;
            soul[i].animNowType = IdleSoul;
            soul[i].animPattern = IdleAnimSoul;
        }

        if (SoulStandbyTime > 0)
        {
            SoulStandbyTime -= 1;
        }
        else
        {
            SoulStandbyTime = 0;
        }
    }

    if (soul[3].PresenceFlag)
    {
        SoulPresenceAll = true;
        boss.animNowType = Idle;
        boss.animPattern = IdleAnimBoss;
    }

    if (SoulPresenceAll)
    {
        boss.SummonEndCount = 0;
        // 弾の移動をさせる
        for (int i = 0; i < MaxSoulNum; i++)
        {

            if (!soul[i].ShotFlag && SoulStandbyTime == 0 && soul[i].PresenceFlag)
            {
                soul[i].SoulToPlayer = VSub(player.pos, soul[i].pos);
                soul[i].ShotFlag = true;
                SoulStandbyTime = 200;
            }

            if (soul[i].ShotFlag && soul[i].PresenceFlag)
            {
                //正規化
                if (VSize(soul[i].SoulToPlayer) > 0)
                {
                    soul[i].direction = VNorm(soul[i].SoulToPlayer);
                }
                //移動
                VECTOR velocity = VScale(soul[i].direction, 6);
                soul[i].pos = VAdd(soul[i].pos, velocity);
            }

            if (!soul[i].PresenceFlag)
            {
                boss.SummonEndCount += 1;
            }
        }

        //弾発射のディレイ
        if (SoulStandbyTime > 0)
        {
            SoulStandbyTime -= 1;
        }
        else
        {
            SoulStandbyTime = 0;
        }
        //弾が画面外に行ったら表示を消す
        OffScreenSoul(soul);
        if (boss.SummonEndCount > 3)
        {
            boss.state = BossState::Idele;
        }
    }
    
}

void OffScreenSoul(Soul soul[])
{
    for (int i = 0; i < MaxSoulNum; i++)
    {
        if (soul[i].pos.x < 0 || soul[i].pos.x > ScreenWidth ||
            soul[i].pos.y < 0 || soul[i].pos.y > ScreenHeight)
        {
            soul[i].PresenceFlag = false;
            soul[i].ShotFlag = false;
        }
    }
}

void UpdateAnimationSoul(Soul soul[], float deltaTime)
{
    for (int i = 0; i < MaxSoulNum; i++)
    {
        if (soul[i].PresenceFlag)
        {
            if (soul[i].animPastType != soul[i].animNowType)
            {
                soul[i].animPastType = soul[i].animNowType;
                soul[i].animNowPattern = 0;
            }


            //魂アニメーション
            soul[i].animTimer += deltaTime;
            if (soul[i].animTimer > 1.0f / soul[i].animPattern)
            {

                soul[i].animTimer = 0.0f;
                soul[i].animNowPattern++;
                if (soul[i].animNowPattern == soul[i].animPattern)
                {
                    soul[i].animNowPattern = 0;
                }
            }

            soul[i].animNowIndex = soul[i].animNowPattern;
           
        }
        
    }
   
}

void ControlHP(Boss& boss)
{

}
