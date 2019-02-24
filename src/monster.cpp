#include "monster.h"


void monster::draw() //Draws a monster
{
    std::string path = "Monsters/" + getName() + ".txt"; //Gets file path from child
    std::ifstream file;                 //Creates file stream
    file.open(path);    //opens file
    if(file)
    {
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                file >> drawing[i][j];  //Draws the monster
            }
        }
    }
    file.close();                       //Closes file
    for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                std::cout << drawing[i][j] << " ";  //Draws the drawing from the array
            }
            std::cout << std::endl; //New line
        }

}
void monster::printStats()
{
    std::cout   << getName() << ": "    //Prints enemy name
                << "Level: " << getLevel() << " -~- "   //^ enemy level
                << "Health: " << getHealth() << "/" << getMaxHealth() //^^ Health
                << std::endl;
    std::cout << "~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-" << std::endl;
}

/*
    TO DO: CHANCE WITH LEVEL GAP ***
*/

int monster::attack(int userLevel, int userHealth)
{
    /*int chance = getLevel() - userLevel; //works out gap of level //THIS ***
    if(chance <= 0)
    {
        chance = 1;
    }
    */
    int hit;
    Random rand;
    hit = rand.num(0, getDamage());
    std::cout << "The enemy tries to attack you, ";
    if(damage >= 1)
    {
        std::cout << "and hits! Dealing " << hit << " damage." << std::endl;
    }
    else std::cout << "and misses." << std::endl;
    return hit;
}

int monster::checkIfDead(bool &battling)
{
    if(health <= 0 )
    {
        gap(30);
        std::cout << "Enemy slain! You gain " << getExp() << " experience points!" << std::endl;
        std::cout << "Enter anything to continue." << std::endl;
        std::string input = " ";
        std::cin >> input;
        battling = false;
        return getExp();
    }
    battling = true;
    return 0;
}


std::string monster::getName() const
{
    return name;
}

int monster::getHealth() const
{
    return health;
}
void monster::setHealth(int h)
{
    health = h;
}

int monster::getMaxHealth() const
{
    return maxHealth;
}

int monster::getLevel() const
{
    return level;
}

int monster::getDamage() const
{
    return damage;
}

int monster::getExp() const
{
    return expGive;
}


void monster::gap(int x)
{
    for (int i = 0; i < x; i++)
    {
        std::cout << std::endl;
    }
     std::cout << "~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-" << std::endl;
}



monster::monster()
{

}

monster::~monster()
{
    //dtor
}
