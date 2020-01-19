#include "hand_generator_ga.hpp"
#include "../card_cons.hpp"
#include <iostream>
#include <bitset>


void Hand_Generator_GA::_initialize()
{
    this->_pos[0] = cards::NUM_CARDS_PER_DECK;
    for (int i=1; i < cards::NUM_CARDS_PER_GAMMA; i++) {
        this->_pos[i] = this->_pos[i - 1] - cards::NUM_SUITS;
        this->_cap[i] = 0;
    }
    this->_cap[0] = 0;
    this->_update();
}


void Hand_Generator_GA::_update()
{
    this->_hand = 
        (cards::TWO_OF_CLUBS << (this->_pos[0]-1) ) |
        (cards::TWO_OF_CLUBS << (this->_pos[1]-1) ) |
        (cards::TWO_OF_CLUBS << (this->_pos[2]-1) );
}


//Ugliest Function in the whole world
void Hand_Generator_GA::_next_hand()
{
//    for (int i =0; i < 3; i++) {
//        std::cout << this->_pos[i] << '\t';
//    }
//    std::cout << std::bitset<52>(this->_hand) << std::endl;
    if (this->_cap[cards::NUM_CARDS_PER_GAMMA-1] == cards::NUM_SUITS-1) {
        this->_pos[cards::NUM_CARDS_PER_GAMMA-1] += cards::NUM_SUITS-1;
        this->_cap[cards::NUM_CARDS_PER_GAMMA-1] = 0;
        if (this->_cap[cards::NUM_CARDS_PER_GAMMA-2] == cards::NUM_SUITS-1) {
            this->_pos[cards::NUM_CARDS_PER_GAMMA-2] += cards::NUM_SUITS-1;
            this->_cap[cards::NUM_CARDS_PER_GAMMA-2] = 0;
            if (this->_cap[cards::NUM_CARDS_PER_GAMMA-3] == cards::NUM_SUITS-1) {
                this->_pos[cards::NUM_CARDS_PER_GAMMA-3] += cards::NUM_SUITS-1;
                this->_cap[cards::NUM_CARDS_PER_GAMMA-3] = 0;
                this->_drop();
            } else {
                this->_pos[cards::NUM_CARDS_PER_GAMMA-3]--;
                this->_cap[cards::NUM_CARDS_PER_GAMMA-3]++;
            }
        } else {
            this->_pos[cards::NUM_CARDS_PER_GAMMA-2]--;
            this->_cap[cards::NUM_CARDS_PER_GAMMA-2]++;
        }
    } else {
        this->_pos[cards::NUM_CARDS_PER_GAMMA-1]--;
        this->_cap[cards::NUM_CARDS_PER_GAMMA-1]++;
    }
    this->_update();
}


void Hand_Generator_GA::_drop()
{
//    std::cout << "dropped" << std::endl;
    this->_pos[cards::NUM_CARDS_PER_GAMMA-1] -= cards::NUM_SUITS;
    if (this->_pos[cards::NUM_CARDS_PER_GAMMA-1] == 0) {
        this->_pos[cards::NUM_CARDS_PER_GAMMA-2] -= cards::NUM_SUITS;
        if (this->_pos[cards::NUM_CARDS_PER_GAMMA-2] == cards::NUM_SUITS * 1) {
            this->_pos[cards::NUM_CARDS_PER_GAMMA-3] -= cards::NUM_SUITS;
            if (this->_pos[cards::NUM_CARDS_PER_GAMMA-3] == cards::NUM_SUITS * 2) {
                this->_initialize();
                this->_update();
//                std::cout << "complete" << std::endl;
                return;
            }
            this->_pos[cards::NUM_CARDS_PER_GAMMA-2] = this->_pos[cards::NUM_CARDS_PER_GAMMA-3] - cards::NUM_SUITS;
        }
        this->_pos[cards::NUM_CARDS_PER_GAMMA-1] = this->_pos[cards::NUM_CARDS_PER_GAMMA-2] - cards::NUM_SUITS;
    }
}
