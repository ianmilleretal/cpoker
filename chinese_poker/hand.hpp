#ifndef HAND_
#define HAND_


#include "../card_cons.hpp"
#include <cstdint>


class Hand
{
protected:
    Card_Flags _cards;
    Short_U    _count;


public:
    Hand() : 
        _cards(0),
        _count(0) {}
    Hand(bool is_full) : 
        _cards(0 - is_full),
        _count(cards::NUM_CARDS_PER_DECK * is_full) {}

    void set(Card_Flags cards)
        {this->_cards = cards;}
    void reset()
        {this->_cards = 0; this->_count = 0;}
    void increment_count(Short_U num)
        {this->_count += num;}

    Card_Flags get()
        {return this->_cards;}
    Short_U count()
        {return this->_count;}
};


#endif
