#include "../card_cons.hpp"
#include "payoff_composer.hpp"
#include <iostream>
#include <bitset>
#include <utility>
#include <fstream>
#include <string>



int bit_count(Card_Flags flags)
{
    int result = 0;
    Card_Flags bit = 1;
    for (int i=0; i < 52; i++) {
        if (bit & flags) result++;
        bit <<= 1;
    }
    return result;
}


int main()
{

    Payoff_Composer composer;
/*
    for (int i=0; i<40; i++) {
        Card_Flags hand = composer.straight_flush().first;
        std::cout << std::bitset<52>(hand) << std::endl;
        if (bit_count(hand) != 5) {
            std::cout << "here" << std::endl;
            exit(1);
        }
        if (composer.get_is_finished()) std::cout << "FINISHED SF" << std::endl;
    }
    composer.reset_finish();


    for (int i=0 ; i<624; i++) {
        Card_Flags hand = composer.four_of_a_kind().first;
        std::cout << std::bitset<52>(hand) << std::endl;
        if (bit_count(hand) != 5) {
            std::cout << "here" << std::endl;
            exit(1);
        }
        if (composer.get_is_finished()) std::cout << "FINISHED 4k" << std::endl;
    }
    composer.reset_finish();


    for (int i=0; i < 3744; i++) {
        Card_Flags hand = composer.full_house().first;
        std::cout << std::bitset<52>(hand) << std::endl;
        if (bit_count(hand) != 5) {
            std::cout << "here" << std::endl;
            exit(1);
        }
        if (composer.get_is_finished()) std::cout << "FINISHED FH" << std::endl;
    }
    composer.reset_finish();


    for (int i=0; i < 5108; i++) {
        Card_Flags hand = composer.flush().first;
        std::cout << std::bitset<52>(hand) << std::endl;
        if (bit_count(hand) != 5) {
            std::cout << "here" << std::endl;
            exit(1);
        }
        if (composer.get_is_finished()) std::cout << "FINISHED FL" << std::endl;
    }
    composer.reset_finish();


    for (int i=0; i < 10200; i++) {
        Card_Flags hand = composer.straight().first;
        std::cout << std::bitset<52>(hand) << std::endl;
        if (bit_count(hand) != 5) {
            std::cout << "here" << std::endl;
            exit(1);
        }
        if (composer.get_is_finished()) std::cout << "FINISHED ST" << std::endl;
    }
    composer.reset_finish();


    for (int i=0; i < 54912; i++) {
        Card_Flags hand = composer.three_of_a_kind().first;
        std::cout << std::bitset<52>(hand) << std::endl;
        if (bit_count(hand) != 5) {
            std::cout << "here" << std::endl;
            exit(1);
        }
        if (composer.get_is_finished()) std::cout << "FINISHED 3K" << std::endl;
    }
    composer.reset_finish();


    for (int i=0; i < 123552; i++) { //123552
        Card_Flags hand = composer.two_pair().first;
        std::cout << std::bitset<52>(hand) << std::endl;
        if (bit_count(hand) != 5) {
            std::cout << "here" << std::endl;
            exit(1);
        }
        if (composer.get_is_finished()) std::cout << "FINISHED TP" << std::endl;
    }

*/
    for (int i=0; i < 10000; i++) { //1098240
        Card_Flags hand = composer.two_of_a_kind().first;
        std::cout << std::bitset<52>(hand) << std::endl;
        if (bit_count(hand) != 5) {
            std::cout << "here" << std::endl;
            exit(1);
        }
        if (composer.get_is_finished()) std::cout << "FINISHED 2K" << std::endl;
    }
    composer.reset_finish();


    std::cout << "Complete - no errors" << std::endl;

    return 0;
}

