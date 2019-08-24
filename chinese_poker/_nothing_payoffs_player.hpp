#ifndef _NOTHING_PAYOFFS_PLAYER
#define _NOTHING_PAYOFFS_PLAYER


#include "../card_cons.hpp"


class _Nothing_Payoffs_Player
{
private:
    Payoff _one;
    Payoff _two;


protected:
    Payoff* _rank_nothing_payoff(const Card_Flags &cards);
    Payoff* _create_nothing_payoff(const Card_Flags &cards);
    void _reset();


public:
    _Nothing_Payoffs_Player() :
        _one(cards::SENTINEL, cards::SENTINEL, cards::SENTINEL),
        _two(cards::SENTINEL, cards::SENTINEL, cards::SENTINEL) {}
};


#endif
