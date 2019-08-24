#include "_count_payoffs_player.hpp"


void _Count_Payoffs_Player::add_payoff(Payoff* payoff)
{
    this->_payoffs[this->_num_payoffs] = payoff;
    this->_num_payoffs++;
}


void _Count_Payoffs_Player::add_payoffs_3c(Payoff* payoffs, int size)
{
    for (int i=0; i < size; i++) {
        if (
        (this->get_cards() & payoffs[i].first) == payoffs[i].first)
        {
            this->_payoffs_3c[this->_num_payoffs_3c] = &payoffs[i];
            this->_num_payoffs_3c++;
        }
    }
}


void _Count_Payoffs_Player::give()
{
    _Base_Player::give();
    this->_num_payoffs = 0;
    this->_num_payoffs_3c = 0;
}
