#pragma once


//�v���C���[�A�j���[�V�����摜�̕�����
const int PlayerImg_Xnum = 14;              // 1�̃A�j���[�V�����̃p�^�[����
const int PlayerImg_Ynum = 8;               // �A�j���[�V�����̎�ސ�

//���ꂼ��̃A�j���[�V�����̃p�^�[��
const int Idle_Animation     = 0;           //���삵�Ă��Ȃ����
const int Run_Animation      = 1;           //����
const int Attack_Animation_1 = 2;           //�U���P
const int Attack_Animation_2 = 3;           //�U���Q
const int Jump_Animation     = 4;           //�W�����v
const int Fall_Animation     = 5;           //������
const int Hit_Animation      = 6;           //�G�̍U�����󂯂��Ƃ�
const int Die_Animation      = 7;           //HP��0�ɂȂ����Ƃ�

//���ꂼ��̃A�j���[�V�����̃p�^�[����,fps��
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
    VECTOR pos;         //���W
    VECTOR direction;
    float w, h;             // �c����
    float fallSpeed;        // �������x

    bool isGround;          // �n�ʂƐڒn���Ă��邩
    bool isHitTop;
    //----------------------------
    int HP;

    //-----------------------------
    // �����蔻��Ɋւ���ϐ�
    //-----------------------------
    bool HitEnemy;              //�G�ɓ����������̃t���O
    float invincibleTime;       //���G����
    //float CanNotOperateTime;    //����ł��Ȃ�����

    bool HitAttack;             //�U���������������̃t���O
    //-----------------------------
    // ����Ɋւ���ϐ�
    //-----------------------------

    bool DashFlag;
    int DashTimer;


    //-----------------------------
    // �U���Ɋւ���ϐ�
    //-----------------------------
    bool AttackFlag;            //�U��1���g�p������
    bool AttackFlag_2;           //�U��2���g�p������
    bool AttackTimerFlag;       //�U��1����2���ւ̓��͑҂�

    bool JumpAttackFlag;        //�W�����v�U���P���s������
    bool JumpAttackFlag_2;       //�W�����v�U���Q���s������
    
    bool PrevAttackFlag;        //�U���{�^���������h�~
    bool PrevJumpFlag;          //�W�����v�������h�~

    bool TimerFlag;             
    bool TimerFlag_2;           
    int AttackTimer;            //�U���P���I���܂ł̎���
    int AttackTimer_2;          //�U���Q���I���܂ł̎���

    int AttackIntervalTimer_1;  //�U���P�̎��̍U���܂ł̃C���^�[�o��
    int AttackIntervalTimer_2;  //�U���Q�̎��̍U���܂ł̃C���^�[�o��
    //-----------------------------
    // �A�j���[�V�����Ɋւ���ϐ�
    //-----------------------------

    float animTimer;        // �A�j���[�V�����^�C�}�[
    int animNowType;        // ���݂̃A�j���[�V�����̎��
    int animNowPattern;     // ���݂̃A�j���[�V�����p�^�[��
    int animPattern;        // ���݂̃A�j���[�V�����摜��
    int animNowIndex;       // ���݂̃A�j���[�V�����摜�z��̓Y����(0�`112)
    int animPastType;       // 1�O�̃A�j���[�V�����摜��

    int PlayerAnimation[PlayerImg_Xnum * PlayerImg_Ynum]; //�v���C���[�̉摜�n���h��
    //�����Ă�������ŕ`��̌�����ς���
    bool Graph_LR;

    //�i�s����
    bool Move_R;
    bool Move_L;
};


//----------------------------------
// �֐��v���g�^�C�v�錾
//----------------------------------
struct Map;
struct MapChip;
struct Boss;
/// <summary>
/// �v���C���[������
/// </summary>
/// <param name="player">�v���C���[�\����</param>
void InitPlayer(Player &player);

/// <summary>
/// �v���C���[�A�j���[�V����
/// </summary>
/// <param name="player">�v���C���[�\����</param>
/// <param name="deltaTime">�f���^�^�C��</param>
void UpdateAnimationPlayer(Player& player, Boss& boss, Map& map, float deltaTime);

/// <summary>
/// �v���C���[�`��
/// </summary>
/// <param name="player">�v���C���[�\����</param>
void DrawPlayer(Player& player);

void DrawPlayerUI(Player& player);


/// <summary>
/// �v���C���[�㏈��
/// </summary>
void FinalizePlayer();

/// <summary>
/// �v���C���[�X�V
/// </summary>
/// <param name="player">�v���C���[�\����</param>
/// <param name="deltaTime">�f���^�^�C��</param>
/// <returns>�����Ă��邩�̔���</returns>
bool UpdatePlayer(Player& player,Boss&boss, Map& map, float deltaTime);


bool IsHitPlayerWithMapChip(const Player& player, const MapChip& mapChip, VECTOR& futurePos);

VECTOR CheckPlayerHitMap(Player& player,const Map& map, VECTOR& velocity);

void CheckHitGround(Player& player, const Map& map);

void CheckHitTop(Player& player, const Map& map);

void controlHP(Player& player,Boss& boss);

VECTOR KnockBack(Player& player);

void MovementLimit(Player& player);