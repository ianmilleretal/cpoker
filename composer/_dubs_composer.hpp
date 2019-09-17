#ifndef _DUBS_COMPOSER_
#define _DUBS_COMPOSER_


#include "../card_cons.hpp"
#include "_trips_composer.hpp"


class _Dubs_Composer : virtual public _Trips_Composer
{
private:
    Card_Flags _pair;
    int _shift4;
    int _which_pair;

    void _next_rank();
    void _check_finished();


protected:
    int _suit3;

    void _reset();


public:
    _Dubs_Composer();

    Payoff two_of_a_kind();
};


#endif
