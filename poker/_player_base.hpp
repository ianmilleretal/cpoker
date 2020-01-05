#ifndef _BASE_PLAYER
#define _BASE_PLAYER


#include "../card_cons.hpp"
#include "hand.hpp"
#include "deck.hpp"


class _Base_Player
{
protected:
    Hand _hand;
    Deck* _pdeck;


public:
    _Base_Player() :
        _hand(),
        _pdeck(nullptr) {}
    _Base_Player(Deck* pdeck) :
        _hand(),
        _pdeck(pdeck) {}


    void give();
    void draw(int num_cards = cards::NUM_CARDS_PER_HAND);

    void set_hand(Hand &hand)
        {this->_hand = hand;}
    void set_pdeck(Deck* pdeck)
        {this->_pdeck = pdeck;}

    Hand get_hand()
        {return this->_hand;}
    Deck* get_pdeck()
        {return this->_pdeck;}
    Card_Flags get_cards()
        {return this->_hand.get();}
};


#endif
