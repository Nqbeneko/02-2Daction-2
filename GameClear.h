#pragma once
struct Player;
struct Boss;

class GameClear
{
private:
    bool Clear;
    bool AnimationEnd;
    int Graph;
    float StopTimer;

public:

    void Init();

    void Progress(Player& player,Boss& boss,Map& map, float deltaTime);

    void DrawDeadBoss(Boss& boss);

    bool GetAnimationEnd() { return AnimationEnd; }
    int GetStopTimer() { return StopTimer; }

};









