#ifndef PLAYER_
#define PLAYER_


#include "../card_cons.hpp"
#include "_count_payoffs_player.hpp"


enum class Strat {ALPHA, BETA, GAMMA};


class Player : 
    public _Count_Payoffs_Player
{
protected:
    Strat _strategy;
    int _score;


public:
    Player() :
        _Count_Payoffs_Player(),
        _strategy(Strat::ALPHA),
        _score(0) {}
    Player(Deck* pdeck) :
        _Count_Payoffs_Player(pdeck),
        _strategy(Strat::ALPHA),
        _score(0) {}

//    void compose_turnin();
    void reset();
    void set_score(int value)
        {this->_score = value;}
    void set_strategy(Strat strategy)
        {this->_strategy = strategy;}

    int get_score()
        {return this->_score;}
//    Turnin get_turnin()
//        {return Turnin(
//            this->_alpha, this->_beta, this->_gamma);}
};


#endif
