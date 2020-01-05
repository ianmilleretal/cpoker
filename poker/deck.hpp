#ifndef DECK_
#define DECK_


#include "hand.hpp"
#include "../card_cons.hpp"
#include <random>


class Deck : public Hand
{
protected:
    std::mt19937 _generator;


public:
    Deck() :
        Hand(true),
         _generator() {}

    void deal(Hand &hand);
    void reset();
    void seed(Short_U seed)
        {this->_generator.seed(seed);}

    std::mt19937& generator()
        {return this->_generator;}
};


#endif
