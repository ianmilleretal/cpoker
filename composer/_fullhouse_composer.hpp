#ifndef _FULLHOUSE_COMPOSER_
#define _FULLHOUSE_COMPOSER_


#include "../card_cons.hpp"
#include "_base_composer.hpp"


class _Fullhouse_Composer : virtual public _Base_Composer
{
private:
    int _num_doubles;
    int _num_triples;
    int _sequence2;
    int _sequence3;
    int _trip_kind;

    void _next_rank();


protected:
    int _shift1;
    int _shift2;

    Card_Flags _generate_double();
    Card_Flags _generate_triple(int repeats);
    void _reset_generators();


public:
    _Fullhouse_Composer() : 
        _Base_Composer(),
        _num_doubles(0),
        _num_triples(0),
        _shift1(cards::ACE - 1),
        _shift2(cards::KING - 1),
        _sequence2(0),
        _sequence3(0),
        _trip_kind(0) {}

    Payoff full_house();
};


#endif
