//TODO: Fix bug with composer.two_of_a_kind()

#include "../card_cons.hpp"
#include "payoff_composer.hpp"
#include <iostream>
#include <fstream>


const std::string file_name = "payoffs.bin";


#define WRITE(FILE, COMPOSER, HAND, PAYOFF)          \
    while (COMPOSER.get_is_finished() == false) {    \
        PAYOFF = COMPOSER.HAND();                    \
        FILE.write((char*) &PAYOFF, sizeof(PAYOFF)); \
    }                                                \
    composer.reset_finish();



int main()
{
    std::fstream ofile;
    ofile.open(file_name, std::ios_base::binary | std::ios_base::out);
    Payoff_Composer composer;
    Payoff payoff;

    //This should be called last; there is a bug, probably with the 
    //composer.reset() member function - when composer.two_of_a_kind()
    //is called last, it causes collisions. It runs fine this way, but
    //then the payoff ranks are out of order. This is where I left off
    WRITE(ofile, composer, two_of_a_kind,   payoff); 
    WRITE(ofile, composer, straight_flush,  payoff);
    WRITE(ofile, composer, four_of_a_kind,  payoff);
    WRITE(ofile, composer, full_house,      payoff);
    WRITE(ofile, composer, flush,           payoff);
    WRITE(ofile, composer, straight,        payoff);
    WRITE(ofile, composer, three_of_a_kind, payoff);
    WRITE(ofile, composer, two_pair,        payoff);


    ofile.close();
    return 0;
}
