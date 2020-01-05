#include "_poker_round.hpp"
#include "../card_cons.hpp"
#include "hand.hpp"
#include <iostream>
#include <bitset>


#define BREAK(a) std::cout << a << std::endl;
#define BITS(a)  std::bitset<52>( (a) )


int collision_check(Player* player);


void _Round_Chinese_Poker::take_round()
{
    for (int i=0; i < this->_num_players; i++) {
        this->_players[i]->draw();
        this->_payoffs_table.lookup((*this->_players[i]));
        this->_nothing_table.lookup((*this->_players[i]));
        this->_players[i]->add_payoffs_ga(
            this->_payoffs_ga, _Base_Chinese_Poker::TOTAL_GA_PAYOFFS);
        if (this->_players[i]->get_num_payoffs_ab() +
            this->_players[i]->get_num_nothing() != 1287) 
            std::cout << "Payoff Total Not Equal to 1287!\n" <<
            "Player: " << i << '\n';
//        this->_players[i]->compose_turnin();
//        Turnin result = this->_players[i]->get_turnin();
    }

}


void _Round_Chinese_Poker::end_round()
{
    this->_deck->reset();
    for (int i=0; i < this->_num_players; i++) {
        this->_players[i]->reset();
    }
}


int collision_check(Player* player)
{
    int result=0;
    Payoff** payoffs = player->get_payoffs_ab();
    Payoff** nothing = player->get_nothing();
    for (int i=0; i < player->get_num_payoffs_ab(); i++) {
        int count = 0;
        for (int j=0; j < player->get_num_payoffs_ab(); j++) {
            if (payoffs[i]->first == payoffs[j]->first) count++;
        }
        if (count) result += count - 1;
        if (count > 1) std::cout << "collision found payoff\n";
    }
    for (int i=0; i < player->get_num_nothing(); i++) {
        int count = 0;
        for (int j=0; j < player->get_num_nothing(); j++) {
            if (nothing[i]->first == nothing[j]->first) count++;
        }
        if (count) result += count - 1;
        if (count > 1) std::cout << "cross collision found\n";
    }
    for (int i=0; i < player->get_num_nothing(); i++) {
        int count = 0;
        for (int j=0; j < player->get_num_payoffs_ab(); j++) {
            if (nothing[i]->first == payoffs[j]->first) {
                count++;
                std::cout << BITS(nothing[i]->first) << std::endl;
            }
        }
        if (count) {
            result += count - 1;
            std::cout << "cross collision found\n";
        }
    }
    return result;
}
