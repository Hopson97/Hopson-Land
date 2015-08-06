#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>

class random
{
    public:
        int num(int low, int high); //andom int between two numbers
        random();
        virtual ~random();
    protected:
    private:
};

#endif // RANDOM_H
