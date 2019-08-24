#include "_straight_composer.hpp"
#include <iostream>


static Card_Flags generate_card(int kind, int suit);
static bool matches(Card_Flags cards, Card_Flags templas);


Payoff _Straight_Composer::straight()
{
    Card_Flags cards = 0;

    if (!this->_which) {
        // 6, 5, 4, 3, 2 suited
        Card_Flags templat = 0x11111;
        cards = this->_regular_straight();
        while (matches(cards, templat) )
            cards = this->_regular_straight();
        if (this->_which) {
            this->reset_finish();
            this->_kind = cards::ACE;
        }
    } else {
        //A, -K, -Q, -J, -T, -9, -8, -7, -6, 5, 4, 3, 2 suited
        Card_Flags templat = 0x1000000001111;
        cards = this->_bottom_straight();
        while (matches(cards, templat) )
            cards = this->_bottom_straight();
    }
    return Payoff(cards, this->_rank, cards::STRAIGHT);
}


Card_Flags _Straight_Composer::_regular_straight()
{   //I honestly thought using for-loops here made it harder to read
    Card_Flags cards = 0;
    cards |= generate_card(this->_kind - 0,
        (this->_suit / 0x100) % cards::NUM_SUITS);//4^4
    cards |= generate_card(this->_kind - 1,
        (this->_suit / 0x040) % cards::NUM_SUITS);//4^3
    cards |= generate_card(this->_kind - 2,
        (this->_suit / 0x010) % cards::NUM_SUITS);//4^2
    cards |= generate_card(this->_kind - 3,
        (this->_suit / 0x004) % cards::NUM_SUITS);//4^1
    cards |= generate_card(this->_kind - 4,
        this->_suit % cards::NUM_SUITS);//4^0

    this->_suit++;
    if (this->_suit == (0x400-1) && this->_kind == cards::SIX)
        this->_which = true;
    if (this->_suit == 0x400) {
        this->_suit = 0;
        this->_kind--;
        this->_rank++;
    }
    return cards;
}


Card_Flags _Straight_Composer::_bottom_straight()
{   //For loops ended up being convoluted & we're still under 25 lines
    Card_Flags cards = 0;
    cards |= generate_card(cards::ACE,
        (this->_suit / 0x100) % cards::NUM_SUITS);
    cards |= generate_card(cards::FIVE,
        (this->_suit / 0x040) % cards::NUM_SUITS);
    cards |= generate_card(cards::FOUR,
        (this->_suit / 0x010) % cards::NUM_SUITS);
    cards |= generate_card(cards::THREE,
        (this->_suit / 0x004) % cards::NUM_SUITS);
    cards |= generate_card(cards::TWO,
        this->_suit % cards::NUM_SUITS);

    this->_suit++;
    if (this->_suit == 0x400-1) {//Only one set of Aces, then finish
        this->_is_finished = true;
    }
    return cards;
}


Card_Flags generate_card(int kind, int suit)
{
    Card_Flags result = 1;
    result <<= suit;
    return result << (kind-1) * cards::NUM_SUITS;
}


bool matches(Card_Flags cards, Card_Flags templat)
{
    bool result = false;
    for (int i=0; i < cards::NUM_CARDS_PER_DECK; i++) {
        if (cards == templat) result = true;
        templat <<= 1;
    }
    return result;
}
