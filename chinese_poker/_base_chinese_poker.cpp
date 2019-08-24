#include "_base_chinese_poker.hpp"
#include <string>


const std::string _Base_Chinese_Poker::PAIRS_PATH = 
    "../bins/3c_pairs.bin";
const std::string _Base_Chinese_Poker::TRIPS_PATH =
    "../bins/3c_trips.bin";
const std::string _Base_Chinese_Poker::PAYOFFS_PATH =
    "../bins/payoffs.bin";
const int _Base_Chinese_Poker::NUM_PLAYERS = 4;
const int _Base_Chinese_Poker::DECK_SEED = 255;


_Base_Chinese_Poker::_Base_Chinese_Poker() :
    _pairs_path(PAIRS_PATH),
    _trips_path(TRIPS_PATH),
    _payoffs_path(PAYOFFS_PATH)
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
    const int NUM_PAIRS_3C = 3744;
    Payoff_Table::initialize(this->_payoffs_path);
    Reader read_pairs(this->_pairs_path);
    Reader read_trips(this->_trips_path);
    read_pairs.bin(this->_payoffs_3c);
    read_trips.bin(this->_payoffs_3c + NUM_PAIRS_3C);
}
