#include "_trips_composer.hpp"
#include <iostream>


#define FINISH_CONDITION this->_shift2 == cards::THREE - 1 && \
                         this->_shift1 == cards::TWO - 1


static void decrement_past(int &target, int &past);


Payoff _Trips_Composer::three_of_a_kind()
{
    const Card_Flags spade = this->_shift_spade;
    Card_Flags cards = this->_generate_triple(
        cards::NUM_SUITS * cards::NUM_SUITS) << 
        this->_shift1 * cards::NUM_SUITS;
    cards |= spade >> this->_suit2 << this->_shift2*cards::NUM_SUITS;
    cards |= spade >> this->_suit1 << this->_shift3*cards::NUM_SUITS;
    Payoff result(cards, this->_rank, cards::THREE_OF_A_KIND);

    this->_suit1++;
    if (this->_suit1 == cards::NUM_SUITS) {
        this->_suit1 = 0;
        this->_suit2++;
        if (this->_suit2 == cards::NUM_SUITS) {
            this->_suit2 = 0;
            this->_next_rank();
        }
    }
    return result;
}


void _Trips_Composer::_next_rank()
{
    this->_num_singles++;
    if (this->_num_singles == cards::COMBO_TRIPS) {
        this->_rank++;
        this->_num_singles = 0;
        decrement_past(this->_shift3, this->_shift1);
        if (this->_shift3 < cards::TWO - 1) {
            decrement_past(this->_shift2, this->_shift1);
            if (this->_shift2 == cards::TWO - 1) {
                this->_shift1--;
                this->_shift2 = cards::ACE - 1;
            } 
            if (FINISH_CONDITION) {
                this->_is_finished = true;
            }
            this->_shift3 = this->_shift2;
            decrement_past(this->_shift3, this->_shift1);
        }
    }
    if (this->_is_finished) this->_reset();
}


void _Trips_Composer::_reset()
{
    this->_reset_generators();
    this->_suit1 = 0;
    this->_suit2 = 0;
    this->_shift3 = cards::QUEEN - 1;
    this->_shift2 = cards::KING - 1;;
    this->_shift1 = cards::ACE - 1;;
}


void decrement_past(int &target, int &past)
{
    target--;
    if (target == past) target--;
}


#undef FINISH_CONDITION
