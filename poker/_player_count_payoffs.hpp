#ifndef _COUNT_PAYOFFS_PLAYER
#define _COUNT_PAYOFFS_PLAYER


#include "../card_cons.hpp"
#include "_player_base.hpp"


class _Count_Payoffs_Player : public _Base_Player
{
protected:
    static const int BINOMIAL_13_5 = 1287;
    static const int BINOMIAL_13_3 = 3796;

    Payoff* _payoffs_ab[BINOMIAL_13_5];
    Payoff* _payoffs_ga[BINOMIAL_13_3];
    Payoff* _nothing[BINOMIAL_13_5];

    int _num_payoffs_ab;
    int _num_payoffs_ga;
    int _num_nothing;


public:
    _Count_Payoffs_Player() :
        _Base_Player(),
        _num_payoffs_ab(0),
        _num_payoffs_ga(0),
        _num_nothing(0) {}

    _Count_Payoffs_Player(Deck* pdeck) :
        _Base_Player(pdeck),
        _num_payoffs_ab(0),
        _num_payoffs_ga(0),
        _num_nothing(0) {}

    void give();
    void add_payoff_ab(Payoff* payoff);
    void add_payoffs_ga(Payoff* payoffs, const int size);

    Payoff** get_payoffs_ab()
        {return this->_payoffs_ab;}
    Payoff** get_payoffs_ga()
        {return this->_payoffs_ga;}
    Payoff** get_nothing()
        {return this->_nothing;}
    int get_num_payoffs_ab()
        {return this->_num_payoffs_ab;}
    int get_num_payoffs_ga()
        {return this->_num_payoffs_ga;}
    int get_num_nothing()
        {return this->_num_nothing;}
};


#endif
