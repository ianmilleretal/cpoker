#ifndef CHINESE_POKER
#define CHINESE_POKER


#include "../card_cons.hpp"
#include "player.hpp" 
#include "deck.hpp"
#include "reader.hpp"
#include "payoff_table.hpp"
#include <string>


class _Base_Chinese_Poker
{
private:
    static const std::string PAIRS_PATH;
    static const std::string TRIPS_PATH;
    static const std::string PAYOFFS_PATH;
    static const int NUM_PLAYERS;
    static const int DECK_SEED;

    void _initialize();
    std::string _pairs_path;
    std::string _trips_path;
    std::string _payoffs_path;


protected:
    static const int TOTAL_3C_PAYOFFS = 3744 + 52;

    Payoff _payoffs_3c[_Base_Chinese_Poker::TOTAL_3C_PAYOFFS];
    Player** _players;
    int _num_players;
    Deck* _deck;


public:
    _Base_Chinese_Poker();
    _Base_Chinese_Poker(int seed, int num_players);
    ~_Base_Chinese_Poker();

    void initialize();
    Player* get_player(int i)
        {return this->_players[i];}
};


#endif
