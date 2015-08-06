#include "player.h"

#include "maploader.h"

#include "monsterIncludes.h"

#include <sstream>

#include <ctime>
#include <cstdlib>

#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;

void makeGap(int x) //Creates a gap/ "clears" the screen
{
    for (int i = 0; i < x; i++)
    {
        cout << endl;
    }
}

void makeLine() //Creates a pretty line
{
    cout << "~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-" << endl;
}

void drawGapAndLine() //I wonder what this does?
{
    makeGap(7);
    makeLine();
}
string askForName() //Split function, returns players name for the game
{

    string name;                            //Creates name string
    cout << "What is your name?" << endl;   //Asks user what their name is
    cin >> name;                            //User enters their name

    return name;                            //returns name to call
}
void initLoop(player user) //Initiates the main loop
{
    cout    << "Hello, " << user.getName() << endl; //Says hello to the user by name
    makeGap(2);
    makeLine();
}

bool checkInputReturn(string tile, player &user) //Checks if  what the player is standing on is
{                  // able to be interacted with.
    random rand;
    int randomN;    //Creates random
    if(tile == ",") //Checks if tile stood on is long grass
    {
        randomN = rand.num(1,5); //Random number, 1 to 5
        if( randomN == 1)       //Lucky number 1...
        {
            return true;        //Returns true, meaning might be encounter
        }
        else
        {
            return false;       //If "unlucky" no encounter will happen
        }
    }
    else
    {
        return false;           //Because warnings
    }

}

string getFileName(player user) //Gets file name based on where the players map location is
{
    string mapX;     //Determines X (left) side of file name
    string mapY;     //Determines Y (right) side of file name
    ostringstream x;        //Creates stream able to convert integer into string
    ostringstream y;        //Creates stream able to convert integer into string
    x << user.getMapX();    //Turns the map x of player into string
    mapX = x.str();         //Defines the X string
    y << user.getMapY();    //Turns the map x of player into string
    mapY = y.str();         //Defines the Y string

    return "Maps/Map " + mapX + " " + mapY + ".txt"; //Creates and returns exact file name

}
monster determineMonster(int userLevel) //(enc) Randomly chooses a monster to be spawned.
{
    random rand;
    int monsterN = rand.num(1,1); //Chooses a number to represent a random number
    if (monsterN == 1) //Rat has been chosen
    {
        rat aRat(userLevel);
        return aRat;
    }
    else{   //Because rats are common
        rat aRat(userLevel);
        return aRat;
    }
}
bool tryEscape(int enemyLevel, int playerLvl)   //For when the player wants to try escape
{
    int escape;
    int escapeGap = enemyLevel - playerLvl; //Determines gap of levels

    if(escapeGap <= 2 ) //If the gap is too small of in the negatives, it becomes 2
    {
        escapeGap = 2;
    }
    random rand;
    escape = rand.num(1,escapeGap); //Decides whether the player has escaped

    if(escape == 1) //Lucky number is one! if this happens, the escape has been successful
    {
        return true;
    }
    else
    {
        cout << "Escape failed! " << endl;
        return false;
    }
}
void introduceAttack()
{
    drawGapAndLine();
    cout << "Uh oh! You have run into an enemy! Prepare for battle!" << endl;

    cout << "Enter to continue" << endl;
    cin.clear();
    cin.ignore();

    string cont;
    getline(cin, cont);
}
bool battle(player &user, monster enemy, bool battling, float volume) //Loop for an encounter
{
    /*  sf::Music goldDust;         //Load up "battle music"
        if(!goldDust.openFromFile("Music/GoldDust.ogg"));   //Load up "battle music" file
        goldDust.setVolume(volume);
        goldDust.play();    //Play the battle music
    */
    void introduceAttack();
    string input = "k"; //Input string - Not char so they cannot type in multiple letters for ease
    drawGapAndLine();
    while(battling)
    {
        user.handleStats();
        user.printStats();      //Shows current user statistics
        cout << "-~-" << endl;  //Pretty line :3
        enemy.printStats();     //Enemy statistic
        enemy.draw();           //Draw the enemy from file
        input = user.battleInput(); //Player does input
        if(input == "r")
        {
            drawGapAndLine();
            battling = tryEscape(enemy.getLevel(),
                                 user.getLevel());//If the player tires to run, roll a die.
        }
        else if(input == "f") //If the player tries to attack, attack!
        {
            drawGapAndLine();

            enemy.setHealth(enemy.getHealth()
                            -user.battleAttack()); //Players attack

        }
        else if (input == "e")
        {
            drawGapAndLine();
            cerr << "Invalid input. Type in \"f\" or \"r\" "<< endl; //If the input is not a correct one, nothing happens
        }
        else return false;//Error catcher

        user.setCurrExp(user.getCurrExp()
                        +enemy.checkIfDead(battling)); //Checks if enemy is dead, (enemy.checkIfDad() has exp change logic too
        if(!battling)
        {
            user.setTotalExp(user.getTotalExp()
            + enemy.getExp()); //For changing total xp
        }
        if(input != "e")
        {
        user.setHealth(user.getHealth()
                       -enemy.attack(user.getLevel(),
                                     user.getHealth())); //Enemy attack
        makeLine();
        }
    }
    return false;
}

void drawStatsAndMap(player user, mapLoader mapLoad, string theMap[][14], string mapFile) //Split function
{                           //Basically draws the what the user sees when roaming
    mapFile = getFileName(user);    //Gets file name
    user.printStats();  //Print user statistics
    mapLoad.loadMap(theMap, mapFile);   //Load the map
    mapLoad.drawMap(theMap, user.getPlayerX(),user.getPlayerY()); //Draw the map
}

void mainGameLoop(mapLoader mapLoad, player user) //The main game loop I guess
{
    float volume = 100;

    sf::Music sonata;   //Load roaming
    if(!sonata.openFromFile("Music/Sonata.ogg")); //Load roaming file
    sonata.play();  //Play roaming file

    string theMap[14][14]; //Map array
    string input = " "; //String for input stuff
    string mapFile; //String for file name
    bool running = true;    //Boolean to check if "program is running"
    bool encounter = false; //Boolean to check if an encounter is currently happening
    monster enemy;  //This will turn into a child class of this parent
    while(running)  //While program is running...
    {
        sonata.setVolume(volume); //sets volume of music

        if(!encounter)  //If no encounter is happening
        {
            user.handleStats();
            drawGapAndLine();
            drawStatsAndMap(user, mapLoad, theMap,mapFile); //Basically a split function, commented about above
            input = user.input(theMap, volume); //Checks input
            encounter = checkInputReturn(input, user);  //Checks input (only if it was movement tbf
        }
        else if(encounter)  //But if an encounter is happening
        {
            sonata.stop();  //Stop the music
            drawGapAndLine();
            enemy = determineMonster(user.getLevel()); //Determines a potential monster
            encounter = battle(user, enemy, encounter, volume); //Only returns when the battle is over
            sonata.play();  //When it over, resume the music
        }
    }
}

int main() //Main function
{


    srand(time(NULL));  //Prepares the game for anything that needs random numbers
    mapLoader mapLoad;  //Prepares object for loading map
    string name;        //Prepares string for the players name.
    cout << "Welcome to Hopson Land!!!" << endl;    //OMG welcome"
    makeGap(2);
    string option = "Z";
    do
    {
        cout    << "(N)ew game, or "
                << "(L)oad game?" << endl;

        cin >> option;
        if(option == "N" || option == "n" || option == "L" || option == "l") break;
    }while(option != "N" || option != "n" || option != "L" || option != "l");

    if(option == "N")
    {
        name = askForName();        //Allows user to input their name
        player user(name, 5, 5);    //Player constructor
        mainGameLoop(mapLoad, user);    //Calls the main loop!
    }
    else if(option == "L")
    {
        cout    << "Right, what was your EXACT name when playing last?" << endl;
        string name;
        char loadStatus;
        do
        {

            cin     >> name;
            cout    << "Loading data..." << endl;
            player user(name, 0, 0);

            loadStatus = user.loadData();   //Checks if file exists and loads data
            if(loadStatus == 0) //If file does not exist, try again...
            {
                cerr << "File not exist. Try again. Did you do correct capitalisation?" << endl;
                continue;
            }
            else
            {

                mainGameLoop(mapLoad, user); //Initiate loop
            }
        }while(loadStatus != '1');  //While a file has not been loaded
    }
    return 0;
}






















