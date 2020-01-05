#ifndef _HAND_NO
#define _HAND_NO


#include "../card_cons.hpp"


//No abstraction to be found here:
class Hand_Generator
{
private:
    void _initialize();
    void _update();
    void _drop();

    Card_Flags _hand;

protected:
    int _pos[cards::NUM_CARDS_ALPHA_BETA];
    int _cap[cards::NUM_CARDS_ALPHA_BETA];

    void _next_hand();
    void _reset_hand()
        {this->_initialize();}

    Card_Flags _get_hand()
        {return this->_hand;}

public:
    Hand_Generator()
        {this->_initialize();}

};


#endif
