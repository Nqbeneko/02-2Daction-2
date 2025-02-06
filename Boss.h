#pragma once
const int BossHP = 15;
const float ANGLE = 45.0f;
const float BossSpeed = 2.0f;

const int BossHpPositionX = 800 / 2 - ((BossHP * 20) / 2);
const int BossHpPositionY = 430;

const int BossHpLength = BossHP * 20 + 1;

//----------------------------
// Boss�A�j���[�V����
//----------------------------
const int BossChipSize = 100;       // �{�X�̏c���̑傫��

const int Idle = 0;                 
const int Attack = 1;
const int Skill = 2;
const int Summon = 3;
const int PreliminaryAction = 4;
const int Appearance = 5;
const int Deth = 6;

const int IdleAnimBossX = 4;        // �ҋ@�摜��������(��)
const int IdleAnimBossY = 2;        // �ҋ@�摜��������(�c)
const int AttackAnimBossX = 6;      // �U���摜��������(��)
const int AttackAnimBossY = 3;      // �U���摜��������(�c)
const int SkillAnimBossX = 6;       // �X�L���摜��������(��)
const int SkillAnimBossY = 2;       // �X�L���摜��������(�c)
const int SummonAnimBossX = 4;      // �����摜��������(��)
const int SummonAnimBossY = 2;      // �����摜��������(�c)
const int AppearanceAnimBossX = 19; // �o���摜��������(��)
const int AppearanceAnimBossY = 1;  // �o���摜��������(�c)
const int DethAnimBossX = 10; // �o���摜��������(��)
const int DethAnimBossY = 2;  // �o���摜��������(�c)

const int IdleAnimBoss = 8;         // �ҋ@���[�V������
const int AttackAnimBoss = 13;      // �U�����[�V������
const int SkillAnimBoss = 12;       // �X�L�����[�V������
const int SummonAnimBoss = 5;       // �������[�V������
const int PreliminaryActionAnimBoss = 8;    //�U���\������
const int AppearanceAnimBoss = 19;   //�o���A�j���[�V������
const int DethAnimBoss = 18;         //���S�A�j���[�V������

//----------------------------
// Boss�֘A
//----------------------------
const int PositionMid_X = 400;          //����X
const int PositionMid_Y = 176;          //����Y
const int PositionMidUp_X = 400;        //������X
const int PositionMidUp_Y = 50;         //������Y
const int PositionMidDown_X = 400;      //������X
const int PositionMidDown_Y = 312;      //������Y
const int PositionMidLeft_X = 62;       //������X
const int PositionMidLeft_Y = 176;      //������Y
const int PositionMidRight_X = 736;     //�����EX
const int PositionMidRight_Y = 176;     //�����EY
const int PositionUpLeft_X = 62;        //����X
const int PositionUpLeft_Y = 50;        //����Y
const int PositionUpRight_X = 736;      //�E��X
const int PositionUpRight_Y = 50;       //�E��Y
const int PositionDownLeft_X = 62;      //����X
const int PositionDownLeft_Y = 312;     //����Y
const int PositionDownRight_X = 736;    //�E��X
const int PositionDownRight_Y = 312;    //�E��Y

//----------------------------
// ���A�j���[�V�����֘A
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
// �G�t�F�N�g�֘A
//----------------------------

const int AttackEfect = 0;
const int RushEfect = 1;

enum BossState
{
    Idele,              // �ҋ@
    AttackScythe,       // �U���P
    Rush,               // �ːi�U��
    SummonSoul,         // �e���������ł�
    Appear,             //�o��
    Dead               // ����ł�
};

struct Position
{
    VECTOR Mid;         //����
    VECTOR MidUp;       //������
    VECTOR MidDown;     //������
    VECTOR MidLeft;     //������
    VECTOR MidRight;    //�����E
    VECTOR UpLeft;      //����
    VECTOR UpRight;     //�E��
    VECTOR DownLeft;    //����
    VECTOR DownRight;   //�E��
    int LRM;             //�U���J�n����(0->��,1->�E,2->����)
    int Elevation;      //�U���J�n�ʒu�̍���(0->��A1->�����A2->��)
};

struct Boss
{
    int state;
    Position nextPos;
    

    VECTOR pos;             // ���W
    VECTOR direction;       // ����
    VECTOR center;          // ���S���W

    float w, h;             // �c����
    float moveSpeed;        // �ړ����x
    int HP;                 // �̗�
    bool RightMove;         // 
    int BossGraph[7][19];   // �{�X���[�V�����摜
    int DamageGraph[5][13]; //�U�����󂯂��Ƃ��̃{�X�摜
    int UIGraph[5];

    VECTOR EnemyToTarget;

    int RigorTime;          //�U����d������

    bool Idle_ON;           //Idle��Ԃ̎�true

    float Angle;
    float radius;
    bool MoveArcFlag;

    //�U���؂�ւ��p
    int SwitchingTime;
    bool SwitchFlag;
    bool SwitchingTimeFlag;
    //�ʏ�U���֘A
    bool Attack_ON;
    bool AttackFlag;
    bool HitAttack;             //�{�X�̍U���������������ǂ���
    bool PreliminaryActionFlag;
    int PreliminaryActionTimer; //�\�����쎞��
    int AttackCount;            //�U���񐔁i3��s������I���j

    //�ːi�U���֘A
    VECTOR PastPlayerPos;
    VECTOR TargetPos;
    bool Rush_ON;
    bool Conflict;
    int Rush_PreliminaryActionTimer;    //�\�����쎞��
    int RushCount;

    bool RushHomePos;       //�ːi�U���Ɉڂ�����Œ�̈ʒu�ֈړ�������
    bool RushAttackNow;     //�ːi���Ă��邩
    bool SetNextTarget;     //���̖ڕW�ʒu�����܂�����

    //�v���C���[����̍U�����󂯂��Ƃ�����t���O
    bool FlashingBoss;

    //�����A�e�U���֘A
    bool Summon_ON;
    bool SummonHomePos;
    int SummonEndCount;
    
    //�o���A���S�A�j���[�V�����֘A
    bool Appear_ON;
    bool Deth_ON;


    //�A�j���[�V�����֘A
    float animTimer;        // �A�j���[�V�����^�C�}�[
    int animNowType;        // ���݂̃A�j���[�V�����̎��
    int animNowPattern;     // ���݂̃A�j���[�V�����p�^�[��
    int animPattern;        // ���݂̃A�j���[�V�����摜��
    int animNowIndex;       // ���݂̃A�j���[�V�����摜�z��̓Y����(0�`112)
    int animPastType;       // 1�O�̃A�j���[�V�����摜��
};

struct Soul
{
    VECTOR SoulToPlayer;    // ������v���C���[�ւ̃x�N�g��
    VECTOR pos;             // ���W
    VECTOR direction;       // ����
    float w, h;             // �c����

    int StandbyTime;
    bool PresenceFlag;      // ��ʏ�ɑ��݂��Ă��邩�̃t���O
    bool ReserveFlag;       // �����o�����I��������̃t���O
    bool ShotFlag;
   

    float animTimer;        // �A�j���[�V�����^�C�}�[
    int animNowType;        // ���݂̃A�j���[�V�����̎��
    int animNowPattern;     // ���݂̃A�j���[�V�����p�^�[��
    int animPattern;        // ���݂̃A�j���[�V�����摜��
    int animNowIndex;       // ���݂̃A�j���[�V�����摜�z��̓Y����(0�`112)
    int animPastType;       // 1�O�̃A�j���[�V�����摜��
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

