#pragma once


//プレイヤーアニメーション画像の分割数
const int PlayerImg_Xnum = 14;              // 1つのアニメーションのパターン数
const int PlayerImg_Ynum = 8;               // アニメーションの種類数

//それぞれのアニメーションのパターン
const int Idle_Animation     = 0;           //操作していない状態
const int Run_Animation      = 1;           //走り
const int Attack_Animation_1 = 2;           //攻撃１
const int Attack_Animation_2 = 3;           //攻撃２
const int Jump_Animation     = 4;           //ジャンプ
const int Fall_Animation     = 5;           //落ちる
const int Hit_Animation      = 6;           //敵の攻撃を受けたとき
const int Die_Animation      = 7;           //HPが0になったとき

//それぞれのアニメーションのパターン数,fps数
const int IDLE       = 8;
const int RUN        = 8;
const int ATTACK_1   = 4;
const int ATTACK_2   = 3;
const int JUMP       = 4;
const int FALL       = 4;
const int HIT        = 2;
const int DIE        = 14;

const float animationFPS = 5.0f;

//
const float PlayerSpeed     = 3.0f;
const int PlayerSize        = 32;
const int PlayerChipSize    = 64;

const float JumpPower    = 8.0f;
const float Gravity      = 0.3f;

struct Player
{
    VECTOR pos;         //座標
    VECTOR direction;
    float w, h;             // 縦横幅
    float fallSpeed;        // 落下速度

    bool isGround;          // 地面と接地しているか
    bool isHitTop;
    //----------------------------
    int HP;

    //-----------------------------
    // 当たり判定に関する変数
    //-----------------------------
    bool HitEnemy;              //敵に当たったかのフラグ
    float invincibleTime;       //無敵時間
    //float CanNotOperateTime;    //操作できない時間

    bool HitAttack;             //攻撃が当たったかのフラグ
    //-----------------------------
    // 回避に関する変数
    //-----------------------------

    bool DashFlag;
    int DashTimer;


    //-----------------------------
    // 攻撃に関する変数
    //-----------------------------
    bool AttackFlag;            //攻撃1を使用したか
    bool AttackFlag_2;           //攻撃2を使用したか
    bool AttackTimerFlag;       //攻撃1から2をへの入力待ち

    bool JumpAttackFlag;        //ジャンプ攻撃１を行ったか
    bool JumpAttackFlag_2;       //ジャンプ攻撃２を行ったか
    
    bool PrevAttackFlag;        //攻撃ボタン長押し防止
    bool PrevJumpFlag;          //ジャンプ長押し防止

    bool TimerFlag;             
    bool TimerFlag_2;           
    int AttackTimer;            //攻撃１が終わるまでの時間
    int AttackTimer_2;          //攻撃２が終わるまでの時間

    int AttackIntervalTimer_1;  //攻撃１の次の攻撃までのインターバル
    int AttackIntervalTimer_2;  //攻撃２の次の攻撃までのインターバル
    //-----------------------------
    // アニメーションに関する変数
    //-----------------------------

    float animTimer;        // アニメーションタイマー
    int animNowType;        // 現在のアニメーションの種類
    int animNowPattern;     // 現在のアニメーションパターン
    int animPattern;        // 現在のアニメーション画像数
    int animNowIndex;       // 現在のアニメーション画像配列の添え字(0〜112)
    int animPastType;       // 1つ前のアニメーション画像数

    int PlayerAnimation[PlayerImg_Xnum * PlayerImg_Ynum]; //プレイヤーの画像ハンドル
    //向いている方向で描画の向きを変える
    bool Graph_LR;

    //進行方向
    bool Move_R;
    bool Move_L;
};


//----------------------------------
// 関数プロトタイプ宣言
//----------------------------------
struct Map;
struct MapChip;
struct Boss;
/// <summary>
/// プレイヤー初期化
/// </summary>
/// <param name="player">プレイヤー構造体</param>
void InitPlayer(Player &player);

/// <summary>
/// プレイヤーアニメーション
/// </summary>
/// <param name="player">プレイヤー構造体</param>
/// <param name="deltaTime">デルタタイム</param>
void UpdateAnimationPlayer(Player& player, Boss& boss, Map& map, float deltaTime);

/// <summary>
/// プレイヤー描画
/// </summary>
/// <param name="player">プレイヤー構造体</param>
void DrawPlayer(Player& player);

void DrawPlayerUI(Player& player);


/// <summary>
/// プレイヤー後処理
/// </summary>
void FinalizePlayer();

/// <summary>
/// プレイヤー更新
/// </summary>
/// <param name="player">プレイヤー構造体</param>
/// <param name="deltaTime">デルタタイム</param>
/// <returns>動いているかの判定</returns>
bool UpdatePlayer(Player& player,Boss&boss, Map& map, float deltaTime);


bool IsHitPlayerWithMapChip(const Player& player, const MapChip& mapChip, VECTOR& futurePos);

VECTOR CheckPlayerHitMap(Player& player,const Map& map, VECTOR& velocity);

void CheckHitGround(Player& player, const Map& map);

void CheckHitTop(Player& player, const Map& map);

void controlHP(Player& player,Boss& boss);

VECTOR KnockBack(Player& player);

void MovementLimit(Player& player);