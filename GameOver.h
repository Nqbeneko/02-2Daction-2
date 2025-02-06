#pragma once

struct Player;
class Timer;

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
    void Progress(Player& player, Timer* time,int fontHandle1, int fontHandle3,SE* se);
    void Draw(Timer* time, int fontHandle1, int fontHandle3);
    void DrawPlayer(Player& player);
    void AnimationPlayer(Player& player);

    bool GetAnimEnd() { return AnimEnd; }
};