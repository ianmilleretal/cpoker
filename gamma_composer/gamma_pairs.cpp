#include "gamma_pairs.hpp"
#include "../card_cons.hpp"
#include "../alpha_beta_composer/pair_generator.hpp"
#include <iostream>
#include <bitset>

//sum of num of everything above a pair.
const int Three_Dubs_Composer::_BEG_RANGE = 
    40 + 624 + 3744 + 5108 + 10200 + 54912 + 123552;
const int Three_Dubs_Composer::_NUM_DUBS = 1098240;


static int bitcount(Card_Flags &cards, int kind)
{
    int result = 0;
    Card_Flags flag = 0x01;
    flag <<= (kind * cards::NUM_SUITS);

    for (int i=0; i < cards::NUM_SUITS; i++) {
        if (flag & cards) result++;
        flag <<= 1;
    }
    return result;
}


int high_kicker(Card_Flags &cards)
{
    int result = cards::ACE - 1;
    bool found = false;
    while (!found) {
        if (bitcount(cards, result) != 1) {
            result --;
        } else {
            found = true;
        }
    }
    return result;
}


Three_Dubs_Composer::Three_Dubs_Composer(Payoff* all_payoffs)
{
    this->_5c_dubs = all_payoffs + this->_BEG_RANGE;
    this->_kind = cards::ACE - 1;
    this->_kicker = cards::KING - 1;
}


#include <iostream>
void Three_Dubs_Composer::parse_dubs()
{
    int rank;
    int frank = this->_5c_dubs[0].second;
    int index=0;
    for (int i=0; i < this->_NUM_DUBS; i++) {
        if (frank != this->_5c_dubs[i].second) {
            frank = this->_5c_dubs[i].second;
            if (bitcount(this->_5c_dubs[i].first, this->_kind) != 2) {
                rank = this->_5c_dubs[i-1].second;
                this->_compose_bottom_set(rank, index);
                this->_kind--;
                this->_kicker = cards::ACE - 1;
            } else if 
            (
                high_kicker(this->_5c_dubs[i].first) != this->_kicker
            )
            {
                rank = this->_5c_dubs[i-1].second;
                this->_compose_set(rank, index);
                this->_kicker--;
                if (this->_kicker == this->_kind) this->_kicker--;
            }
        }

    }
    this->_compose_bottom_set(rank, index);
}


void Three_Dubs_Composer::_compose_set(int rank, int &index)
{
    Pair_Generator generator;
    Card_Flags cards;
    Card_Flags kicker_flag;
    for (int i=0; i < cards::NUM_SUITS; i++) {
            kicker_flag = 0x01;
            kicker_flag <<= this->_kicker * cards::NUM_SUITS;
        kicker_flag <<= i;
        for (int j=0; j < cards::COMBO_DUBS; j++) {
            cards = generator.next() <<
                (this->_kind * cards::NUM_SUITS);
            cards |= kicker_flag;
            this->_3c_dubs[index] = Payoff(cards, rank, cards::PAIR);
            index++;
        }
    }
}


void Three_Dubs_Composer::_compose_bottom_set(int rank, int &index)
{
    this->_compose_set(rank, index);
    this->_kicker--;
    if (this->_kicker == this->_kind) this->_kicker--;
    this->_compose_set(rank, index);
    this->_kicker--;
    if (this->_kicker == this->_kind) this->_kicker--;
    this->_compose_set(rank, index);
}
