#ifndef _SF_COMPOSER_
#define _SF_COMPOSER_


#include "../card_cons.hpp"
#include "_base_composer.hpp"


class _Straight_Flush_Composer : virtual public _Base_Composer
{
public:
    _Straight_Flush_Composer() : _Base_Composer() {}

    Payoff straight_flush(); //Include Royal Flush
};


#endif
