#include "maploader.h"


void mapLoader::loadMap(std::string mapLayout[14][14], std::string filename) //Loads map into an array
{
    std::ifstream file; //Creates a stream for inputting files into the code
    file.open(filename);    //Opens the file
    if(file)                //If file is open = true
    {
        for(int i = 0; i < 14; i++)
        {
            for(int j = 0; j < 14; j++)
            {
                file >> mapLayout[i][j];    //Add file to array
            }
        }
    }
}

void mapLoader::drawMap(std::string mapLayout[14][14],
                        int playerX, int playerY) //For drawing player
{
    for(int i = 0; i < 14; i++)
    {
        for(int j = 0; j < 14; j++)
        {
            if(i == playerY && j == playerX) //Checks if it is checking
            {                               //same location player is in
                if(mapLayout[i][j] == "#");
                else
                {
                mapLayout[i][j] = "@"; //Changes it to @
                }
            }
            std::cout << mapLayout[i][j] << " "; //Draws what would usually be
        }
        std::cout << std::endl;
    }
}

mapLoader::mapLoader()
{
    //ctor
}

mapLoader::~mapLoader()
{
    //dtor
}
