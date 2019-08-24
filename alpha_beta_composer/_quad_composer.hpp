#ifndef _QUAD_COMPOSER_
#define _QUAD_COMPOSER_


#include "../card_cons.hpp"
#include "_base_composer.hpp"


class _Quad_Composer : virtual public _Base_Composer
{
private:
    int _shift;
    int _extra;


public:
    _Quad_Composer() : 
        _Base_Composer(),
        _shift(cards::ACE-1),
        _extra(cards::KING-1) {}

    Payoff four_of_a_kind();
};


#endif
