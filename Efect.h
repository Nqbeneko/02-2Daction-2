#pragma once

const int RushEyeEfect = 0;


struct Efect
{
    int Graph[6][7];
    //�A�j���[�V�����֘A
    float animTimer;        // �A�j���[�V�����^�C�}�[
    int animNowType;        // ���݂̃A�j���[�V�����̎��
    int animNowPattern;     // ���݂̃A�j���[�V�����p�^�[��
    int animPattern;        // ���݂̃A�j���[�V�����摜��
    int animNowIndex;       // ���݂̃A�j���[�V�����摜�z��̓Y����(0�`112)
    int animPastType;       // 1�O�̃A�j���[�V�����摜��
};

struct Boss;

void InitBossEfect(Efect& efect);

void BossRushPreliminaryAction(Efect& efect,Boss&boss);

void DrawBossEfect(Efect& efect, Boss& boss);
