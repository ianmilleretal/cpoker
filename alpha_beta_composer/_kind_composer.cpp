#include "_kind_composer.hpp"
#include <iostream>


const Card_Flags _Kind_Composer::ORIGINAL_PAIR = 0x0C; //1100


static void decrement_past(int &target, int &past1, int &past2);



_Kind_Composer::_Kind_Composer() :
        _Dubs_Composer(),
        _generator1(),
        _generator2()
{
        this->_pair1 = this->_generator1.next();
        this->_pair2 = this->_generator2.next();
}


Payoff _Kind_Composer::two_pair()
{
    Card_Flags cards = this->_shift_spade >> this->_suit1;
    cards <<= this->_shift3 * cards::NUM_SUITS;
    cards |= this->_pair2 << (this->_shift2 * cards::NUM_SUITS);
    cards |= this->_pair1 << (this->_shift1 * cards::NUM_SUITS);

    this->_suit1++;
    if (this->_suit1 == cards::NUM_SUITS) {
        this->_suit1 = 0;
        this->_pair2 = this->_generator2.next();
        if (this->_pair2 == ORIGINAL_PAIR) {
            this->_pair1 = this->_generator1.next();
            if(this->_pair1 == ORIGINAL_PAIR)
                this->_next_rank();
        }
    }
    return Payoff(cards, this->_rank, cards::TWO_PAIR);
}


void _Kind_Composer::_next_rank()
{
    decrement_past(this->_shift3, this->_shift1, this->_shift2);
    if (this->_shift3 < cards::TWO - 1) {
        this->_shift2--;
        if (this->_shift2 < cards::TWO - 1) {
            this->_shift1--;
            this->_shift2 = this->_shift1 - 1;
            if (this->_shift1 == cards::TWO - 1)
                this->_is_finished = true;
        }
        this->_shift3 = cards::ACE;
        decrement_past(this->_shift3, this->_shift1, this->_shift2);
    }
    if (this->_is_finished) this->_reset();
}


void _Kind_Composer::_reset()
{
    this->_generator1.reset();
    this->_generator1.reset();
    _Dubs_Composer::_reset();
}


void decrement_past(int &target, int &past1, int &past2)
{
    target--;
    if (target == past1 || target == past2)
        target--;
    if (target == past1 || target == past2)
        target--;
}
