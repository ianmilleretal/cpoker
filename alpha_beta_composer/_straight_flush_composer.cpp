#include "_straight_flush_composer.hpp"


Payoff _Straight_Flush_Composer::straight_flush()
{
    Card_Flags cards = 0;
    for (int i=0; i < cards::NUM_CARDS_PAYOFF_1; i++) {
        int shift = ((this->_high_card-i) * cards::NUM_SUITS)-1;
        if (shift >= 0)
            cards |= this->_shift_bit << shift;
    }

    cards >>= this->_suit;
    if ( (this->_high_card == cards::FIVE)) {
        Card_Flags ace = this->_shift_spade >> this->_suit;
        cards |= ace << ((cards::ACE - 1) * cards::NUM_SUITS);
    }

    Payoff result(cards, this->_rank, cards::STRAIGHT_FLUSH);
    if ((++this->_suit) == 4) {
        this->_rank++;
        this->_high_card--;
        this->_suit = 0;
    }
    if (this->_high_card == cards::FOUR) this->_is_finished = true;

    return result;
}
