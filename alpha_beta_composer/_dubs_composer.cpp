#include "_dubs_composer.hpp"
#include "../card_cons.hpp"
#include <iostream>
#include <bitset>


static void decrement_past(int &target, int &pass);


_Dubs_Composer::_Dubs_Composer() :
        _Trips_Composer(),
        _shift4(cards::JACK - 1),
        _which_pair(0),
        _suit3(0) 
{
        this->_pair = this->_generate_double();
}


Payoff _Dubs_Composer::two_of_a_kind()
{
    const Card_Flags spade = this->_shift_spade;
    Card_Flags cards = this->_pair << this->_shift1*cards::NUM_SUITS;
    cards |= spade >> this->_suit1 << this->_shift2*cards::NUM_SUITS;
    cards |= spade >> this->_suit2 << this->_shift3*cards::NUM_SUITS;
    cards |= spade >> this->_suit3 << this->_shift4*cards::NUM_SUITS;

    this->_suit3++;
    if (this->_suit3 == cards::NUM_SUITS) {
        this->_suit3 = 0;
        this->_suit2++;
        if (this->_suit2 == cards::NUM_SUITS) {
            this->_suit2 = 0;
            this->_suit1++;
            if (this->_suit1 == cards::NUM_SUITS) {
                this->_suit1 = 0;
                this->_pair = this->_generate_double();
                this->_which_pair++;
                if (this->_which_pair == cards::COMBO_DUBS)
                    this->_next_rank();
            }
        }
    }
    return Payoff(cards, this->_rank, cards::PAIR);
}


void _Dubs_Composer::_next_rank()
{
    this->_which_pair = 0;
    this->_rank++;
    decrement_past(this->_shift4, this->_shift1);
    if (this->_shift4 < cards::TWO - 1) {
        decrement_past(this->_shift3, this->_shift1);
        if (this->_shift3 < cards::THREE - 1 || 
            (this->_shift3 == cards::THREE - 1 && (this->_shift1 < cards::FOUR - 1))) {
            decrement_past(this->_shift2, this->_shift1);
            if (this->_shift2 < cards::FOUR - 1 || 
                (this->_shift2 == cards::FOUR - 1 && (this->_shift1 < cards::FIVE - 1))) {
                this->_shift1--;
                this->_shift2 = cards::ACE - 1;
            }
            this->_shift3 = this->_shift2;
            decrement_past(this->_shift3, this->_shift1);
        }
        this->_shift4 = this->_shift3;
        decrement_past(this->_shift4, this->_shift1);
    }
    this->_check_finished();
}


void _Dubs_Composer::_check_finished()
{
    this->_is_finished = this->_shift1 < cards::TWO - 1;
    if (this->_is_finished) this->_reset();
}


void _Dubs_Composer::_reset()
{
    _Trips_Composer::_reset();
    this->_suit3 = 0;
}


void decrement_past(int &target, int &pass)
{
    target--;
    if (target == pass)
        target--;
}
