#include "_score_chinese_poker.hpp"


_Score_Chinese_Poker::_Score_Chinese_Poker() :
    _Round_Chinese_Poker()
{
    this->_round_scores = new int[this->_num_players];
    this->_reset_scores();
}


_Score_Chinese_Poker::_Score_Chinese_Poker(int seed, int num_players): 
    _Round_Chinese_Poker(seed, num_players)
{
    this->_round_scores = new int[this->_num_players];
    this->_reset_scores();
}


_Score_Chinese_Poker::~_Score_Chinese_Poker()
{
    delete[] this->_round_scores;
}


void _Score_Chinese_Poker::_reset_scores()
{
    for (int i=0; i < this->_num_players; i++)
        this->_round_scores[i] = 0;
}


void _Score_Chinese_Poker::score()
{
    for (int i=0; i < this->_num_players - 1; i++) {
        for (int j=i+1; j < this->_num_players; j++) {
            this->_compare(
                this->_players[i], this->_players[j], i, j);
        }
    }
}


void _Score_Chinese_Poker::_compare(
    Player* player1, Player* player2, int index1, int index2)
{
    int score1 = 0;
    int score2 = 0;
/*
    Turnin turnin1 = player1->get_turnin();
    Turnin turnin2 = player2->get_turnin();
    if (turnin1.first->second  < turnin2.first->second)    score1++;
    if (turnin1.first->second  > turnin2.first->second)    score2++;
    if (turnin1.second->second < turnin2.second->second)   score1++;
    if (turnin1.second->second > turnin2.second->second)   score2++;
    if (turnin1.third->third == cards::PAIR &&
        turnin1.third->second == turnin2.third->second)
            int z =0;
//        Three_Card_Compare::compare(
//            turnin1.third->second, turnin2.third->second,
//            score1, score2);
    else {
        if (turnin1.third->second < turnin2.third->second) score1++;
        if (turnin1.third->second > turnin2.third->second) score2++;
    }
    if (score1 == 3) score1 = 6;
    if (score2 == 3) score2 = 6;
    player1->set_score(player1->get_score() + score1);
    player2->set_score(player2->get_score() + score2);
    this->_round_scores[index1] += score1;
    this->_round_scores[index2] += score2;
*/
}
