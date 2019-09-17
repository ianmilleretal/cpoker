#include "../card_cons.hpp"
#include "payoff_composer.hpp"
#include <iostream>
#include <fstream>
#include <bitset>


const std::string file_name = "payoffs.bin";


int bitcount(const Card_Flags &cards);


int count = 0;


#define WRITE(FILE, COMPOSER, HAND, PAYOFF)          \
    while (COMPOSER.get_is_finished() == false) {    \
        PAYOFF = COMPOSER.HAND();                    \
        if (bitcount(PAYOFF.first) == 5)  {          \
            FILE.write((char*) &PAYOFF, sizeof(PAYOFF)); \
            count++;                                     \
        } else {                                         \
            std::cout << # HAND << std::endl;            \
            std::cout << std::bitset<64>(PAYOFF.first) << std::endl; \
        }                                                \
    }                                                    \
    composer.reset_finish();


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




int main()
{
    std::fstream ofile;
    ofile.open(file_name, std::ios_base::binary | std::ios_base::out);
    Payoff_Composer composer;
    Payoff payoff;

    WRITE(ofile, composer, two_of_a_kind,   payoff);
    WRITE(ofile, composer, straight_flush,  payoff);
    WRITE(ofile, composer, four_of_a_kind,  payoff);
    WRITE(ofile, composer, full_house,      payoff);
    WRITE(ofile, composer, flush,           payoff);
    WRITE(ofile, composer, straight,        payoff);
    WRITE(ofile, composer, three_of_a_kind, payoff);
    WRITE(ofile, composer, two_pair,        payoff);

    std::cout << count << std::endl;

    ofile.close();
    return 0;
}
