#ifndef _TRIPS_COMPOSER_
#define _TRIPS_COMPOSER_


#include "../card_cons.hpp"
#include "_base_composer.hpp"
#include "_fullhouse_composer.hpp"


class _Trips_Composer : virtual public _Fullhouse_Composer
{
private:
    int _num_singles;

    void _next_rank();


protected:
    int _suit1;
    int _suit2;
    int _shift3;

    void _reset();


public:
    _Trips_Composer() :
        _Fullhouse_Composer(),
        _num_singles(0),
        _suit1(0),
        _suit2(0),
        _shift3 (cards::QUEEN - 1) {}

    Payoff three_of_a_kind();
};


#endif
