#include "_player_count_payoffs.hpp"


void _Count_Payoffs_Player::add_payoff_ab(Payoff* payoff)
{
    if (payoff->third == cards::NOTHING) {
        this->_nothing[this->_num_nothing] = payoff;
        this->_num_nothing++;
    } else {
        this->_payoffs_ab[this->_num_payoffs_ab] = payoff;
        this->_num_payoffs_ab++;
    }
}


void _Count_Payoffs_Player::add_payoffs_ga(Payoff* payoffs, int size)
{
    for (int i=0; i < size; i++) {
        if (
        (this->get_cards() & payoffs[i].first) == payoffs[i].first)
        {
            this->_payoffs_ga[this->_num_payoffs_ga] = &payoffs[i];
            this->_num_payoffs_ga++;
        }
    }
}


void _Count_Payoffs_Player::give()
{
    _Base_Player::give();
    this->_num_payoffs_ab = 0;
    this->_num_payoffs_ga = 0;
}
