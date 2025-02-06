#pragma once
const int BossHP = 15;
const float ANGLE = 45.0f;
const float BossSpeed = 2.0f;

const int BossHpPositionX = 800 / 2 - ((BossHP * 20) / 2);
const int BossHpPositionY = 430;

const int BossHpLength = BossHP * 20 + 1;

//----------------------------
// Bossアニメーション
//----------------------------
const int BossChipSize = 100;       // ボスの縦横の大きさ

const int Idle = 0;                 
const int Attack = 1;
const int Skill = 2;
const int Summon = 3;
const int PreliminaryAction = 4;
const int Appearance = 5;
const int Deth = 6;

const int IdleAnimBossX = 4;        // 待機画像分割枚数(横)
const int IdleAnimBossY = 2;        // 待機画像分割枚数(縦)
const int AttackAnimBossX = 6;      // 攻撃画像分割枚数(横)
const int AttackAnimBossY = 3;      // 攻撃画像分割枚数(縦)
const int SkillAnimBossX = 6;       // スキル画像分割枚数(横)
const int SkillAnimBossY = 2;       // スキル画像分割枚数(縦)
const int SummonAnimBossX = 4;      // 召喚画像分割枚数(横)
const int SummonAnimBossY = 2;      // 召喚画像分割枚数(縦)
const int AppearanceAnimBossX = 19; // 出現画像分割枚数(横)
const int AppearanceAnimBossY = 1;  // 出現画像分割枚数(縦)
const int DethAnimBossX = 10; // 出現画像分割枚数(横)
const int DethAnimBossY = 2;  // 出現画像分割枚数(縦)

const int IdleAnimBoss = 8;         // 待機モーション数
const int AttackAnimBoss = 13;      // 攻撃モーション数
const int SkillAnimBoss = 12;       // スキルモーション数
const int SummonAnimBoss = 5;       // 召喚モーション数
const int PreliminaryActionAnimBoss = 8;    //攻撃予備動作
const int AppearanceAnimBoss = 19;   //出現アニメーション数
const int DethAnimBoss = 18;         //死亡アニメーション数

//----------------------------
// Boss関連
//----------------------------
const int PositionMid_X = 400;          //中央X
const int PositionMid_Y = 176;          //中央Y
const int PositionMidUp_X = 400;        //中央上X
const int PositionMidUp_Y = 50;         //中央上Y
const int PositionMidDown_X = 400;      //中央下X
const int PositionMidDown_Y = 312;      //中央下Y
const int PositionMidLeft_X = 62;       //中央左X
const int PositionMidLeft_Y = 176;      //中央左Y
const int PositionMidRight_X = 736;     //中央右X
const int PositionMidRight_Y = 176;     //中央右Y
const int PositionUpLeft_X = 62;        //左上X
const int PositionUpLeft_Y = 50;        //左上Y
const int PositionUpRight_X = 736;      //右上X
const int PositionUpRight_Y = 50;       //右上Y
const int PositionDownLeft_X = 62;      //左下X
const int PositionDownLeft_Y = 312;     //左下Y
const int PositionDownRight_X = 736;    //右下X
const int PositionDownRight_Y = 312;    //右下Y

//----------------------------
// 魂アニメーション関連
//----------------------------

const int IdleSoul = 0;
const int AppearSoul = 1;
const int DethSoul = 2;

const int SoulIdleX = 4;
const int SoulIdleY = 1;
const int SoulAppearX = 3;
const int SoulAppearY = 2;
const int SoulDethX = 3;
const int SoulDethY = 2;

const int IdleAnimSoul = 4;
const int AppearAinmSoul = 6;
const int DethAnimSoul = 5;

const int MaxSoulNum = 4;

//----------------------------
// エフェクト関連
//----------------------------

const int AttackEfect = 0;
const int RushEfect = 1;

enum BossState
{
    Idele,              // 待機
    AttackScythe,       // 攻撃１
    Rush,               // 突進攻撃
    SummonSoul,         // 弾を召喚し打つ
    Appear,             //出現
    Dead               // 死んでる
};

struct Position
{
    VECTOR Mid;         //中央
    VECTOR MidUp;       //中央上
    VECTOR MidDown;     //中央下
    VECTOR MidLeft;     //中央左
    VECTOR MidRight;    //中央右
    VECTOR UpLeft;      //左上
    VECTOR UpRight;     //右上
    VECTOR DownLeft;    //左下
    VECTOR DownRight;   //右下
    int LRM;             //攻撃開始方向(0->左,1->右,2->中央)
    int Elevation;      //攻撃開始位置の高さ(0->上、1->中央、2->下)
};

struct Boss
{
    int state;
    Position nextPos;
    

    VECTOR pos;             // 座標
    VECTOR direction;       // 方向
    VECTOR center;          // 中心座標

    float w, h;             // 縦横幅
    float moveSpeed;        // 移動速度
    int HP;                 // 体力
    bool RightMove;         // 
    int BossGraph[7][19];   // ボスモーション画像
    int DamageGraph[5][13]; //攻撃を受けたときのボス画像
    int UIGraph[5];

    VECTOR EnemyToTarget;

    int RigorTime;          //攻撃後硬直時間

    bool Idle_ON;           //Idle状態の時true

    float Angle;
    float radius;
    bool MoveArcFlag;

    //攻撃切り替え用
    int SwitchingTime;
    bool SwitchFlag;
    bool SwitchingTimeFlag;
    //通常攻撃関連
    bool Attack_ON;
    bool AttackFlag;
    bool HitAttack;             //ボスの攻撃が当たったかどうか
    bool PreliminaryActionFlag;
    int PreliminaryActionTimer; //予備動作時間
    int AttackCount;            //攻撃回数（3回行ったら終了）

    //突進攻撃関連
    VECTOR PastPlayerPos;
    VECTOR TargetPos;
    bool Rush_ON;
    bool Conflict;
    int Rush_PreliminaryActionTimer;    //予備動作時間
    int RushCount;

    bool RushHomePos;       //突進攻撃に移った後固定の位置へ移動したか
    bool RushAttackNow;     //突進しているか
    bool SetNextTarget;     //次の目標位置が決まったか

    //プレイヤーからの攻撃を受けたとき光るフラグ
    bool FlashingBoss;

    //召喚、弾攻撃関連
    bool Summon_ON;
    bool SummonHomePos;
    int SummonEndCount;
    
    //出現、死亡アニメーション関連
    bool Appear_ON;
    bool Deth_ON;


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
    VECTOR SoulToPlayer;    // 魂からプレイヤーへのベクトル
    VECTOR pos;             // 座標
    VECTOR direction;       // 方向
    float w, h;             // 縦横幅

    int StandbyTime;
    bool PresenceFlag;      // 画面上に存在しているかのフラグ
    bool ReserveFlag;       // 魂が出現し終わったかのフラグ
    bool ShotFlag;
   

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
class SE;

void InitBoss(Boss& boss);

void InitSoul(Soul soul[]);

void UpdateBoss(Boss& boss, Soul soul[],Player& player, float deltaTime,SE* se);

void UpdateAnimationBoss(Boss& boss,float deltaTime);

void UpdateSoul(Soul soul[], Boss& boss, Player& player, SE* se);

void UpdateAnimationSoul(Soul soul[], float deltaTime);

void OffScreenSoul(Soul soul[]);

void DrawBoss(Boss& boss);

void DrawSoul(Soul soul[]);

void DrawBossUI(Boss& boss);

void DrawEfect(Boss& boss);

void MoveArc(Boss& boss);

void UpdateBossIdle(Boss& boss, float deltaTime, SE* se);

void UpdateBossAttack(Boss& boss, Player& player, float deltaTime, SE* se);

void UpdateBossRush(Boss& boss, Player& player, float deltaTime, SE* se);

void DeterminePosition(Boss& boss);

void UpdateBossSummon(Boss& boss, Player& player,Soul soul[], float deltaTime, SE* se);

void UpdateAppear(Boss& boss,float deltaTime, SE* se);

void ControlHP(Boss& boss);

