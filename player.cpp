#include"DxLib.h"
#include "screen.h"
#include "map.h"
#include "player.h"
#include "collision.h"
#include "Boss.h"
#include <math.h>
      
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

bool HitEnemyAttack = false;	//敵の攻撃に当たったかどうか

//プレイヤー初期化
void InitPlayer(Player& player)
{
    player.w = PlayerSize;
    player.h = PlayerSize;

    player.pos = VGet(64 + PlayerChipSize * 0.5f, PlayerChipSize * 0.5f, 0);
    player.direction = VGet(0, 0, 0);
    
    player.isGround = true;
    player.isHitTop = false;

    player.fallSpeed = 0.0f;

    //------------------------------
    player.HP = 5;

    //-----------------------------
    // 当たり判定に関する変数
    //-----------------------------
    player.HitEnemy = false;
    player.invincibleTime = INITNUM;
    //player.CanNotOperateTime = 0;
    player.HitAttack = false;
    //-----------------------------
    // 回避に関する変数
    //-----------------------------
    player.DashFlag = false;
    player.DashTimer = INITNUM;
    //-----------------------------
    // 攻撃に関する変数
    //-----------------------------
    player.AttackFlag = false;
    player.AttackFlag_2 = false;

    player.JumpAttackFlag = false;
    player.JumpAttackFlag_2 = false;

    player.AttackTimerFlag = false;

    player.TimerFlag = false;
    player.TimerFlag_2 = false;

    player.AttackTimer = INITNUM;
    player.AttackTimer_2 = INITNUM;

    player.AttackIntervalTimer_1 = INITNUM;
    player.AttackIntervalTimer_2 = INITNUM;

    player.PrevAttackFlag = false;
    player.PrevJumpFlag = false;

    //-------------------------
    //アニメーション関係
    //-------------------------
    player.animNowType = Idle_Animation;
    player.animPattern = IDLE;
    player.animTimer = INITNUM;
    player.animNowPattern = INITNUM;
    player.animNowIndex = INITNUM;

    player.animPastType = player.animNowType;

    player.Graph_LR = false;
    player.Move_L = false;
    player.Move_R = false;

    LoadDivGraph("img/DarkSamurai (64x64).png", PlayerImg_Xnum * PlayerImg_Ynum, PlayerImg_Xnum, PlayerImg_Ynum, 64, 64, player.PlayerAnimation);

}

//プレイヤーアニメーション
void UpdateAnimationPlayer(Player& player, Boss& boss, Map&map, float deltaTime)
{
    
    //---------------------------------
    // アニメーション計算
    //---------------------------------
    bool isMove = UpdatePlayer(player,boss,map, deltaTime);
    //-----------------------------------------------------
    // 操作されていないときIdleアニメーションに変更
    //----------------------------------------------------
    if (!player.AttackFlag_2 && !player.AttackFlag && !isMove)
    {
        player.animNowType = Idle_Animation;
        player.animPattern = IDLE;
    }

    //------------------------------------------------------
    // ジャンプが開始されたらアニメーション変更
    //-----------------------------------------------------
    if (!player.AttackFlag_2 && !player.AttackFlag && player.fallSpeed < 0.0f)
    {

        player.animNowType = Jump_Animation;
        player.animPattern = JUMP;
    }
    //----------------------------------------------------------
    //落ちるときにアニメーション変更
    //----------------------------------------------------------
    else if (!player.AttackFlag_2 && !player.AttackFlag && player.fallSpeed > 0.0f)
    {
        player.animNowType = Fall_Animation;
        player.animPattern = FALL;
    }

    //-------------------------------------------------------------------
    //攻撃のフラグがTRUEかつタイマーが0の時攻撃１のアニメーションに変更
    //-------------------------------------------------------------------
    if (player.AttackFlag && !player.TimerFlag)
    {
        player.animNowType = Attack_Animation_1;
        player.animPattern = ATTACK_1;
        player.AttackTimer = AttackCoolTime_1;
        player.TimerFlag = true;
        player.AttackIntervalTimer_1 = AttackWaitingTime_1;
    }
    else if (player.AttackFlag_2 && !player.TimerFlag_2)
    {
        player.animNowType = Attack_Animation_2;
        player.animPattern = ATTACK_2;
        player.AttackTimer_2 = AttackCoolTime_2;
        player.TimerFlag_2 = true;
        player.AttackIntervalTimer_2 = AttackWaitingTime_2;
    }

    //-------------------------------------------------------------------
    // 攻撃を受けたら点滅
    //-------------------------------------------------------------------
   /* if (player.invincibleTime > 0)
    {
        player.animNowType = Hit_Animation;
        player.animPattern = HIT;
    }*/

    //-------------------------------------------------------------------
    //アニメーションが変更されたらそのアニメーションの最初から描画
    //-------------------------------------------------------------------
    if (player.animPastType != player.animNowType)
    {
        player.animPastType = player.animNowType;
        player.animNowPattern = INITNUM;
        if (player.animNowType == Hit_Animation)
        {
            player.animNowPattern = 1;
        }
    }

    //-------------------------------------------------------------------
    // 攻撃のフラグがTRUEの時はアニメーションを１ループで終わる
    //-------------------------------------------------------------------
    if (player.animNowType == Attack_Animation_1 || player.animNowType == Attack_Animation_2)
    {
        player.animTimer += deltaTime;
        if (player.animTimer > 1.0f / player.animPattern)
        {
            player.animTimer = 0.0f;
            player.animNowPattern++;
            
            if (player.animNowPattern > player.animPattern - 1)
            {
                player.animNowPattern = player.animPattern - 1;
            }
        }
    }
    else
    {
        //アニメーション
        player.animTimer += deltaTime;
        if (player.animTimer > 1.0f / player.animPattern)
        {

            player.animTimer = 0.0f;
            player.animNowPattern++;
            if (player.animNowPattern == player.animPattern)
            {
                player.animNowPattern = 0;
            }
        }
    }

   //------------------------------
   // 攻撃が終わるまでの時間処理
   //------------------------------
    //攻撃１
    if(player.AttackTimer != 0)
    {
        player.AttackTimer -= TimerDecrease;
        if (player.AttackTimer > 0 && player.AttackTimer < 20)
        {
            player.AttackTimerFlag = true;
        }
        else
        {
            player.AttackTimerFlag = false;
        }
    }
    else 
    {
        player.AttackFlag = false;
        player.TimerFlag = false;
    }
    //攻撃２
    if (player.AttackTimer_2 != 0)
    {
        player.AttackTimer_2 -= TimerDecrease;
    }
    else
    {
        player.AttackFlag_2 = false;
        player.TimerFlag_2 = false;
    }

    //------------------------------
    // 攻撃インターバルの処理
    //------------------------------
    if (player.AttackIntervalTimer_1 != 0)
    {
        player.AttackIntervalTimer_1 -= TimerDecrease;
    }

    if (player.AttackIntervalTimer_2 != 0)
    {
        player.AttackIntervalTimer_2 -= TimerDecrease;
    }
    //------------------------------
    // 回避インターバルの処理
    //------------------------------
    if (player.DashTimer != 0)
    {
        player.DashTimer -= TimerDecrease;
    }
    
    //最終的な画像配列の添え字計算
    // 添え字 = 一つのパターンのコマ数 + アニメーション種類 * １つのアニメーションのパターン枚数
    player.animNowIndex = player.animNowPattern + player.animNowType * PlayerImg_Xnum;
}

//プレイヤー描画
void DrawPlayer(Player &player)
{
    if ((static_cast<int>(player.invincibleTime) / 10) % 2 == 0)
    {
        //キャラクターの描画
        if (!player.Graph_LR)
        {
            DrawGraph(static_cast<int>(player.pos.x - player.w), static_cast<int>(player.pos.y - player.w), player.PlayerAnimation[player.animNowIndex], TRUE);
        }
        if (player.Graph_LR)
        {
            DrawTurnGraph(static_cast<int>(player.pos.x - player.w), static_cast<int>(player.pos.y - player.h), player.PlayerAnimation[player.animNowIndex], TRUE);
        }
    }

    
    //DrawBox(player.pos.x - 32.0f, player.pos.y - 16.0f, player.pos.x + 32.0f, player.pos.y + 16.0f, GetColor(255, 125, 0), FALSE);
    //DrawCircle(player.pos.x, player.pos.y, 1, GetColor(255, 255, 255), TRUE);
    DrawBox(static_cast<int>(player.pos.x - PlayerCollisionX), static_cast<int>(player.pos.y - PlayerCollisionY),static_cast<int>(player.pos.x + PlayerCollisionX), static_cast<int>(player.pos.y + PlayerCollisionY), GetColor(0, 255, 0), FALSE);

}

//プレイヤー関連UI描画
void DrawPlayerUI(Player& player)
{
    DrawBox(DrawHpPositionX - 1, DrawHpPositionY - 1, DrawHpPositionX + 1 + HP1GageSizeX * 5, DrawHpPositionY + HP1GageSizeY + 1, GetColor(255, 255, 255), TRUE);
    DrawBox(DrawHpPositionX, DrawHpPositionY, DrawHpPositionX + HP1GageSizeX * player.HP, DrawHpPositionY + HP1GageSizeY, GetColor(0, 255, 0), TRUE);
    SetFontSize(10);
    DrawFormatString(DrawHpPositionX, DrawHpPositionY - 11, GetColor(255, 255, 255), "PLAYER HP");
}

//プレイヤー更新
bool UpdatePlayer(Player& player, Boss& boss, Map& map, float deltaTime)
{
    bool isMove = false;
    bool jump = false;

    player.direction = VGet(0, 0, 0);

       
    //-----------------------------------------------------------------------------
       // 左右移動
       //-----------------------------------------------------------------------------
       //左
    if (CheckHitKey(KEY_INPUT_LEFT) && !player.AttackFlag_2 && !player.AttackFlag)
    {
        //移動
        player.direction = VGet(-1, 0, 0);
        //アニメーション
        player.animNowType = Run_Animation;
        player.animPattern = RUN;
        player.Move_L = true;

        isMove = true;
    }
    else
    {
        player.Move_L = false;
    }
    //右
    if (CheckHitKey(KEY_INPUT_RIGHT) && !player.AttackFlag_2 && !player.AttackFlag)
    {
        //移動
        player.direction = VGet(1, 0, 0);
        //アニメーション
        player.animNowType = Run_Animation;
        player.animPattern = RUN;
        player.Move_R = true;

        isMove = true;
    }
    else
    {
        player.Move_R = false;
    }

    //回避
    if (CheckHitKey(KEY_INPUT_C) && player.DashTimer == 0)
    {
        player.DashFlag = true;
        player.DashTimer = DashCoolTime;
    }

    //移動キーが同時押しされたらその場にとどまる
    if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_LEFT) && !player.AttackFlag_2 && !player.AttackFlag)
    {
        player.direction = VGet(0, 0, 0);
        player.animNowType = Idle_Animation;
        player.animPattern = IDLE;
    }

    //攻撃ボタンが押されたらフラグをTRUEにする
    if (CheckHitKey(KEY_INPUT_X) && !player.AttackFlag && player.AttackIntervalTimer_1 == 0 && player.AttackIntervalTimer_2 == 0 && !player.JumpAttackFlag && !player.PrevAttackFlag)
    {
        player.AttackFlag = true;

        if (!player.isGround)
        {
            player.JumpAttackFlag = true;
        }
    }
    else if (CheckHitKey(KEY_INPUT_X) && !player.AttackFlag_2 && player.AttackFlag && (player.AttackIntervalTimer_1 > 10 && player.AttackIntervalTimer_1 < 30) && !player.JumpAttackFlag_2 && !player.PrevAttackFlag)
    {
        player.AttackFlag_2 = true;
        if (!player.isGround)
        {
            player.JumpAttackFlag_2 = true;
        }
    }

    //攻撃ボタン長押し防止
    if (CheckHitKey(KEY_INPUT_X))
    {
        player.PrevAttackFlag = true;
    }
    else
    {
        player.PrevAttackFlag = false;
    }

   
    //描画方向
    if (!player.Move_R && player.Move_L)
    {
        player.Graph_LR = true;
    }
    if (player.Move_R && !player.Move_L)
    {
        player.Graph_LR = false;
    }

    //正規化
    if (VSquareSize(player.direction) > 0)
    {
        player.direction = VNorm(player.direction);
    }

    //移動量を代入
    VECTOR velocity = VScale(player.direction, PlayerSpeed);

    //落下速度を更新
    player.fallSpeed += Gravity;

    //地面と接しているか確認
    CheckHitGround(player, map);
    CheckHitTop(player, map);

    //地面に接して居たらジャンプ攻撃フラグをFalseに
    if (player.isGround)
    {
        player.JumpAttackFlag = false;
        player.JumpAttackFlag_2 = false;
    }

    //地面に接地しているかつスペースキーが押されたときジャンプする
    if (CheckHitKey(KEY_INPUT_Z) && !player.AttackFlag && player.isGround && !player.PrevJumpFlag)
    {
        player.fallSpeed = -JumpPower;
        player.isGround = false;
    }

    //ジャンプボタン長押し防止
    if (CheckHitKey(KEY_INPUT_Z))
    {
        player.PrevJumpFlag = true;
    }
    else
    {
        player.PrevJumpFlag = false;
    }

    //ジャンプ攻撃中のみ落下速度を遅くする
    if (!player.isGround && (player.AttackFlag || player.AttackFlag_2 || player.DashFlag))
    {
        player.fallSpeed = 0.0F;
    }

    //落下速度を移動量に加える
    VECTOR fallVelocity = VGet(0, player.fallSpeed, 0);
    velocity = VAdd(velocity, fallVelocity);

   //=======================
   //敵との当たり判定
   //======================
   //ボスとのあたりはんてい
    player.HitEnemy = UpdateHitBox(boss, player);
    controlHP(player,boss);
    
    /*if (player.HitEnemy)
    {
        VECTOR KnockBackDistance = KnockBack(player);
        velocity = VGet(KnockBackDistance.x, 0, 0);
    }*/

    // ダッシュ
    if (player.DashFlag && !player.Graph_LR)
    {
        VECTOR DashVelocity = VGet(DashDistance, 0, 0);
        velocity = VAdd(velocity, DashVelocity);
        player.DashFlag = false;
    }
    else if (player.DashFlag && player.Graph_LR)
    {
        VECTOR DashVelocity = VGet(-DashDistance, 0, 0);
        velocity = VAdd(velocity, DashVelocity);
        player.DashFlag = false;
    }

    //当たり判定をし、壁にめり込まないようにvelocityを操作する
    velocity = CheckPlayerHitMap(player, map,velocity);

    //移動
    player.pos = VAdd(player.pos, velocity);

    MovementLimit(player);
 
    return isMove;
}

//プレイヤーがマップに当たっているか
bool IsHitPlayerWithMapChip(const Player& player, const MapChip& mapChip, VECTOR& futurePos)
{
    if (mapChip.chipKind < 22)
    {
        return false;
    }

    //マップチップに当たっているかどうか調べる
    float futurePosLeft = futurePos.x - player.w * 0.3f;
    float futurePosRight = futurePos.x + player.w * 0.3f;
    float futurePosTop = futurePos.y - player.h * 0.5f;
    float futurePosBottom = futurePos.y + player.h * 0.5f;

    float targetLeft = mapChip.pos.x - mapChip.w * 0.5f;
	float targetRight = mapChip.pos.x + mapChip.w * 0.5f;
	float targetTop = mapChip.pos.y - mapChip.h * 0.5f;
	float targetBottom = mapChip.pos.y + mapChip.h * 0.5f;

    if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
        (targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
        ((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
            (targetTop > futurePosTop && targetTop < futurePosBottom)))
    {
        return true;
    }
    return false;
}

//プレイヤーの未来の移動先でマップチップに当たっていたら当たらなくなるまで位置を修正する
VECTOR CheckPlayerHitMap(Player& player, const Map& map, VECTOR& velocity)
{
    if (VSize(velocity) == 0)
    {
        return velocity;
    }

    VECTOR ret = velocity; 

    bool loop = true;
    bool isFirstHit = true;
    while (loop)
    {
        loop = false;

        VECTOR futurePos = VAdd(player.pos, ret);

        for (int iy = 0; iy < MapHeight; iy++)
        {
            bool isHit = false;
            for (int ix = 0; ix < MapWidth; ix++)
            {
                isHit = IsHitPlayerWithMapChip(player, map.MapChips[iy][ix], futurePos);
                //初回当たった時
                if (isHit && isFirstHit)
                {
                    //小数点以下切り捨て
                    player.pos.x = floorf(player.pos.x);
                    player.pos.y = floorf(player.pos.y);
                    ret.x = floorf(ret.x);
                    ret.y = floorf(ret.y);
                    isFirstHit = false;
                    loop = true;
                }

                // 
                if (isHit && !isFirstHit)
                {
                    float absX = fabsf(ret.x);
                    float absY = fabsf(ret.y);

                    bool shrinkX = (absX != 0.0f);

                    if (shrinkX)
                    {
                        if (ret.x > 0.0f)
                        {
                            ret.x -= 1.0f;
                        }
                        else
                        {
                            ret.x += 1.0f;
                        }

                        //縮め切ったら消す
                        if (fabs(ret.x) < 1.0f)
                        {
                            ret.x = 0.0f;
                        }
                        loop = true;
                    }
                    else
                    {
                        if (ret.y > 0.0f)
                        {
                            ret.y -= 1.0f;
                        }
                        else
                        {
                            ret.y += 1.0f;
                        }

                        //縮めきったら消す
                        if (fabs(ret.y) < 1.0f)
                        {
                            ret.y = 0.0f;
                        }
                        loop = true;
                    }
                    break;
                }
            }
            if (isHit)
            {
                break;
            }
        }
    }
    return ret;
}

//プレイヤーが地面に当たっているか
void CheckHitGround(Player& player, const Map& map)
{
    VECTOR checkGround = VGet(player.pos.x, player.pos.y + 0.1f, player.pos.z);

    bool isHit = false;
    for (int iy = 0; iy < MapHeight; iy++)
    {
        for (int ix = 0; ix < MapWidth; ix++)
        {
            isHit = IsHitPlayerWithMapChip(player, map.MapChips[iy][ix], checkGround);
            if (isHit)
            {
                break;
            }
        }
        if (isHit)
        {
            break;
        }
    }
    if (isHit)
    {
        player.isGround = true;

        player.fallSpeed = 0.0f;

        player.pos.y = floorf(player.pos.y);
    }
    else
    {
        player.isGround = false;
    }
}

//プレイヤーの頭上が当たっているか
void CheckHitTop(Player& player, const Map& map)
{
    VECTOR checkTop = VGet(player.pos.x, player.pos.y - 1.0f, player.pos.z);

    bool isHit = false;
    for (int iy = 0; iy < MapHeight; iy++)
    {
        for (int ix = 0; ix < MapWidth; ix++)
        {
            isHit = IsHitPlayerWithMapChip(player, map.MapChips[iy][ix], checkTop);
            if (isHit)
            {
                break;
            }
        }
        if (isHit)
        {
            break;
        }
    }
    if (isHit)
    {
        if (!player.isHitTop)
        {
            player.isHitTop = true;
            player.fallSpeed = 0.0f;

            player.pos.y = floorf(player.pos.y);
        }


    }
    else
    {
        player.isHitTop = false;
    }
     
}

//プレイヤーHP管理
void controlHP(Player& player,Boss& boss)
{
    //敵に当たったとき無敵時間の設定とHPの減少
    if (player.invincibleTime == 0 && player.HitEnemy)
    {
        player.HP -= 1;
        player.invincibleTime = InvincibleTime;
        player.HitEnemy = false;
    }
    //ボスの攻撃がプレイヤーに当たったとき
    if (player.invincibleTime == 0 && boss.AttackFlag && boss.HitAttack && !HitEnemyAttack)
    {
        player.HP -= 1;
        player.invincibleTime = InvincibleTime;
        HitEnemyAttack = true;
    }
    if (!boss.AttackFlag)
    {
        HitEnemyAttack = false;
    }


    if (player.HP <= 0)
    {
        player.HP = 0;
    }

    //無敵時間タイマーを減らす
    if (player.invincibleTime > 0)
    {
        player.invincibleTime -= 1;
    }
    else
    {
        player.invincibleTime = 0;
    }



    ////ノックバックされるときに操作できない時間を少しつける
    //if (player.CanNotOperateTime == 0 && player.HitEnemy) {
    //    player.CanNotOperateTime = 20;
    //}
    //操作不能時間を減らす
    /*if (player.CanNotOperateTime > 0){
        player.CanNotOperateTime -= 1;
    }
    else {
        player.CanNotOperateTime = 0;
    }*/
}

VECTOR KnockBack(Player& player)
{
    VECTOR knockBack = VGet(0, 0, 0);
    //プレイヤーが右を向いているとき左方向にノックバック
    if (!player.Graph_LR)
    {
        knockBack = VGet(-50, 0, 0);
    }
    else if (player.Graph_LR)
    {
        knockBack = VGet(50, 0, 0);
    }

    return knockBack;
}

//プレイヤーがマップ外に行かないように戻す
void MovementLimit(Player& player)
{
    if (player.pos.x > 756.0f)
    {
        player.pos.x = 756.0f;
    }
    if (player.pos.x < 44.0f)
    {
        player.pos.x = 44.0f;
    }
}