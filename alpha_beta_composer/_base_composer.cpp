#include "_base_composer.hpp"


const Card_Flags _Base_Composer::_shift_bit = 1;
const Card_Flags _Base_Composer::_shift_spade = 0x08;
const Card_Flags _Base_Composer::_shift_half = 0xF;


void _Base_Composer::reset_finish()
{
    this->_is_finished = false;
    this->_suit = 0;
    this->_high_card = cards::ACE;
}
