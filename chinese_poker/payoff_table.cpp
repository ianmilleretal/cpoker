#include "payoff_table.hpp"
#include "player.hpp"
#include "reader.hpp"
#include <forward_list>
#include <iostream>
#include <bitset>

const int PAYOFF_SIZE = 5;
const int NUM_KEYS = 3;


void Payoff_Table::initialize(const std::string &path)
{
    int hash1, hash2, hash3;
    Reader read(path);
    while (!read.peek_eof()) {
        read.one(this->_current);
        hash1 = this->_hash(this->_current.first);
        hash2 = this->_hash(hash1);
        hash3 = this->_hash(hash2);
        this->insert(hash1, hash2, hash3);
    }
}


void Payoff_Table::insert(int index1, int index2, int index3)
{
    auto last =
    this->_table[index1][index2][index3].before_begin();
    auto next = this->_table[index1][index2][index3].begin();
    while (next != this->_table[index1][index2][index3].end())
        next++;
    this->_table[index1][index2][index3].insert_after(
        last, this->_current);
}


void Payoff_Table::lookup(Player &player)
{
    int num_key_pairs = player.get_hand().count();
    int num_with_pays = num_key_pairs - (PAYOFF_SIZE - 1);
    int high = this->_hash(player.get_cards() );

//    std::cout << std::bitset<64>(this->_cards) << std::endl;
    for (int i=0; i < num_with_pays; i++) {
        int next = this->_hash(high);
        for (int j=0; j < num_with_pays - i; j++) {
            int last = this->_hash(next);
            for (int k=0; k < num_with_pays - i - j; k++) {
//                std::cout << high << '\t' << next << '\t' << last << std::endl;
                this->_award(player, high, next, last);
                last = this->_hash(last);
            }
            next = this->_hash(next);
        }
        high = this->_hash(high);
    }
//    exit(2);
}


void Payoff_Table::_award(
    Player &player, int key1, int key2, int key3)
{
    bool is_found = false;
    auto it = this->_table[key1][key2][key3].begin();
    while (it != this->_table[key1][key2][key3].end()) {
        if ( (this->_cards & it->first) == it->first) {
            Payoff* p = &(*it);
            player.add_payoff(p);
        }
        it++;
    }
}


int Payoff_Table::_hash(int max)
{
    int result = -1;
    Card_Flags card = 1;
    for (int i=0; i < max; i++) {
        if (card & this->_cards) {
            result = i;
        }
        card <<= 1;
    }
    return result;
}


int Payoff_Table::_hash(Card_Flags cards)
{
    this->_cards = cards;
    return this->_hash(cards::NUM_CARDS_PER_DECK);
}
