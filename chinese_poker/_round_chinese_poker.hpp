#ifndef _ROUND_CHINESE_POKER
#define _ROUND_CHINESE_POKER

#include "_base_chinese_poker.hpp"


class _Round_Chinese_Poker : public _Base_Chinese_Poker
{
public:
    _Round_Chinese_Poker() :
        _Base_Chinese_Poker() {}
    _Round_Chinese_Poker(int seed, int num_players) :
        _Base_Chinese_Poker(seed, num_players) {}

    void take_round();
    void end_round();
};


#endif 
