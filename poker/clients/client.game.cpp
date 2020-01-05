#include "_round_chinese_poker.hpp"
#include <iostream>


int main()
{
    std::cout << "Initializing... ";
    _Round_Chinese_Poker game;
    std::cout << "Done." << std::endl;
    for (int i=0; i < 10; i++) {
        if (i % 1000 == 0)
            std::cout << "Taking round " << i << std::endl;
        game.take_round();
        game.end_round();
    }
    std::cout << "Done." << std::endl;


    return 0;
}
