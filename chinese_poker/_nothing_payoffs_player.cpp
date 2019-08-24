#include "_nothing_payoffs_player.hpp"
#include <stdexcept>


static int rank_cards(const Card_Flags &cards);


void _Nothing_Payoffs_Player::_reset()
{
    this->_one.third = cards::SENTINEL;
    this->_two.third = cards::SENTINEL;
}


Payoff* _Nothing_Payoffs_Player::_rank_nothing_payoff(
    const Card_Flags &cards)
{
    Payoff* result;
    int rank = rank_cards(cards);
    if (this->_one.third == cards::SENTINEL) {
        this->_one = Payoff(cards, rank, cards::NOTHING);
        result = &this->_one;
    } else if (this->_two.third == cards::SENTINEL) {
        this->_two = Payoff(cards, rank, cards::NOTHING);
        result = &this->_two;
    } else {
        throw std::runtime_error("Nothing Payoffs Not Reset!");
    }
    return result;
}


Payoff* _Nothing_Payoffs_Player::_create_nothing_payoff(
    const Card_Flags &cards)
{

    Card_Flags result = 0x0;
    int count = 0;
    Card_Flags card = cards::ACE_OF_SPADES;
    do {
        if (card & cards) {
            result |= card;
            count++;
        }
        card >>= 1;
    } while (count < 5);
    return this->_rank_nothing_payoff(result);
}


int rank_cards(const Card_Flags &cards)
{
    int rank = 0;
    int bit = 1;
    for (int i=0; i < cards::NUM_KINDS; i++) {
        Card_Flags card = cards::ACE_OF_SPADES >> i*cards::NUM_SUITS;
        bool is_found = false;
        int j=0;
        do {
            if (card & cards) {
                rank += (bit << (cards::NUM_KINDS - i - 1));
                is_found = true;
            }
            card >>= 1;
            j++;
        } while (!is_found && (j < cards::NUM_SUITS));
    }
    return rank;
}
