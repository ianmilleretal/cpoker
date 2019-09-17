#include "_round_chinese_poker.hpp"
#include "../card_cons.hpp"
#include "hand.hpp"
#include <iostream>
#include <bitset>


#define BREAK(a) std::cout << a << std::endl;
#define BITS(a)  std::bitset<52>( (a) )


void _Round_Chinese_Poker::take_round()
{
    for (int i=0; i < this->_num_players; i++) {
        this->_players[i]->draw();
        this->_payoffs_table.lookup((*this->_players[i]));
        this->_nothing_table.lookup((*this->_players[i]));
        this->_players[i]->add_payoffs_3c(
            this->_payoffs_3c, _Base_Chinese_Poker::TOTAL_3C_PAYOFFS);
        std::cout << this->_players[i]->get_num_payoffs() << std::endl;
        std::cout << this->_players[i]->get_num_nothing() << std::endl;
        std::cout << this->_players[i]->get_num_payoffs_3c() << std::endl;

        int count = this->_players[i]->get_num_payoffs() +this->_players[i]->get_num_nothing();
        if (count < 1287) {
            std::cout << "ALERT!" << std::endl;
        } else if (count > 1287) {
            collision_check(this->_players[i]);
        } else {
            std::cout << "GOOD"
        }
//        exit(1);
//        this->_players[i]->compose_turnin();

//        Turnin result = this->_players[i]->get_turnin();
/*
        std::cout << BITS(this->_players[i]->get_cards()) << "  hand" << std::endl;
        std::cout << BITS(result.first->first) << '\t';
        if (result.first->third == cards::NOTHING)
            std::cout << "Hi-c" << '\t';
        std::cout << result.first->second << std::endl;
        std::cout << BITS(result.second->first) << '\t';
        if (result.second->third == cards::NOTHING)
            std::cout << "Hi-c" << '\t';
        std::cout << result.second->second << std::endl;
        std::cout << BITS(result.third->first) << '\t';
        if (result.third->third == cards::NOTHING)
            std::cout << "Hi-c" << '\t';
        std::cout << result.third->second << std::endl;
        std::cout << std::endl;
*/
    }

}


void _Round_Chinese_Poker::end_round()
{
    this->_deck->reset();
    for (int i=0; i < this->_num_players; i++) {
        this->_players[i]->reset();
    }
}

