#ifndef PLAYER_H
#define PLAYER_H
#include "random.h"
#include <string>
#include <iostream>
#include <fstream>

class player
{
    public:
        player(std::string namex, int X, int Y);
        virtual ~player();

        void handleStats(); //Checks to see if health is 0, or level up needed ETC.

        char loadData();    //Loading player data

        void printStats();  //Prints all data to UI

        void weaponHandler();   //Checks weapon

        std::string input(std::string amap[][14], float &volume); //Roaming input

        std::string battleInput();  //Input for when in battle
        int battleAttack();         //For when the user chooses to fight

        std::string getName() const; //returns player name
        void setName(std::string n);

        /*
            LOTS OF GETTERS AND SETTERS
        */

        int getPlayerY() const;
        void setPlayerY(int y);

        int getPlayerX() const;
        void setPlayerX(int x);

        int getMapX() const;
        void setMapX(int x);

        int getMapY() const;
        void setMapY(int y);

        int getHealth() const;
        void setHealth(int h);

        int getMaxHealth() const;
        void setMaxHealth(int h);

        int getLevel() const;
        void setLevel(int l);

        int getCurrExp() const;
        void setCurrExp(int x);

        int getExpNeeded() const;
        void setExpNeeded(int x);

        int getTotalExp() const;
        void setTotalExp(int x);

        int getMaxDamage() const;
        void setMaxDamage(int x);

        std::string getWeapon() const;
        void setWeapon(std::string w);

        /*
            LOTS OF GETTERS AND SETTERS [END]
        */

    protected:
    private:
        void levelUp(); //Stuff for when player levels up
        void saveData(); //Saving user data


        std::string weapon; //Current weapon

        std::string move(std::string amap[0][14], int y, int x);//Direction for movement from "roaming" input
        int playerX;    //X Co-Ordinate of player in current map
        int playerY;    //Y Co-Ordinate of player in current map

        int mapX;       //X Co-Ordinate of player in world map
        int mapY;       //Y Co-Ordinate of player in world map

        std::string name;   //Players name

        int health;         //Health
        int maxHealth;      //Players maximum health

        int level;              //Players level
        int currExp;        //Exp current
        int expNeeded;      //CurrExp needs to reach this for a level up
        int totalExp;       //Total exp

        int maxDamage;      //Maximum damage the player can deal



};

#endif // PLAYER_H
