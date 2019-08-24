#include "../card_cons.hpp"
#include "player.hpp"

/*
#define CALC(a) this->_calc_turnin(this->_payoffs, this->_ ## a, \
    this->_num_payoffs);
#define CALC_3C this->_calc_turnin(this->_payoffs_3c, \
    this->_highest_3c, this->_num_payoffs_3c);


#include <iostream>
void Player::compose_turnin()
{
    switch(this->_strategy) {
        case Strat::ALPHA :
            this->_calc_alpha();
            break;
        case Strat::BETA  :
            this->_calc_beta();
            break;
        case Strat::GAMMA :
            this->_calc_alpha(); //..._gamma
            break;
    }
}

*/
void Player::reset()
{
//    _Nothing_Payoffs_Player::_reset();
    this->_hand.reset();
    this->_num_payoffs = 0;
    this->_num_payoffs_3c = 0;
}
