#pragma once

struct Player;
struct Boss;

class Start
{
private:

    bool PlayerSet;
    bool BossSet;

public:
    bool StartFlag;

    void Init();

    void Progress(Player& player,Boss& boss,Map &map);

    void AnimationPlayer(Player& player);

};