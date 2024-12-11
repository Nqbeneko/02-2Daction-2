#pragma once



//----------------------------
// Boss�A�j���[�V����
//----------------------------
const int BossChipSize = 100;       // �{�X�̏c���̑傫��

const int Idle = 0;                 
const int Attack = 1;
const int Skill = 2;
const int Summon = 3;

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


struct Boss
{
    VECTOR pos;             // ���W
    VECTOR direction;       // ����
    VECTOR center;          // ���S���W

    float w, h;             // �c����
    float moveSpeed;        // �ړ����x
    int HP;                 // �̗�
    bool RightMove;
    int BossGraph[4][13];   // �{�X���[�V�����摜


    float Angle;
    float radius;
    bool MoveArcFlag;

    bool AttackFlag;
    int RigorTime;          //�U����d������
    bool HitAttack;          //�{�X�̍U���������������ǂ���

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

void UpdateBoss(Boss& boss, Soul& soul, Player& player);

void UpdateAnimationBoss(Boss& boss, Soul& soul,float deltaTime);

void DrawBoss(Boss& boss, Soul& soul,Player&player);

void DrawBossUI(Boss& boss);

void MoveArc(Boss& boss);

void MoveAttack(Boss& boss, Player& player);

void AttackSkill(Boss& boss, Player& player);

void ControlHP(Boss& boss);