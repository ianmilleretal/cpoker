#include "_highest_payoffs_player.hpp"
#include "../card_cons.hpp"


void _Highest_Payoffs_Player::draw(int num_cards)
{
    _Base_Player::draw(num_cards);
    this->_remaining = this->get_cards();
}


void _Highest_Payoffs_Player::_calc_turnin(
    Payoff** payoffs, Payoff* &payoff, int num_payoffs)
{
    int i = this->_find_first_payoff(payoffs, payoff, num_payoffs);
    if (!payoff) {
        payoff = this->_rank_nothing_payoff(this->_remaining);
    } else {
        this->_find_lowest_ranked(payoffs + i, payoff, num_payoffs - i - 1);
    }
    this->_remaining &= ~payoff->first;
}


int _Highest_Payoffs_Player::_find_first_payoff(
    Payoff** payoffs, Payoff* &payoff, int num_payoffs)
{
    int i=0;
    do {
        if ((payoffs[i]->first & this->_remaining) == payoffs[i]->first)
            payoff = payoffs[i];
        i++;
    } while ((!payoff) && (i < num_payoffs) );
    return i;
}


void _Highest_Payoffs_Player::_find_lowest_ranked(
    Payoff** payoffs, Payoff* &payoff, int num_payoffs)
{
    for (int i=0; i < num_payoffs; i++) {
        if (((payoffs[i]->first & this->_remaining) == payoffs[i]->first) &&
            payoffs[i]->second < payoff->second) {
            payoff = payoffs[i];
        }
    }
}
