#include "_poker_round.hpp"
#include <iostream>


int main()
{
    std::cout << "Initializing... ";
    _Round_Chinese_Poker game;
    std::cout << "Done." << std::endl;
    for (int i=0; i < 1; i++) {
        game.take_round();
        game.end_round();
    }
    std::cout << "Done." << std::endl;


    return 0;
}
