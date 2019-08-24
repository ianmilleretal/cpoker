#include "../card_cons.hpp"
#include "payoff_table.hpp"
#include "player.hpp"
#include <iostream>
#include <bitset>


Payoff nothing[1302540];
Card_Flags cardz = 0;
Card_Flags card[5];
int tracker[5];
bool is_rank = false;
int rank = 0;

void advance(int i=4);
int bitcount(const Card_Flags &cards);


int main()
{
    Payoff_Table::initialize("../bins/payoffs.bin");
    for (int i=0; i < 5; i++) {
        card[i] = cards::ACE_OF_SPADES >> (i * cards::NUM_SUITS);
        cardz |= card[i];
        tracker[i] = 0;
    }
    Hand buffer;
    Player dummy;
    int count = 0;
    bool bad = false;
    do {
        buffer.reset(); 
        dummy.reset();
        buffer.increment_count(5);
        buffer.set(cardz);
        dummy.set_hand(buffer);
        Payoff_Table::lookup(dummy);
        if (dummy.get_num_payoffs() == 0) {
            if (bitcount(cardz) != 5) bad = true;
            if (is_rank) {
                rank++;
                is_rank = false;
            }
            Payoff p_buffer(cardz, rank, cards::NOTHING);
            nothing[count] = p_buffer;
            std::cout << std::bitset<52>(cardz) << '\t' << count <<std::endl;
            count++;
        }
        advance();
    } while (count < 1302540); // 1302540
    std::cout << "Found a bad payoff: " << bad << std::endl;

    return 0;
}


void advance(int i)
{
    card[i] >>= 1;
    if  (
            !card[i] || 
            (i != 4 && (card[i] == (1 << ((4-i) * cards::NUM_SUITS - 1) ) ) )
        ){
        is_rank = true;
        advance(i-1);
        card[i] = card[i-1] >> (cards::NUM_SUITS - tracker[i-1]);
        tracker[i] = 0;
    } else {
        tracker[i]++;
        if (tracker[i] == 4) {
            is_rank = true;
            tracker[i] = 0;
        }
    }
    cardz = 0;
    for (int i=0; i < 5; i++)
        cardz |= card[i];
}


int bitcount(const Card_Flags &cards)
{
    int result = 0;
    Card_Flags bit = 1;
    for (int i=0; i < 64; i++) {
        if (cards & bit) result++;
        bit <<= 1;
    }
    return result;
}
