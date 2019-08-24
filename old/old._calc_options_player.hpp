#ifndef _CALC_OPTIONS_PLAYER
#define _CALC_OPTIONS_PLAYER


#include "../card_cons.hpp"
#include "_count_payoffs_player.hpp"
#include "_backup_payoffs_player.hpp"
#include "_nothing_payoffs_player.hpp"
#include "deck.hpp"


class _Calc_Options_Player :
    public _Backup_Payoffs_Player,
    public _Nothing_Payoffs_Player
{
private:
    int _count_alphas();
    void _remaining_to_gamma();
    Payoff* _find_alpha(Payoff* beta, int end);
    Payoff* _find_beta(Payoff* alpha, int start);


protected:
    Payoff* _alpha;
    Payoff* _beta;
    Payoff* _gamma;
    Card_Flags _remaining;

    void _calc_alpha();
    void _calc_beta();
    void _calc_gamma();


public:
    _Calc_Options_Player() :
        _Backup_Payoffs_Player(),
        _Nothing_Payoffs_Player(),
        _alpha(nullptr),
        _beta(nullptr),
        _gamma(nullptr) {}

    _Calc_Options_Player(Deck* pdeck) :
        _Backup_Payoffs_Player(pdeck),
        _Nothing_Payoffs_Player(),
        _alpha(nullptr),
        _beta(nullptr),
        _gamma(nullptr) {}

    void draw(int num_cards = cards::NUM_CARDS_PER_HAND);
};


#endif
