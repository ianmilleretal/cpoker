#ifndef _HIGHEST_PLAYER
#define _HIGHEST_PLAYER


#include "../card_cons.hpp"
#include "_count_payoffs_player.hpp"
#include "_nothing_payoffs_player.hpp"
#include "deck.hpp"


class _Highest_Payoffs_Player :
    virtual public _Count_Payoffs_Player,
    public _Nothing_Payoffs_Player
{
private:
    int _find_first_payoff(
        Payoff** payoffs, Payoff* &payoff, int num_payoffs);
    void _find_lowest_ranked(
        Payoff** payoffs, Payoff* &payoff, int num_payoffs);


protected:
    Payoff* _highest;
    Payoff* _nextest;
    Payoff* _highest_3c;
    Card_Flags _remaining;

    void _calc_turnin(
        Payoff** payoffs, Payoff* &payoff, int num_payoffs);


public:
    _Highest_Payoffs_Player() :
        _Count_Payoffs_Player(),
        _Nothing_Payoffs_Player(),
        _highest(nullptr),
        _nextest(nullptr),
        _highest_3c(nullptr) {}
    _Highest_Payoffs_Player(Deck* pdeck) :
        _Count_Payoffs_Player(pdeck),
        _Nothing_Payoffs_Player(),
        _highest(nullptr),
        _nextest(nullptr),
        _highest_3c(nullptr) {}

    void draw(int num_cards = cards::NUM_CARDS_PER_HAND);
};


#endif
