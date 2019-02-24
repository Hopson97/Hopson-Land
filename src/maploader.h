#pragma once

#include <string>
#include <iostream>
#include <fstream>

class mapLoader
{
    public:
        void loadMap(std::string mapLayout[14][14], std::string filename); //Loads map

        void drawMap(std::string mapLayout[14][14],
                            int playerX, int playeY); //Draws map


        mapLoader();
        virtual ~mapLoader();

    protected:
    private:
};
