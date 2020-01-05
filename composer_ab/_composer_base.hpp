#ifndef _BASE_COMPOSER_
#define _BASE_COMPOSER_


#include "../card_cons.hpp"


class _Base_Composer
{
protected:
    static const Card_Flags _shift_bit;
    static const Card_Flags _shift_half;
    static const Card_Flags _shift_spade;

    int _rank;
    int _suit;
    bool _is_finished;
    Card_Flags _high_card;


public:
    _Base_Composer() : 
        _rank(0),
        _suit(0),
        _is_finished(false),
        _high_card(cards::ACE) {}

    void reset_finish();

    bool get_is_finished()
        {return this->_is_finished;}
};


#endif
