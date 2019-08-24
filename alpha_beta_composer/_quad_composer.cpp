#include "_quad_composer.hpp"


Payoff _Quad_Composer::four_of_a_kind()
{
    if (this->_shift == this->_extra)
        this->_extra--;
    Card_Flags compose = this->_shift_half << 
        this->_shift * cards::NUM_SUITS;
    Card_Flags extra_c = this->_shift_spade << 
        this->_extra * cards::NUM_SUITS;
    compose |= extra_c >> this->_suit;
    this->_suit++;
    Payoff result(compose, this->_rank, cards::FOUR_OF_A_KIND);

    if (this->_suit == cards::NUM_SUITS) {
        this->_suit = 0;
        this->_rank++;
        if (this->_shift < cards::TWO && this->_extra < cards::THREE){
            this->_is_finished = true;
        } else if (this->_extra < cards::TWO){
            this->_shift--;
            this->_extra = cards::ACE - 1;
        } else  {
            this->_extra--;
        }
    }
    return result;
}
