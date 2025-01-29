#pragma once

const int RushEyeEfect = 0;

const int DashEffect = 0;
const int DashPatternNum = 14;


struct Effect
{
    int Graph[6][16];
    //アニメーション関連
    float animTimer;        // アニメーションタイマー
    int animNowType;        // 現在のアニメーションの種類
    int animNowPattern;     // 現在のアニメーションパターン
    int animPattern;        // 現在のアニメーション画像数
    int animNowIndex;       // 現在のアニメーション画像配列の添え字(0～112)
    int animPastType;       // 1つ前のアニメーション画像数
};

struct Boss;
struct Player;

void InitBossEffect(Effect& efect);

void InitPlayerEffect(Effect& playeffect);

void BossRushPreliminaryAction(Effect& effect,Boss& boss);

void UpdatePlayerDashEfect(Effect& effect, Player& player);

void DrawBossEfect(Effect& effect, Boss& boss);

void DrawPlayerDashEffect(Effect& effect, Player& player);