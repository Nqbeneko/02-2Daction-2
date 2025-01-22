#pragma once

struct Boss;
struct Player;

void ControlBoss(Boss& boss);

void DrawBossPosition(Boss& boss);

void SelectDrawManageUI(Player& palyer, Boss& boss,Soul soul[]);