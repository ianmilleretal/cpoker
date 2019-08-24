#ifndef _SCORE_CHINESE_POKER
#define _SCORE_CHINESE_POKER

#include "_round_chinese_poker.hpp"


class _Score_Chinese_Poker : public _Round_Chinese_Poker
{
private:
    void _reset_scores();
    void _compare(
        Player* player1, Player* player2, int index1, int index2);


protected:
    int* _round_scores;


public:
    _Score_Chinese_Poker();
    _Score_Chinese_Poker(int seed, int num_players);
    ~_Score_Chinese_Poker();

    void score();
};


#endif 
