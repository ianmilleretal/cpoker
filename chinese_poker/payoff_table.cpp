#include "payoff_table.hpp"
#include "player.hpp"
#include "reader.hpp"
#include <forward_list>


bool Payoff_Table::is_initialized = false;
Payoff Payoff_Table::current;
Payoff_List
    Payoff_Table::_table
        [cards::NUM_CARDS_PER_DECK]
        [cards::NUM_CARDS_PER_DECK]
        [cards::NUM_CARDS_PER_DECK];
Card_Flags Payoff_Table::cards = 0;


const int PAYOFF_SIZE = 5;
const int NUM_KEYS = 2;


#include <iostream>
#include <bitset>


int __d_count=0;


void Payoff_Table::initialize(const std::string &path)
{
    int hash1, hash2, hash3;
    Reader read(path);
    int count = 0;
    while (!read.peek_eof()) {
        read.one(Payoff_Table::current);
        hash1 = Payoff_Table::hash(Payoff_Table::current.first);
        hash2 = Payoff_Table::hash(hash1);
        hash3 = Payoff_Table::hash(hash2);
        Payoff_Table::insert(hash1, hash2, hash3);
        count++;
    }
    std::cout << "Inserted: " << __d_count << std::endl;
    std::cout << "Read:     " << count << std::endl;
}


void Payoff_Table::insert(int index1, int index2, int index3)
{
    auto last =
    Payoff_Table::_table[index1][index2][index3].before_begin();
    auto next = Payoff_Table::_table[index1][index2][index3].begin();
    bool collision = false;
    while (next != Payoff_Table::_table[index1][index2][index3].end()){
        if (next->first == Payoff_Table::current.first) {
            std::cout << "collision!:" << std::endl;
            std::cout << std::bitset<52>(Payoff_Table::current.first) << std::endl;
            std::cout << std::bitset<52>(next->first) << std::endl;
            collision = true;
        }
        next++;
    }
    if (!collision) {
        Payoff_Table::_table[index1][index2][index3].insert_after(
            last, Payoff_Table::current);
        __d_count++;
    } else {
        std::cout << std::bitset<52>(Payoff_Table::current.first) <<std::endl;
    }
}


#include <iostream>
#include <bitset>
void Payoff_Table::lookup(Player &player)
{
    int num_key_pairs = player.get_hand().count();
    int num_with_pays = num_key_pairs - PAYOFF_SIZE - NUM_KEYS + 3;
    int high = Payoff_Table::hash(player.get_cards() );

    for (int i=0; i < num_with_pays; i++) {
        int next = Payoff_Table::hash(high);
        for (int j=0; j < num_key_pairs - i - 1; j++) {
            int last = Payoff_Table::hash(next);
            for (int k=0; k < num_key_pairs - i - j - 2; k++) {
                Payoff_Table::_award(player, high, next, last);
                last = Payoff_Table::hash(last);
            }
            next = Payoff_Table::hash(next);
        }
        high = Payoff_Table::hash(high);
    }
}


void Payoff_Table::_award(
    Player &player, int key1, int key2, int key3)
{
    auto it = Payoff_Table::_table[key1][key2][key3].begin();
    while (it != Payoff_Table::_table[key1][key2][key3].end()) {
        if ( (Payoff_Table::cards & it->first) == it->first) {
            Payoff* p = &(*it);
            player.add_payoff(p);
        }
        it++;
    }
}


int Payoff_Table::hash(int max)
{
    int result = -1;
    Card_Flags card = 1;
    for (int i=0; i < max; i++) {
        if (card & Payoff_Table::cards) {
            result = i;
        }
        card <<= 1;
    }
    return result;
}


int Payoff_Table::hash(Card_Flags cards)
{
    Payoff_Table::cards = cards;
    return Payoff_Table::hash(cards::NUM_CARDS_PER_DECK);
}
