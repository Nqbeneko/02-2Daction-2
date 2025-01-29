#pragma once

const int RushEyeEfect = 0;

const int DashEffect = 0;
const int DashPatternNum = 14;


struct Effect
{
    int Graph[6][16];
    //�A�j���[�V�����֘A
    float animTimer;        // �A�j���[�V�����^�C�}�[
    int animNowType;        // ���݂̃A�j���[�V�����̎��
    int animNowPattern;     // ���݂̃A�j���[�V�����p�^�[��
    int animPattern;        // ���݂̃A�j���[�V�����摜��
    int animNowIndex;       // ���݂̃A�j���[�V�����摜�z��̓Y����(0�`112)
    int animPastType;       // 1�O�̃A�j���[�V�����摜��
};

struct Boss;
struct Player;

void InitBossEffect(Effect& efect);

void InitPlayerEffect(Effect& playeffect);

void BossRushPreliminaryAction(Effect& effect,Boss& boss);

void UpdatePlayerDashEfect(Effect& effect, Player& player);

void DrawBossEfect(Effect& effect, Boss& boss);

void DrawPlayerDashEffect(Effect& effect, Player& player);