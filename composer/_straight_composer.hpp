#ifndef _STRAIGHT_COMPOSER
#define _STRAIGHT_COMPOSER


#include "_base_composer.hpp"


class _Straight_Composer : virtual public _Base_Composer
{
private:
    int _kind;
    bool _which;

    Card_Flags _bottom_straight();
    Card_Flags _regular_straight();


public:
    _Straight_Composer() :
        _Base_Composer(),
        _kind(cards::ACE),
        _which(false) {}

    Payoff straight();
};


#endif
