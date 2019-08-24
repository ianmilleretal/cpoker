#include "three_card_compare.hpp"
#include "../card_cons.hpp"


void Three_Card_Compare::compare_pairs(
    Card_Flags cards1, Card_Flags cards2, int &score1, int &score2)
{
    int pair_kind1 = Three_Card_Compare::_find_pair(cards1);
    int pair_kind2 = Three_Card_Compare::_find_pair(cards2);
    int kicker1 = 0;
    int kicker2 = 0;
    if (pair_kind1 == pair_kind2) {
        kicker1 = Three_Card_Compare::_find_kicker(cards1);
        kicker2 = Three_Card_Compare::_find_kicker(cards2);
    }
    if (pair_kind1 + kicker1 > pair_kind2 + kicker2)
        score1++;
    else if (pair_kind1 + kicker1 < pair_kind2 + kicker2)
        score2++;
}


int Three_Card_Compare::_find_pair(Card_Flags cards)
{
    int result = cards::TWO;

    Card_Flags card = 0x01;
    bool is_found = false;
    do {
        int count = 0;
        for (int i=0; i < cards::NUM_SUITS; i++) {
            if (cards & (card << i))
                count++;
        }
        if (count = cards::NUM_CARDS_PER_PAIR)
            is_found = true;
        else {
            card <<= cards::NUM_SUITS;
            result++;
        }
    } while (!is_found);

    return result;
}


int Three_Card_Compare::_find_kicker(Card_Flags cards)
{
    int result = cards::TWO;

    Card_Flags card = 0x01;
    bool is_found = false;
    do {
        for (int i=0; i < cards::NUM_SUITS; i++) {
            if (cards & (card << i))
                is_found = true;
        }
        card <<= cards::NUM_SUITS;
        result++;
    } while (!is_found);

    return result;
}
