#ifndef RAT_H
#define RAT_H
#include "monster.h"

class rat : public monster
{
    public:
        rat(int player_level);  //Rats constructor deals with member variables
        virtual ~rat();
    protected:
    private:

};

#endif // RAT_H
