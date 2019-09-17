#ifndef PAY_OFF_TABLE_
#define PAY_OFF_TABLE_


#include "../card_cons.hpp"
#include "hand.hpp"
#include "player.hpp"
#include <forward_list>


class Payoff_Table
{
private:
    Payoff_Table();
    Payoff_Table(Payoff_Table &other);
    Payoff_Table& operator=(Payoff_Table &other);
    static void _award(Player &player, int key1, int key2, int key3);
    
    static Payoff_List _table
        [cards::NUM_CARDS_PER_DECK]
        [cards::NUM_CARDS_PER_DECK]
        [cards::NUM_CARDS_PER_DECK];
    static bool is_initialized;

public:
    static void initialize(const std::string &path);
    static void initialize_verbose(const std::string &path);
    static int hash(int max);
    static int hash(Card_Flags cards);
    static void insert(int index1, int index2, int index3);
    static void lookup(Player &player);

    static Payoff current;
    static Card_Flags cards;
};


#endif
