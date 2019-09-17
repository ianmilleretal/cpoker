#ifndef _PAIR_GENERATOR_
#define _PAIR_GENERATOR_


#include "../card_cons.hpp"


class Pair_Generator
{
private:
    int _sequence;


public:
    Pair_Generator() : 
        _sequence(0) {}

    Card_Flags next();

    void reset()
        {this->_sequence  = 0;}
};


#endif
