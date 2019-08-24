#include "hand.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "payoff_table.hpp"
#include "reader.hpp"

#include <iostream>
#include <cstdint>
#include <random>
#include <time.h>
#include <bitset>
#include <fstream>

Payoff trips[52];
Payoff pairs[3744];
void initialize();
void print_bits(Hand my_hand, std::string msg="");


int main()
{
    Deck deck;
    deck.seed(99);
    initialize();

    Player player_one(&deck);
    player_one.draw();
    print_bits(player_one.get_hand(), "Player 1 hand:\n" );
    Payoff_Table::lookup(player_one);

    Payoff** payoffs = player_one.get_payoffs();
    for (int i=0; i < player_one.get_num_payoffs(); i++) {
        std::cout << std::bitset<52>((*payoffs[i]).first) << '\t';
        std::cout << (*payoffs[i]).second << std::endl;
    }
    return 0;
}


void print_bits(Hand my_hand, std::string msg)

{
    std::bitset<52> hand_flags(my_hand.get() );
    std::cout << msg;
    std::cout << hand_flags << std::endl;
}


void initialize()
{
    const std::string pairs_path = "../bins/3c_pairs.bin";
    const std::string trips_path = "../bins/3c_trips.bin";
    const std::string payoff_path = "../bins/payoffs.bin";
    Read read_pairs(pairs_path);
    Read read_trips(trips_path);
    read_pairs.bin(pairs);
    read_trips.bin(trips);
    Payoff_Table::initialize(payoff_path);
}
