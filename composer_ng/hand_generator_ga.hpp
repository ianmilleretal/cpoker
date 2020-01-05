#ifndef _HAND_NG
#define _HAND_NG


#include "../card_cons.hpp"


//No abstraction to be found here:
class Hand_Generator_GA
{
private:
    void _initialize();
    void _update();

    Card_Flags _hand;

protected:
    int _pos[cards::NUM_CARDS_PER_HAND];

    void _next_hand();
    void _reset_hand()
        {this->_initialize();}

    Card_Flags _get_hand()
        {return this->_hand;}

public:
    Hand_Generator_GA()
        {this->_initialize();}

};


#endif
