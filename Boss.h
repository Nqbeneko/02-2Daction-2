#pragma once



//----------------------------
// Bossアニメーション
//----------------------------
const int BossChipSize = 100;       // ボスの縦横の大きさ

const int Idle = 0;                 
const int Attack = 1;
const int Skill = 2;
const int Summon = 3;

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


struct Boss
{
    VECTOR pos;             // 座標
    VECTOR direction;       // 方向
    VECTOR center;          // 中心座標

    float w, h;             // 縦横幅
    float moveSpeed;        // 移動速度
    int HP;                 // 体力
    bool RightMove;
    int BossGraph[4][13];   // ボスモーション画像


    float Angle;
    float radius;
    bool MoveArcFlag;

    bool AttackFlag;
    int RigorTime;          //攻撃後硬直時間
    bool HitAttack;          //ボスの攻撃が当たったかどうか

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

void UpdateBoss(Boss& boss, Soul& soul, Player& player);

void UpdateAnimationBoss(Boss& boss, Soul& soul,float deltaTime);

void DrawBoss(Boss& boss, Soul& soul,Player&player);

void DrawBossUI(Boss& boss);

void MoveArc(Boss& boss);

void MoveAttack(Boss& boss, Player& player);

void AttackSkill(Boss& boss, Player& player);

void ControlHP(Boss& boss);