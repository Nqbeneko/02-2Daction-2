#pragma once
struct Player;
struct Boss;
class Timer;

class GameClear
{
private:
    bool Clear;
    bool AnimationEnd;
    int Graph;
    float StopTimer;

public:

    void Init();

    void Progress(Player& player,Boss& boss,Map& map,
        float deltaTime,Timer* time,int fontHandle1,
        int fontHandle3);

    void DrawDeadBoss(Boss& boss);

    bool GetAnimationEnd() { return AnimationEnd; }

    int GetStopTimer() { return StopTimer; }

};









