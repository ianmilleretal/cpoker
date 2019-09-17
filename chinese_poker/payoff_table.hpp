#ifndef PAY_OFF_TABLE_
#define PAY_OFF_TABLE_


#include "../card_cons.hpp"
#include "hand.hpp"
#include "player.hpp"
#include <forward_list>


class Payoff_Table
{
private:
    void _award(Player &player, int key1, int key2, int key3);
    int _hash(int max);
    int _hash(Card_Flags cards);


protected:
    Payoff _current;
    Card_Flags _cards;
    bool _is_initialized;

    Payoff_List _table
        [cards::NUM_CARDS_PER_DECK]
        [cards::NUM_CARDS_PER_DECK]
        [cards::NUM_CARDS_PER_DECK];


public:
    Payoff_Table() :
        _cards(0),
        _is_initialized(false) {}
    void initialize(const std::string &path);
    void insert(int index1, int index2, int index3);
    void lookup(Player &player);


};


#endif
