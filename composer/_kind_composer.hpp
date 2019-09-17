#ifndef _KIND_COMPOSER_
#define _KIND_COMPOSER_


#include "../card_cons.hpp"
#include "_dubs_composer.hpp"
#include "pair_generator.hpp"


class _Kind_Composer : virtual public _Dubs_Composer
{
private:
    static const Card_Flags ORIGINAL_PAIR;
    Card_Flags _pair1;
    Card_Flags _pair2;
    Pair_Generator _generator1;
    Pair_Generator _generator2;

    void _next_rank();
    void _reset();


public:
    _Kind_Composer();

    Payoff two_pair();
};


#endif
