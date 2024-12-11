#pragma once

struct Collision
{
    float PosLeft;
    float PosRight;
    float PosTop;
    float PosBottom;
};

struct Player;
struct Boss;

/// <summary>
/// �v���C���[�U�������蔻�菉����
/// </summary>
/// <param name="playerCol_L"></param>
/// <param name="playerCol_R"></param>
void InitPlayerAttackCollision(Collision& playerCol_L,Collision&playerCol_R);

/// <summary>
/// �{�X�U�������蔻�菉����
/// </summary>
/// <param name="boss1_L"></param>
/// <param name="boss1_R"></param>
/// <param name="boss2"></param>
void InitBossAttackCollision(Collision& boss1_L, Collision& boss1_R,Collision &boss2);

//�����蔻��ʒu�̍X�V

/// <summary>
/// �v���C���[�U�������蔻��ʒu�̍X�V
/// </summary>
/// <param name="playerCol_L"></param>
/// <param name="playerCol_R"></param>
/// <param name="player"></param>
void UpdatePlayerAttackCollision(Collision& playerCol_L, Collision& playerCol_R, Player& player);

/// <summary>
/// �{�X�U�������蔻��ʒu�̍X�V
/// </summary>
/// <param name="boss1_L"></param>
/// <param name="boss1_R"></param>
/// <param name="boss2"></param>
/// <param name="boss"></param>
void UpdateBossAttackCollision(Collision& boss1_L, Collision& boss1_R, Collision& boss2, Boss& boss);


/// <summary>
/// �G�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="boss"></param>
/// <param name="player"></param>
/// <returns></returns>
bool UpdateHitBox(Boss& boss, Player& player);

/// <summary>
/// �G�ƃv���C���[�̍U���̓����蔻��
/// </summary>
/// <param name="playerCol_L"></param>
/// <param name="playerCol_R"></param>
/// <param name="player"></param>
/// <param name="boss"></param>
/// <returns></returns>
bool UpdateHitPlayerAttack(Collision& playerCol_L, Collision& playerCol_R, Player& player,Boss& boss);

/// <summary>
/// �v���C���[�̍U���ƓG��/ </summary>
/// <param name="boss1_L"></param>
/// <param name="boss1_R"></param>
/// <param name="player"></param>
/// <param name="boss"></param>
/// <returns></returns>
bool UpdateHitBossAttack(Collision& boss1_L, Collision& boss1_R, Player& player, Boss& boss);
