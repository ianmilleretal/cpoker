#include "_base_player.hpp"


void _Base_Player::draw(int num_cards)
{
    for (int i=0; i < num_cards; i++) {
        this->_pdeck->deal(this->_hand);
    }
    this->_hand.increment_count(num_cards);
}


void _Base_Player::give()
{
    this->_pdeck->set(this->_hand.get() | this->_pdeck->get());
    this->_pdeck->increment_count(this->_hand.count() );
    this->_hand.reset();
}
