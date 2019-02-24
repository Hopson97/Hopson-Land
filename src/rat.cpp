#include "rat.h"

rat::rat(int player_level)
{
    name = "Rat";
    health = 2 * player_level;
    maxHealth = health;
    level = health / 10;
    if(level < 1)
    {
        level = 1;
    }

    damage = level * 1.5;
    expGive = level * 2;
}

rat::~rat()
{
    //dtor
}
