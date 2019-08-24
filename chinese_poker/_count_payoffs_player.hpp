#ifndef _COUNT_PAYOFFS_PLAYER
#define _COUNT_PAYOFFS_PLAYER


#include "../card_cons.hpp"
#include "_base_player.hpp"


class _Count_Payoffs_Player : public _Base_Player
{
protected:
    static const int BINOMIAL_13_5 = 1287;
    static const int BINOMIAL_13_3 = 3796;

    Payoff* _payoffs[BINOMIAL_13_5];
    Payoff* _payoffs_3c[BINOMIAL_13_3];
    int _num_payoffs;
    int _num_payoffs_3c;


public:
    _Count_Payoffs_Player() :
        _Base_Player(),
        _num_payoffs(0),
        _num_payoffs_3c(0) {}
    _Count_Payoffs_Player(Deck* pdeck) :
        _Base_Player(pdeck),
        _num_payoffs(0),
        _num_payoffs_3c(0) {}

    void give();
    void add_payoff(Payoff* payoff);
    void add_payoffs_3c(Payoff* payoffs, const int size);

    Payoff** get_payoffs()
        {return this->_payoffs;}
    Payoff** get_payoffs_3c()
        {return this->_payoffs_3c;}
    int get_num_payoffs()
        {return this->_num_payoffs;}
    int get_num_payoffs_3c()
        {return this->_num_payoffs_3c;}
};


#endif
