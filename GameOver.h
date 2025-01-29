#pragma once

struct Player;

class GameOver
{
private:
    int Graph;
    float Scale;
    float timer;
    float StopTimer;

    float QuakeTime;
    float addPosX;
    float addPosY;
    bool addFlag;

    bool OverFlag;
    bool AnimEnd;

public:
    void Init();
    void Progress(Player& player);
    void Draw();
    void DrawPlayer(Player& player);
    void AnimationPlayer(Player& player);
};