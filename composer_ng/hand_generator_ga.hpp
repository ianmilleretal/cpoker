#ifndef _HAND_NG
#define _HAND_NG


#include "../card_cons.hpp"


//No abstraction to be found here:
class Hand_Generator_GA
{
private:
    void _initialize();
    void _update();
    void _drop();

    Card_Flags _hand;

protected:
    int _pos[cards::NUM_CARDS_PER_GAMMA];
    int _cap[cards::NUM_CARDS_PER_GAMMA];

    void _next_hand();
    void _reset_hand()
        {this->_initialize();}


public:

    Card_Flags _get_hand()
        {
            this->_next_hand();
            this->_update();
            return this->_hand;
        }

    Hand_Generator_GA()
        {this->_initialize();}

};


#endif
