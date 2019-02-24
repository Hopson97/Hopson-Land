#pragma once


#include <string>
#include <iostream>
#include <fstream>

#include "random.h"


class monster
{
    public:
        monster();
        virtual ~monster();

        int checkIfDead(bool &battling);    //Checks if health < 0

        void draw();    //Draws the monster

        void printStats();  //Prints monsters statistics

        int attack(int userLevel, int userHealth);  //For when monster attacks

        /*
            LOTS OF GETTERS AND SETTERS
        */
        std::string getName() const;

        int getHealth() const;
        void setHealth(int h);

        int getMaxHealth() const;

        int getLevel() const;

        int getDamage() const;

        int getExp() const;

        /*
            LOTS OF GETTERS AND SETTERS [end]
        */

    protected:
        std::string name;   //Name of the monster ie it's species (rat, bat ETC.)
        int health;         //Health
        int maxHealth;      //Maximum health
        int level;          //Level of the enemy, scales slightly with players level in constructors
        int damage;         //Maximum damage the monster can deal
        int expGive;        //The amount of xp that will be given
        std::string drawing[10][15];    //Array for the drawing
    private:
        void gap(int x);    //Just a bit of fancy UI stuff

};