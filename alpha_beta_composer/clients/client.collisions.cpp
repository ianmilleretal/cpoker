#include "../card_cons.hpp"
#include "payoff_composer.hpp"
#include <iostream>
#include <fstream>
#include <bitset>


const std::string file_name = "payoffs.bin";
Payoff payos[10000][1000];
int map[10000];


int count=0;
int collisions=0;


#define WRITE(COMPOSER, HAND, PAYOFF)                  \
    std::cout << # HAND << std::endl;                  \
    while (COMPOSER.get_is_finished() == false) {      \
        PAYOFF = COMPOSER.HAND();                      \
        int hash = PAYOFF.first % 10000;               \
        for (int i=0; i < map[hash]; i++) {            \
            if (PAYOFF.first == payos[hash][i].first) {\
                collisions++;                          \
                std::cout << std::bitset<52>(PAYOFF.first) << std::endl; \
                std::cout << count << std::endl;       \
            }                                          \
        }                                              \
        payos[hash][map[hash]] = PAYOFF;               \
        map[hash]++;                                   \
        count++;                                       \
    }                                                  \
    composer.reset_finish();                           \
    std::cout << count << std::endl;                   \
    std::cout << collisions << std::endl;



int main()
{
    for (int i=0; i < 1000; i++) {
        map[i] = 0;
    }
    std::fstream ofile;
    ofile.open(file_name, std::ios_base::binary | std::ios_base::out);
    Payoff_Composer composer;
    Payoff payoff;

    WRITE(composer, two_of_a_kind,   payoff);
    WRITE(composer, straight_flush,  payoff);
    WRITE(composer, four_of_a_kind,  payoff);
    WRITE(composer, full_house,      payoff);
    WRITE(composer, flush,           payoff);
    WRITE(composer, straight,        payoff);
    WRITE(composer, three_of_a_kind, payoff);
    WRITE(composer, two_pair,        payoff);

  

    ofile.close();
    return 0;
}
