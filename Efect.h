#pragma once

const int RushEyeEfect = 0;


struct Efect
{
    int Graph[6][7];
    //アニメーション関連
    float animTimer;        // アニメーションタイマー
    int animNowType;        // 現在のアニメーションの種類
    int animNowPattern;     // 現在のアニメーションパターン
    int animPattern;        // 現在のアニメーション画像数
    int animNowIndex;       // 現在のアニメーション画像配列の添え字(0～112)
    int animPastType;       // 1つ前のアニメーション画像数
};

struct Boss;

void InitBossEfect(Efect& efect);

void BossRushPreliminaryAction(Efect& efect,Boss&boss);

void DrawBossEfect(Efect& efect, Boss& boss);
