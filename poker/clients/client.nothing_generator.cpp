#include "../card_cons.hpp"
#include "payoff_table.hpp"
#include "player.hpp"
#include <fstream>
#include <string>


const int NUM_NOTHINGS = 1302540;
const std::string file_name = "../bins/nothing.bin";


Card_Flags cardz = 0;
Card_Flags card[5];
int tracker[5];
bool is_rank = false;
int rank = 0;


void advance(int i=4);
void initialize(Payoff_Table table);
int bitcount(const Card_Flags &cards);
void write(Card_Flags cardz, int rank, std::fstream &ofile);
void generate_payoffs(Payoff_Table table, std::fstream &ofile);


int main()
{
    std::fstream ofile;
    ofile.open(file_name, std::ios_base::binary | std::ios_base::out);

    Payoff_Table table;
    initialize(table);

    generate_payoffs(table, ofile);

    ofile.close();
    return 0;
}


void generate_payoffs(Payoff_Table table, std::fstream &ofile)
{
    Hand buffer;
    Player dummy;
    int count = 0;

    do {
        buffer.reset(); 
        buffer.increment_count(5);
        buffer.set(cardz);
        dummy.reset();
        dummy.set_hand(buffer);
        table.lookup(dummy);
        if (dummy.get_num_payoffs() == 0) {
            if (is_rank) {
                rank++;
                is_rank = false;
            }
            write(cardz, rank, ofile);
            count++;
        }
        advance();
    } while (count < NUM_NOTHINGS); // 1302540
}


void write(Card_Flags cardz, int rank, std::fstream &ofile)
{
    Payoff payoff(cardz, rank, cards::NOTHING);
    ofile.write((char*) &payoff, sizeof(payoff));
}


void initialize(Payoff_Table table)
{
    table.initialize("../bins/payoffs.bin");
    for (int i=0; i < 5; i++) {
        card[i] = cards::ACE_OF_SPADES >> (i * cards::NUM_SUITS);
        cardz |= card[i];
        tracker[i] = 0;
    }
}


void advance(int i)
{
    card[i] >>= 1;
    if  (
            !card[i] || 
            (i != cards::NUM_SUITS && (card[i] == 
            (1 << ((cards::NUM_SUITS-i) * cards::NUM_SUITS - 1) ) ) )
        ){
        is_rank = true;
        advance(i-1);
        card[i] = card[i-1] >> (cards::NUM_SUITS - tracker[i-1]);
        tracker[i] = 0;
    } else {
        tracker[i]++;
        if (tracker[i] == cards::NUM_SUITS) {
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
    const int NUM_BITS = 64;
    int result = 0;
    Card_Flags bit = 1;
    for (int i=0; i < NUM_BITS; i++) {
        if (cards & bit) result++;
        bit <<= 1;
    }
    return result;
}
