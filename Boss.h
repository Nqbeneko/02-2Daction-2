#pragma once

//----------------------------
// Boss�A�j���[�V����
//----------------------------
const int BossChipSize = 100;       // �{�X�̏c���̑傫��

const int Idle = 0;                 
const int Attack = 1;
const int Skill = 2;
const int Summon = 3;
const int PreliminaryAction = 4;

const int IdleAnimBossX = 4;        // �ҋ@�摜��������(��)
const int IdleAnimBossY = 2;        // �ҋ@�摜��������(�c)
const int AttackAnimBossX = 6;      // �U���摜��������(��)
const int AttackAnimBossY = 3;      // �U���摜��������(�c)
const int SkillAnimBossX = 6;       // �X�L���摜��������(��)
const int SkillAnimBossY = 2;       // �X�L���摜��������(�c)
const int SummonAnimBossX = 4;      // �����摜��������(��)
const int SummonAnimBossY = 2;      // �����摜��������(�c)

const int IdleAnimBoss = 8;         // �ҋ@���[�V������
const int AttackAnimBoss = 13;      // �U�����[�V������
const int SkillAnimBoss = 12;       // �X�L�����[�V������
const int SummonAnimBoss = 5;       // �������[�V������
const int PreliminaryActionAnimBoss = 8;    //�U���\������

//----------------------------
// �G�t�F�N�g�֘A
//----------------------------

const int AttackEfect = 0;
const int RushEfect = 1;

enum class BossState
{
    Idele,      // �ҋ@
    Attack,     // �U���P
    Rush,      // �ːi�U��
    Summon,     // �e���������ł�
    Dead        // ����ł�
};

struct Efect
{
    int EfectGraph[6][7];
    //�A�j���[�V�����֘A
    float animTimer;        // �A�j���[�V�����^�C�}�[
    int animNowType;        // ���݂̃A�j���[�V�����̎��
    int animNowPattern;     // ���݂̃A�j���[�V�����p�^�[��
    int animPattern;        // ���݂̃A�j���[�V�����摜��
    int animNowIndex;       // ���݂̃A�j���[�V�����摜�z��̓Y����(0�`112)
    int animPastType;       // 1�O�̃A�j���[�V�����摜��
};

struct Boss
{
    BossState state;

    VECTOR pos;             // ���W
    VECTOR direction;       // ����
    VECTOR center;          // ���S���W

    float w, h;             // �c����
    float moveSpeed;        // �ړ����x
    int HP;                 // �̗�
    bool RightMove;         // 
    int BossGraph[5][13];   // �{�X���[�V�����摜

    VECTOR EnemyToPlayer;

    int RigorTime;          //�U����d������

    bool Idle_ON;           //Idle��Ԃ̎�true

    float Angle;
    float radius;
    bool MoveArcFlag;

    //�ʏ�U���֘A
    bool Attack_ON;
    bool AttackFlag;
    bool HitAttack;             //�{�X�̍U���������������ǂ���
    bool PreliminaryActionFlag;
    int PreliminaryActionTimer; //�\�����쎞��
   

    //�ːi�U���֘A
    VECTOR PastPlayerPos;
    bool Rush_ON;
    bool Conflict;
    int RushTimer;
    int RushCount;


    //�����A�e�U���֘A
    bool Summon_ON;


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
    VECTOR pos;             // ���W
    VECTOR direction;       // ����
    float w, h;             // �c����

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