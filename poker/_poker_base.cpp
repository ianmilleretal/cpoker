#include "_poker_base.hpp"
#include <string>


const std::string _Base_Chinese_Poker::PAIRS_PATH = 
    "../bins/pairs_ga.bin";
const std::string _Base_Chinese_Poker::TRIPS_PATH =
    "../bins/trips_ga.bin";
const std::string _Base_Chinese_Poker::PAYOFFS_PATH =
    "../bins/payoffs_ab.bin";
const std::string _Base_Chinese_Poker::NOTHING_PATH =
    "../bins/nothing.bin";
const int _Base_Chinese_Poker::NUM_PLAYERS = 4;
const int _Base_Chinese_Poker::DECK_SEED = 255;


_Base_Chinese_Poker::_Base_Chinese_Poker() :
    _pairs_path(PAIRS_PATH),
    _trips_path(TRIPS_PATH),
    _payoffs_path(PAYOFFS_PATH),
    _nothing_path(NOTHING_PATH)
{
    this->_deck = new Deck;
    this->_deck->seed(_Base_Chinese_Poker::DECK_SEED);
    this->_num_players = this->NUM_PLAYERS;
    this->_players = new Player*[_Base_Chinese_Poker::NUM_PLAYERS];
    for (int i=0; i < this->NUM_PLAYERS; i++) {
        this->_players[i] = new Player;
        this->_players[i]->set_pdeck(this->_deck);
    }
    this->_initialize();
}


_Base_Chinese_Poker::_Base_Chinese_Poker(int seed, int num_players) :
    _pairs_path(PAIRS_PATH),
    _trips_path(TRIPS_PATH),
    _payoffs_path(PAYOFFS_PATH)
{
    this->_deck = new Deck;
    this->_deck->seed(seed);
    this->_num_players = num_players;
    this->_players = new Player*[num_players];
    for (int i=0; i < this->_num_players; i++) {
        this->_players[i] = new Player;
        this->_players[i]->set_pdeck(this->_deck);
    }
    this->_initialize();
}


_Base_Chinese_Poker::~_Base_Chinese_Poker()
{
    delete this->_deck;
    for (int i=0; i < this->_num_players; i++)
        delete this->_players[i];
    delete[] this->_players;
}

#include <iostream>
#include <bitset>

void _Base_Chinese_Poker::_initialize()
{
    //6 pairs per face * 13 faces * (52-4) remaining cards off face
    const int NUM_PAIRS_GA = 3744;
    this->_payoffs_table.initialize(this->_payoffs_path);
    this->_nothing_table.initialize(this->_nothing_path);
    Reader read_pairs(this->_pairs_path);
    Reader read_trips(this->_trips_path);
    read_pairs.bin(this->_payoffs_ga);
    read_trips.bin(this->_payoffs_ga + NUM_PAIRS_GA);
}
