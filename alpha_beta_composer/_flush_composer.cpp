#include "_flush_composer.hpp"


_Flush_Composer::_Flush_Composer() : _Base_Composer()
{
    this->_cards[0] = cards::ACE;
    this->_cards[1] = cards::KING;
    this->_cards[2] = cards::QUEEN;
    this->_cards[3] = cards::JACK;
    this->_cards[4] = cards::NINE;
}


Payoff _Flush_Composer::flush()
{
    Card_Flags c_flags = this->_generate_hand();
    c_flags >>= this->_suit;
    if (!this->_suit) 
        this->_rank++;
    
    this->_suit++;
    if (this->_suit == 4) {
        this->_suit = 0;
        this->_reorder();
        this->_unstraighten();
    }
    Payoff result(c_flags, this->_rank, cards::FLUSH);

    return result;
}


Card_Flags _Flush_Composer::_generate_hand()
{
    const Card_Flags spade = 0x08;
    Card_Flags result = 0;
    for (int i=0; i < 5; i++) {
        result |= (spade << ((this->_cards[i]-1) * cards::NUM_SUITS) );
    }
    return result;
}


void _Flush_Composer::_skip_bottom_straight()
{
    if (this->_cards[1]==cards::FIVE && this->_cards[0]==cards::ACE)
    {
        this->_cards[0] = cards::KING;
        this->_cards[1] = cards::QUEEN;
        this->_cards[2] = cards::JACK;
        this->_cards[3] = cards::TEN;
        this->_cards[4] = cards::EIGHT;
    }
}


void _Flush_Composer::_reorder()
{
    this->_cards[4]--;
    if (this->_cards[4] == 0)
        this->_cards[3]--;
    if (this->_cards[3] == cards::TWO)
        this->_cards[2]--;
    if (this->_cards[2] == cards::THREE)
        this->_cards[1]--;
    if (this->_cards[1] == cards::FOUR) {
        this->_cards[0]--;
        this->_cards[1] = this->_cards[0] - 1;
    }
    this->_skip_bottom_straight();
    if (this->_cards[0]==cards::SIX && this->_cards[1]==cards::FIVE) 
    {
        this->_is_finished = true;
    } else {
        if (this->_cards[2] == cards::THREE) 
            this->_cards[2] = this->_cards[1] - 1;
        if (this->_cards[3] == cards::TWO)
            this->_cards[3] = this->_cards[2] - 1;
        if (this->_cards[4] == 0)
            this->_cards[4] = this->_cards[3] - 1;
    }
}


void _Flush_Composer::_unstraighten()
{
    if (
        this->_cards[0] - 1 == this->_cards[1] &&
        this->_cards[1] - 1 == this->_cards[2] &&
        this->_cards[2] - 1 == this->_cards[3] &&
        this->_cards[3] - 1 == this->_cards[4]
    ) {
        this->_cards[4]--;
    }
}
