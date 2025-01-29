#pragma once

//　定数
const int INITNUM = 0;                  //初期化用の０
const int AttackCoolTime_1 = 30;        //攻撃１クールタイム
const int AttackCoolTime_2 = 30;        //攻撃２クールタイム
const int AttackWaitingTime_1 = 50;     //攻撃２へつなげるまでの待ち時間
const int AttackWaitingTime_2 = 35;     //攻撃１が使えるようになるまでの待ち時間

const float PlayerCollisionX = 10.0f;   //プレイヤーのX軸当たり判定範囲
const float PlayerCollisionY = 16.0f;   //プレイヤーのY軸当たり判定範囲

const int DashCoolTime = 50;            //ダッシュクールタイム
const int DashDistance = 100;           //ダッシュ距離

const int InvincibleTime = 100;         //無敵時間

//UI関係
const int DrawHpPositionX = 30;
const int DrawHpPositionY = 400;
const int HP1GageSizeX = 30;
const int HP1GageSizeY = 10;

const int TimerDecrease = 1;            //タイマーの時間を減らす量

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
const int Dash_Animation     = 8;           //回避

//それぞれのアニメーションのパターン数,fps数
const int IDLE       = 8;
const int RUN        = 8;
const int ATTACK_1   = 4;
const int ATTACK_2   = 3;
const int JUMP       = 4;
const int FALL       = 4;
const int HIT        = 2;
const int DIE        = 14;
const int Dash       = 5;

const float animationFPS = 5.0f;

//
const float PlayerSpeed     = 3.0f;
const int PlayerSize        = 32;
const int PlayerChipSize    = 64;

const float JumpPower    = 8.0f;
const float Gravity      = 0.3f;

//HP関連
const int MAXHP = 8;
const int HPGraphSizeX = 500;
const int HPGraphSizeY = 428;

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
    int HpGraph;
    int HpGraphBack;

    int nameGraph;

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

    bool DashFlag;              //ダッシュが開始されたか
    int DashTimer;              //
    float Distans;              //ダッシュした距離
    int DashAnimGraph[Dash];       //ダッシュ画像

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
    int animNowIndex;       // 現在のアニメーション画像配列の添え字(0～112)
    int animPastType;       // 1つ前のアニメーション画像数

    int PlayerAnimation[PlayerImg_Xnum * PlayerImg_Ynum]; //プレイヤーの画像ハンドル
    int PlayerAnimationDamage[PlayerImg_Xnum * PlayerImg_Ynum]; //プレイヤーダメージを受けたときの画像
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
struct Effect;

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
void UpdateAnimationPlayer(Player& player, Boss& boss, Map& map, float deltaTime, XINPUT_STATE &input, Effect& effect);

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
bool UpdatePlayer(Player& player,Boss&boss, Map& map, float deltaTime, XINPUT_STATE input, Effect& effect);


bool IsHitPlayerWithMapChip(const Player& player, const MapChip& mapChip, VECTOR& futurePos);

VECTOR CheckPlayerHitMap(Player& player,const Map& map, VECTOR& velocity);

void CheckHitGround(Player& player, const Map& map);

void CheckHitTop(Player& player, const Map& map);

void controlHP(Player& player,Boss& boss);

VECTOR KnockBack(Player& player);

void MovementLimit(Player& player);