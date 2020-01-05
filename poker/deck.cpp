#include "deck.hpp"
#include "hand.hpp"
#include <random>


void Deck::deal(Hand &hand)
{
    std::uniform_int_distribution<unsigned short> 
        distribution(1, this->_count);
    Short_U drawn = distribution(this->_generator);
    this->_count--;

    Card_Flags place = 1;
    while (drawn) {
        if (this->_cards & place) {
            drawn--;
        }
        place <<= 1;
    }
    if (!place) {
        place = 0x80000000000000; //0x10000000000000 ??? fixed ???
    } else {
        place >>= 1;
    }
    this->_cards ^= place;
    hand.set(hand.get() | place);
}


void Deck::reset()
{
    this->_cards = 0 - 1;
    this->_count = cards::NUM_CARDS_PER_DECK;
}
