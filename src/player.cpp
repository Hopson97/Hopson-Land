#include "player.h"

std::string name;

using namespace std;


player::player(std::string namex, int X, int Y)
{
    weapon = "Bronze knife";
    maxDamage = 0;

    name = namex;

    playerX = X;
    playerY = Y;

    mapX = 0;
    mapY = 0;

    maxHealth = 10;
    health = maxHealth;

    level = 1;
    currExp = 0;
    totalExp = 0;
    expNeeded = 10;
}

player::~player()
{

}

void player::weaponHandler()
{
    if (weapon == " ")
    {
        setWeapon("Bronze knife");
        setMaxDamage(2);
    }
    else if(weapon == "Bronze knife")
    {
        setMaxDamage(2);
    }
}

void player::levelUp()
{
    if(level > 5)
    {
        setMaxHealth(level*2.2);
        setHealth(maxHealth);
        health = maxHealth;
    }
}

void player::handleStats()
{
    weaponHandler();
    if(level > 5)
    {
        maxHealth = level * 2.5;
    }

    if(getHealth() <= 0)
    {
        //death
    }
    else if(getHealth() > getMaxHealth())
    {
        health = maxHealth;
    }

    if(getCurrExp() > getExpNeeded())
    {
        while(getCurrExp() > getExpNeeded())
        {
        int overflow = getCurrExp() - getExpNeeded();
        setLevel(getLevel() + 1);
        setCurrExp(0);
        if(overflow > 0) setCurrExp(overflow);
        setExpNeeded(getExpNeeded() + ((10 * level)*1.1));

        levelUp();
        }
    }
}

void player::saveData()
{
    string fileName = "Save Files/" + getName() + ".txt";
    ofstream save(fileName);

    save << getName() << endl;

    save << getPlayerX() << endl;
    save << getPlayerY() << endl;
    save << getMapX() << endl;
    save << getMapY() << endl;

    save << getHealth() << endl;
    save << getMaxHealth() << endl;

    save << getLevel() << endl;
    save << getCurrExp() << endl;
    save << getExpNeeded() << endl;
    save << getTotalExp() << endl;
    save << getWeapon() << endl;
}

char player::loadData()
{
    string filename = "Save Files/" + getName() + ".txt";
    ifstream save(filename);
    if(!save.is_open())
    {
        return 0;
    }
    string tempN;
    int num;

    save >> tempN;
    setName(tempN);
    tempN = " bar ";

    save >> num;
    setPlayerX(num);

    save >> num;
    setPlayerY(num);

    save >> num;
    setMapX(num);

    save >> num;
    setMapY(num);

    save >> num;
    setHealth(num);

    save >> num;
    setMaxHealth(num);

    save >> num;
    setLevel(num);

    save >> num;
    setCurrExp(num);

    save >> num;
    setExpNeeded(num);

    save >> num;
    setTotalExp(num);

    save.ignore();
    getline(save,tempN);
    setWeapon(tempN);

    cin.ignore();

    save.close();
    return 'k';
}

void player::printStats()
{
    cout    << getName()                            << ": "                         << endl
            << "Level: "        << getLevel()       << " -~- "
            << "Exp Needed: "   << getCurrExp()     << "/"      << getExpNeeded()   << " -~- "
            << "Total Exp: "    << getTotalExp()    << " -~- "                      << endl
            << "Health: "       << getHealth()      << "/"      << getMaxHealth()   << " -~- "
            << "Weapon: "       << getWeapon()      << " (" << getMaxDamage() << " damage)"
            << endl;


}

string player::move(string amap[][14], int y, int x)
{
    string tile = "";
    if(amap[getPlayerY() + y][getPlayerX() + x] == "#")
    {
        return "blocked";
    }
    else if(amap[getPlayerY() + y][getPlayerX() + x] == ">")
    {
        setMapX(getMapX() + 1);
        setPlayerX(1);
        return tile;
    }
    else if(amap[getPlayerY() + y][getPlayerX() + x] == "<")
    {
        setMapX(getMapX() - 1);
        setPlayerX(12);
        return tile;
    }
    else if(amap[getPlayerY() + y][getPlayerX() + x] == "V")
    {
        setMapY(getMapY() - 1);
        setPlayerY(1);
        return tile;
    }
    else if(amap[getPlayerY() + y][getPlayerX() + x] == "^")
    {
        setMapY(getMapY() + 1);
        setPlayerY(12);
        return tile;
    }
    else
    {
        tile = amap[getPlayerY() + y][getPlayerX() + x];
        setPlayerX(getPlayerX() + x);
        setPlayerY(getPlayerY() + y);
        return tile;
    }
}

std::string player::input(string amap[][14], float &volume) //"amap" is "a map"
{
    string output = "";
    char in;
    cout    << "Options:" << endl
            << "1. W, A, S or D to move..." << endl
            << "2. I to save..." << endl
            << "3. - to decrease the volume -~- + to increase volume"
            << endl;
    cin >> in;
    if(in == 'w' || in == 'W') //GOING UP
    {
        output = move(amap, -1, 0);
        return output;
    }
    else if(in == 's' || in == 'S')//GOING DOWN
    {
        output = move(amap, 1, 0);
        return output;
    }
    else if(in == 'a' || in == 'A') //GOING LEFT
    {
        output = move(amap, 0, -1);
        return output;
    }
    else if(in == 'd' || in == 'D') //GOING RIGHT
    {
        output = move(amap, 0, 1);
        return output;
    }
    else if(in == 'i' || in == 'I')
    {
        saveData();
        cout << "Data saved under name: " << getName();
    }
    else if(in == 'c')
    {
        int cheat = 100;
        setCurrExp(getCurrExp()+cheat);
        setTotalExp(getTotalExp()+cheat);
    }
    else if(in == '-')
    {
        if(volume > 9)
        {
           volume -= 10;
        }
    }
    else if(in == '+')
    {
        if(volume < 100)
        {
           volume += 10;
        }
    }



    return output;
}

string player::battleInput()
{
    cout    << "What will you do?" << endl
            << "[f]ight." << endl
            << "[r]un away (try)." << endl;
    string input = "k";
    do
    {
        cin >> input;
        if(input == "f" || input == "r")
        {
            break;
        }
        else
        {
            return "e";
        }
        return input;
    }while (input != "f" || input != "r");

    return input;
}
/*
    TO DO: CHANCE WITH LEVEL GAP
*/
int player::battleAttack()
{
    cout << "You attempt to hit the enemy! ";

    int damage = 0;
    Random rand;

    damage = rand.num(0,getMaxDamage());

    if(damage == 0) cout<< "But you miss" << endl;
    else cout << "You hit, dealing " << damage << " damage!" << endl;

    return damage;
}

int player::getPlayerY() const
{

    return playerY;
}
void player::setPlayerY(int y)
{
    playerY = y;
}

int player::getPlayerX() const
{
    return playerX;
}
void player::setPlayerX(int x)
{
    playerX = x;
}


std::string player::getName() const
{
    return name;
}
void player::setName(std::string n)
{
    name = n;
}

int player::getHealth() const
{
    return health;
}
void player::setHealth(int h)
{
    health = h;
}

int player::getMaxHealth() const
{
    return maxHealth;
}
void player::setMaxHealth(int h)
{
    maxHealth = h;
}

int player::getMapX() const
{
    return mapX;
}
void player::setMapX(int x)
{
    mapX = x;
}
int player::getMapY() const
{
    return mapY;
}
void player::setMapY(int y)
{
    mapY = y;
}

int player::getLevel() const
{
    return level;
}
void player::setLevel(int l)
{
    level = l;
}

int player::getCurrExp() const
{
    return currExp;
}
void player::setCurrExp(int x)
{
    currExp = x;
}

int player::getExpNeeded() const
{
    return expNeeded;
}
void player::setExpNeeded(int x)
{
    expNeeded = x;
}

int player::getTotalExp() const
{
    return totalExp;
}
void player::setTotalExp(int x)
{
    totalExp = x;
}

int player::getMaxDamage() const
{
    return maxDamage;
}
void player::setMaxDamage(int x)
{
    maxDamage = (x * level) / 1.5;
}

std::string player::getWeapon() const
{
    return weapon;
}


void player::setWeapon(std::string w)
{
    weapon = w;
}








