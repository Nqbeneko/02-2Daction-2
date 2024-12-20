#pragma once

//----------------------------
// Bossアニメーション
//----------------------------
const int BossChipSize = 100;       // ボスの縦横の大きさ

const int Idle = 0;                 
const int Attack = 1;
const int Skill = 2;
const int Summon = 3;
const int PreliminaryAction = 4;

const int IdleAnimBossX = 4;        // 待機画像分割枚数(横)
const int IdleAnimBossY = 2;        // 待機画像分割枚数(縦)
const int AttackAnimBossX = 6;      // 攻撃画像分割枚数(横)
const int AttackAnimBossY = 3;      // 攻撃画像分割枚数(縦)
const int SkillAnimBossX = 6;       // スキル画像分割枚数(横)
const int SkillAnimBossY = 2;       // スキル画像分割枚数(縦)
const int SummonAnimBossX = 4;      // 召喚画像分割枚数(横)
const int SummonAnimBossY = 2;      // 召喚画像分割枚数(縦)

const int IdleAnimBoss = 8;         // 待機モーション数
const int AttackAnimBoss = 13;      // 攻撃モーション数
const int SkillAnimBoss = 12;       // スキルモーション数
const int SummonAnimBoss = 5;       // 召喚モーション数
const int PreliminaryActionAnimBoss = 8;    //攻撃予備動作

//----------------------------
// エフェクト関連
//----------------------------

const int AttackEfect = 0;
const int RushEfect = 1;

enum class BossState
{
    Idele,      // 待機
    Attack,     // 攻撃１
    Rush,      // 突進攻撃
    Summon,     // 弾を召喚し打つ
    Dead        // 死んでる
};

struct Efect
{
    int EfectGraph[6][7];
    //アニメーション関連
    float animTimer;        // アニメーションタイマー
    int animNowType;        // 現在のアニメーションの種類
    int animNowPattern;     // 現在のアニメーションパターン
    int animPattern;        // 現在のアニメーション画像数
    int animNowIndex;       // 現在のアニメーション画像配列の添え字(0～112)
    int animPastType;       // 1つ前のアニメーション画像数
};

struct Boss
{
    BossState state;

    VECTOR pos;             // 座標
    VECTOR direction;       // 方向
    VECTOR center;          // 中心座標

    float w, h;             // 縦横幅
    float moveSpeed;        // 移動速度
    int HP;                 // 体力
    bool RightMove;         // 
    int BossGraph[5][13];   // ボスモーション画像

    VECTOR EnemyToPlayer;

    int RigorTime;          //攻撃後硬直時間

    bool Idle_ON;           //Idle状態の時true

    float Angle;
    float radius;
    bool MoveArcFlag;

    //通常攻撃関連
    bool Attack_ON;
    bool AttackFlag;
    bool HitAttack;             //ボスの攻撃が当たったかどうか
    bool PreliminaryActionFlag;
    int PreliminaryActionTimer; //予備動作時間
   

    //突進攻撃関連
    VECTOR PastPlayerPos;
    bool Rush_ON;
    bool Conflict;
    int RushTimer;
    int RushCount;


    //召喚、弾攻撃関連
    bool Summon_ON;


    //アニメーション関連
    float animTimer;        // アニメーションタイマー
    int animNowType;        // 現在のアニメーションの種類
    int animNowPattern;     // 現在のアニメーションパターン
    int animPattern;        // 現在のアニメーション画像数
    int animNowIndex;       // 現在のアニメーション画像配列の添え字(0～112)
    int animPastType;       // 1つ前のアニメーション画像数
};

struct Soul
{
    VECTOR pos;             // 座標
    VECTOR direction;       // 方向
    float w, h;             // 縦横幅

    float animTimer;        // アニメーションタイマー
    int animNowType;        // 現在のアニメーションの種類
    int animNowPattern;     // 現在のアニメーションパターン
    int animPattern;        // 現在のアニメーション画像数
    int animNowIndex;       // 現在のアニメーション画像配列の添え字(0～112)
    int animPastType;       // 1つ前のアニメーション画像数
};

struct Mob
{
    float x;
    float y;
};

struct Player;

void InitBoss(Boss& boss);

void InitSoul(Soul& soul);

void UpdateBoss(Boss& boss, Soul& soul, Player& player, float deltaTime);

void UpdateAnimationBoss(Boss& boss,float deltaTime);

void DrawBoss(Boss& boss, Soul& soul,Player&player);

void DrawBossUI(Boss& boss);

void DrawEfect(Boss& boss);

void MoveArc(Boss& boss);

void UpdateBossIdle(Boss& boss, float deltaTime);

void UpdateBossAttack(Boss& boss, Player& player, float deltaTime);

void UpdateBossRush(Boss& boss, Player& player, float deltaTime);

void UpdateBossSummon(Boss& boss, float deltaTime);

void ControlHP(Boss& boss);

void ControlBoss(Boss& boss);