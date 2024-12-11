#include"DxLib.h"
#include "screen.h"
#include "map.h"
#include "player.h"
#include "collision.h"
#include "Boss.h"
#include <math.h>
      
//�@�萔
const int INITNUM = 0;                  //�������p�̂O
const int AttackCoolTime_1 = 30;        //�U���P�N�[���^�C��
const int AttackCoolTime_2 = 30;        //�U���Q�N�[���^�C��
const int AttackWaitingTime_1 = 50;     //�U���Q�ւȂ���܂ł̑҂�����
const int AttackWaitingTime_2 = 35;     //�U���P���g����悤�ɂȂ�܂ł̑҂�����

const float PlayerCollisionX = 10.0f;   //�v���C���[��X�������蔻��͈�
const float PlayerCollisionY = 16.0f;   //�v���C���[��Y�������蔻��͈�

const int DashCoolTime = 50;            //�_�b�V���N�[���^�C��
const int DashDistance = 100;           //�_�b�V������

const int InvincibleTime = 100;         //���G����

//UI�֌W
const int DrawHpPositionX = 30;
const int DrawHpPositionY = 400;
const int HP1GageSizeX = 30;
const int HP1GageSizeY = 10;

const int TimerDecrease = 1;            //�^�C�}�[�̎��Ԃ����炷��

bool HitEnemyAttack = false;	//�G�̍U���ɓ����������ǂ���

//�v���C���[������
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
    // �����蔻��Ɋւ���ϐ�
    //-----------------------------
    player.HitEnemy = false;
    player.invincibleTime = INITNUM;
    //player.CanNotOperateTime = 0;
    player.HitAttack = false;
    //-----------------------------
    // ����Ɋւ���ϐ�
    //-----------------------------
    player.DashFlag = false;
    player.DashTimer = INITNUM;
    //-----------------------------
    // �U���Ɋւ���ϐ�
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
    //�A�j���[�V�����֌W
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

//�v���C���[�A�j���[�V����
void UpdateAnimationPlayer(Player& player, Boss& boss, Map&map, float deltaTime)
{
    
    //---------------------------------
    // �A�j���[�V�����v�Z
    //---------------------------------
    bool isMove = UpdatePlayer(player,boss,map, deltaTime);
    //-----------------------------------------------------
    // ���삳��Ă��Ȃ��Ƃ�Idle�A�j���[�V�����ɕύX
    //----------------------------------------------------
    if (!player.AttackFlag_2 && !player.AttackFlag && !isMove)
    {
        player.animNowType = Idle_Animation;
        player.animPattern = IDLE;
    }

    //------------------------------------------------------
    // �W�����v���J�n���ꂽ��A�j���[�V�����ύX
    //-----------------------------------------------------
    if (!player.AttackFlag_2 && !player.AttackFlag && player.fallSpeed < 0.0f)
    {

        player.animNowType = Jump_Animation;
        player.animPattern = JUMP;
    }
    //----------------------------------------------------------
    //������Ƃ��ɃA�j���[�V�����ύX
    //----------------------------------------------------------
    else if (!player.AttackFlag_2 && !player.AttackFlag && player.fallSpeed > 0.0f)
    {
        player.animNowType = Fall_Animation;
        player.animPattern = FALL;
    }

    //-------------------------------------------------------------------
    //�U���̃t���O��TRUE���^�C�}�[��0�̎��U���P�̃A�j���[�V�����ɕύX
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
    // �U�����󂯂���_��
    //-------------------------------------------------------------------
   /* if (player.invincibleTime > 0)
    {
        player.animNowType = Hit_Animation;
        player.animPattern = HIT;
    }*/

    //-------------------------------------------------------------------
    //�A�j���[�V�������ύX���ꂽ�炻�̃A�j���[�V�����̍ŏ�����`��
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
    // �U���̃t���O��TRUE�̎��̓A�j���[�V�������P���[�v�ŏI���
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
        //�A�j���[�V����
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
   // �U�����I���܂ł̎��ԏ���
   //------------------------------
    //�U���P
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
    //�U���Q
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
    // �U���C���^�[�o���̏���
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
    // ����C���^�[�o���̏���
    //------------------------------
    if (player.DashTimer != 0)
    {
        player.DashTimer -= TimerDecrease;
    }
    
    //�ŏI�I�ȉ摜�z��̓Y�����v�Z
    // �Y���� = ��̃p�^�[���̃R�}�� + �A�j���[�V������� * �P�̃A�j���[�V�����̃p�^�[������
    player.animNowIndex = player.animNowPattern + player.animNowType * PlayerImg_Xnum;
}

//�v���C���[�`��
void DrawPlayer(Player &player)
{
    if ((static_cast<int>(player.invincibleTime) / 10) % 2 == 0)
    {
        //�L�����N�^�[�̕`��
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

//�v���C���[�֘AUI�`��
void DrawPlayerUI(Player& player)
{
    DrawBox(DrawHpPositionX - 1, DrawHpPositionY - 1, DrawHpPositionX + 1 + HP1GageSizeX * 5, DrawHpPositionY + HP1GageSizeY + 1, GetColor(255, 255, 255), TRUE);
    DrawBox(DrawHpPositionX, DrawHpPositionY, DrawHpPositionX + HP1GageSizeX * player.HP, DrawHpPositionY + HP1GageSizeY, GetColor(0, 255, 0), TRUE);
    SetFontSize(10);
    DrawFormatString(DrawHpPositionX, DrawHpPositionY - 11, GetColor(255, 255, 255), "PLAYER HP");
}

//�v���C���[�X�V
bool UpdatePlayer(Player& player, Boss& boss, Map& map, float deltaTime)
{
    bool isMove = false;
    bool jump = false;

    player.direction = VGet(0, 0, 0);

       
    //-----------------------------------------------------------------------------
       // ���E�ړ�
       //-----------------------------------------------------------------------------
       //��
    if (CheckHitKey(KEY_INPUT_LEFT) && !player.AttackFlag_2 && !player.AttackFlag)
    {
        //�ړ�
        player.direction = VGet(-1, 0, 0);
        //�A�j���[�V����
        player.animNowType = Run_Animation;
        player.animPattern = RUN;
        player.Move_L = true;

        isMove = true;
    }
    else
    {
        player.Move_L = false;
    }
    //�E
    if (CheckHitKey(KEY_INPUT_RIGHT) && !player.AttackFlag_2 && !player.AttackFlag)
    {
        //�ړ�
        player.direction = VGet(1, 0, 0);
        //�A�j���[�V����
        player.animNowType = Run_Animation;
        player.animPattern = RUN;
        player.Move_R = true;

        isMove = true;
    }
    else
    {
        player.Move_R = false;
    }

    //���
    if (CheckHitKey(KEY_INPUT_C) && player.DashTimer == 0)
    {
        player.DashFlag = true;
        player.DashTimer = DashCoolTime;
    }

    //�ړ��L�[�������������ꂽ�炻�̏�ɂƂǂ܂�
    if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_LEFT) && !player.AttackFlag_2 && !player.AttackFlag)
    {
        player.direction = VGet(0, 0, 0);
        player.animNowType = Idle_Animation;
        player.animPattern = IDLE;
    }

    //�U���{�^���������ꂽ��t���O��TRUE�ɂ���
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

    //�U���{�^���������h�~
    if (CheckHitKey(KEY_INPUT_X))
    {
        player.PrevAttackFlag = true;
    }
    else
    {
        player.PrevAttackFlag = false;
    }

   
    //�`�����
    if (!player.Move_R && player.Move_L)
    {
        player.Graph_LR = true;
    }
    if (player.Move_R && !player.Move_L)
    {
        player.Graph_LR = false;
    }

    //���K��
    if (VSquareSize(player.direction) > 0)
    {
        player.direction = VNorm(player.direction);
    }

    //�ړ��ʂ���
    VECTOR velocity = VScale(player.direction, PlayerSpeed);

    //�������x���X�V
    player.fallSpeed += Gravity;

    //�n�ʂƐڂ��Ă��邩�m�F
    CheckHitGround(player, map);
    CheckHitTop(player, map);

    //�n�ʂɐڂ��ċ�����W�����v�U���t���O��False��
    if (player.isGround)
    {
        player.JumpAttackFlag = false;
        player.JumpAttackFlag_2 = false;
    }

    //�n�ʂɐڒn���Ă��邩�X�y�[�X�L�[�������ꂽ�Ƃ��W�����v����
    if (CheckHitKey(KEY_INPUT_Z) && !player.AttackFlag && player.isGround && !player.PrevJumpFlag)
    {
        player.fallSpeed = -JumpPower;
        player.isGround = false;
    }

    //�W�����v�{�^���������h�~
    if (CheckHitKey(KEY_INPUT_Z))
    {
        player.PrevJumpFlag = true;
    }
    else
    {
        player.PrevJumpFlag = false;
    }

    //�W�����v�U�����̂ݗ������x��x������
    if (!player.isGround && (player.AttackFlag || player.AttackFlag_2 || player.DashFlag))
    {
        player.fallSpeed = 0.0F;
    }

    //�������x���ړ��ʂɉ�����
    VECTOR fallVelocity = VGet(0, player.fallSpeed, 0);
    velocity = VAdd(velocity, fallVelocity);

   //=======================
   //�G�Ƃ̓����蔻��
   //======================
   //�{�X�Ƃ̂�����͂�Ă�
    player.HitEnemy = UpdateHitBox(boss, player);
    controlHP(player,boss);
    
    /*if (player.HitEnemy)
    {
        VECTOR KnockBackDistance = KnockBack(player);
        velocity = VGet(KnockBackDistance.x, 0, 0);
    }*/

    // �_�b�V��
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

    //�����蔻������A�ǂɂ߂荞�܂Ȃ��悤��velocity�𑀍삷��
    velocity = CheckPlayerHitMap(player, map,velocity);

    //�ړ�
    player.pos = VAdd(player.pos, velocity);

    MovementLimit(player);
 
    return isMove;
}

//�v���C���[���}�b�v�ɓ������Ă��邩
bool IsHitPlayerWithMapChip(const Player& player, const MapChip& mapChip, VECTOR& futurePos)
{
    if (mapChip.chipKind < 22)
    {
        return false;
    }

    //�}�b�v�`�b�v�ɓ������Ă��邩�ǂ������ׂ�
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

//�v���C���[�̖����̈ړ���Ń}�b�v�`�b�v�ɓ������Ă����瓖����Ȃ��Ȃ�܂ňʒu���C������
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
                //���񓖂�������
                if (isHit && isFirstHit)
                {
                    //�����_�ȉ��؂�̂�
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

                        //�k�ߐ؂��������
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

                        //�k�߂����������
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

//�v���C���[���n�ʂɓ������Ă��邩
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

//�v���C���[�̓��オ�������Ă��邩
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

//�v���C���[HP�Ǘ�
void controlHP(Player& player,Boss& boss)
{
    //�G�ɓ��������Ƃ����G���Ԃ̐ݒ��HP�̌���
    if (player.invincibleTime == 0 && player.HitEnemy)
    {
        player.HP -= 1;
        player.invincibleTime = InvincibleTime;
        player.HitEnemy = false;
    }
    //�{�X�̍U�����v���C���[�ɓ��������Ƃ�
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

    //���G���ԃ^�C�}�[�����炷
    if (player.invincibleTime > 0)
    {
        player.invincibleTime -= 1;
    }
    else
    {
        player.invincibleTime = 0;
    }



    ////�m�b�N�o�b�N�����Ƃ��ɑ���ł��Ȃ����Ԃ���������
    //if (player.CanNotOperateTime == 0 && player.HitEnemy) {
    //    player.CanNotOperateTime = 20;
    //}
    //����s�\���Ԃ����炷
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
    //�v���C���[���E�������Ă���Ƃ��������Ƀm�b�N�o�b�N
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

//�v���C���[���}�b�v�O�ɍs���Ȃ��悤�ɖ߂�
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