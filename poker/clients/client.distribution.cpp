#include "hand.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "payoff_table.hpp"
#include "reader.hpp"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <random>
#include <time.h>
#include <bitset>
#include <fstream>


#define ALL(A, B) B(A, 0); B(A, 1); B(A, 2); B(A, 3)
#define DRAW(a, b) a[b].draw()
#define GIVE(a, b) a[b].give()
#define LOOKUP(a, b) Payoff_Table::lookup(a[b])
#define COUNT(a, b) count_player(a[b])


void count_player(Player &player);
void count_payoffs(Payoff* payoff);
void print_totals();
void print_total(const uint_fast64_t &total, const std::string &title);
void print_probability(const char &payoff);


std::string PAYOFF_PATH = "../bins/payoffs.bin";
int NUM_TRIALS = 1000;
int SEED = 255;


uint_fast64_t total = 0;
uint_fast64_t straight_flushes = 0;
uint_fast64_t four_of_a_kinds = 0;
uint_fast64_t fullhouses = 0;
uint_fast64_t flushes = 0;
uint_fast64_t straights = 0;
uint_fast64_t three_of_a_kinds = 0;
uint_fast64_t two_pairs = 0;
uint_fast64_t pairs = 0;
bool has_payoff[cards::PAIR+1];
int has_payoff_count[cards::PAIR+1];


int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Usage: ./<run> <NUM_TRIALS><SEED>" << std::endl;
    } else {
        NUM_TRIALS = atoi(argv[1]);
        SEED = atoi(argv[2]);
    }
    for (int i=0; i < cards::PAIR+1; i++) {
        has_payoff[i] = false;
        has_payoff_count[i] = 0;

    }
    std::cout << "Intiializing..." << std::endl;
    Payoff_Table::initialize(PAYOFF_PATH);
    std::cout << "Done!" << std::endl << std::endl;
    std::cout << "Seeding Deck..." << std::endl;
    Deck deck;
    deck.seed(SEED);
    std::cout << "Done!" << std::endl << std::endl;
    std::cout << "Analyzing..." << std::endl;
    std::cout << "Seed: " << SEED << std::endl
;    std::cout << "Total Trials: " << NUM_TRIALS << std::endl;
    Player players[4] = {Player(&deck), Player(&deck),
                         Player(&deck), Player(&deck)};
    for (int i=0; i < NUM_TRIALS; i++) {
        ALL(players, DRAW);
        ALL(players, LOOKUP);
        ALL(players, COUNT);
        ALL(players, GIVE);
        if (i % 1000 == 0)
            std::cout << "Trial number: " << i << std::endl;
    }
    print_totals();

    return 0;
}


void print_totals()
{
    std::cout << std::endl;
    print_total(total, "Payoff Count");
    print_total(straight_flushes, "Straight Flushes");
    print_probability(cards::STRAIGHT_FLUSH);
    print_total(four_of_a_kinds, "4 of a Kinds");
    print_probability(cards::FOUR_OF_A_KIND);
    print_total(fullhouses, "Fullhouses");
    print_probability(cards::FULLHOUSE);
    print_total(flushes, "Flushes");
    print_probability(cards::FLUSH);
    print_total(straights, "Straights");
    print_probability(cards::STRAIGHT);
    print_total(three_of_a_kinds, "3 of a Kinds");
    print_probability(cards::THREE_OF_A_KIND);
    print_total(two_pairs, "Two-Pairs");
    print_probability(cards::TWO_PAIR);
    print_total(pairs, "Pairs");
    print_probability(cards::PAIR);
}


void print_total(const uint_fast64_t &totals, const std::string &title)
{
    double mean_buffer = totals;
    mean_buffer /= NUM_TRIALS * 4;
    std::cout << std::left << std::setw(24) <<
    "Total " + title + ": " << std::right <<
    std::setw(13) << totals << std::left << std::setw(15) <<
    "\tMean: " << mean_buffer << std::endl;
}


void print_probability(const char &payoff)
{
    double buffer = has_payoff_count[payoff];
    buffer /= NUM_TRIALS * 4;
    std::cout << std::left << std::setw(24) << "Hands Containing:" << 
    std::right << std::setw(13) << has_payoff_count[payoff] <<
    std::left << std::setw(15) <<"\tProbability: " << 
    std::fixed << buffer << std::endl << std::endl;
}

void count_player(Player &player)
{
    total += player.get_num_payoffs();
    Payoff** payoffs = player.get_payoffs();
    for (int i=0; i < player.get_num_payoffs(); i++) {
        count_payoffs(payoffs[i]);
        has_payoff[payoffs[i]->third] = true;
    }
    for (int i=0; i < cards::PAIR+1; i++) {
        has_payoff_count[i] += has_payoff[i];
        has_payoff[i] = false;
    }
}


void count_payoffs(Payoff* payoff)
{
    switch(payoff->third) {
        case cards::STRAIGHT_FLUSH :  straight_flushes++; break;
        case cards::FOUR_OF_A_KIND :  four_of_a_kinds++;  break;
        case cards::FULLHOUSE :       fullhouses++;       break;
        case cards::FLUSH :           flushes++;          break;
        case cards::STRAIGHT :        straights++;        break;
        case cards::THREE_OF_A_KIND : three_of_a_kinds++; break;
        case cards::TWO_PAIR :        two_pairs++;        break;
        case cards::PAIR :            pairs++;            break;
    }
}


//Useful code
/*
    players[0].draw();
    Payoff_Table::lookup(players[0]);
    Payoff** payoffs = players[0].get_payoffs();
    for (int i=0; i < players[0].get_num_payoffs(); i++)
        std::cout << std::bitset<52>((*payoffs[i]).first) <<
        ' ' << (*payoffs[i]).third << std::endl;
    std::cout << players[0].get_num_payoffs() << std::endl;
    players[0].give();
*/


/*
    Card_Flags cards1[2000];
    Card_Flags cards2[2000];

    ALL(players, DRAW);
    ALL(players, LOOKUP);
    Payoff** pf = players[0].get_payoffs();
    for (int i=0; i< players[0].get_num_payoffs(); i++) {
        cards1[i] = pf[i]->first;
    }
    ALL(players, GIVE);

    ALL(players, DRAW);
    ALL(players, LOOKUP);
    pf = players[0].get_payoffs();
    for (int i=0; i< players[0].get_num_payoffs(); i++) {
        cards2[i] = pf[i]->first;
    }
    std::cout << "here: " << std::endl;
    for (int i=0; i< players[0].get_num_payoffs(); i++) {
        std::cout << "here: " << std::endl;
        if (cards1[i] != cards2[i]) {
            std::cout << "safe at " << i << std::endl;
            exit(1);
        } else {
            std::cout << cards1[i] << ' ' << cards2[i] << std::endl;
        }
    }
*/
