#include "hand_generator_ga.hpp"
#include "../card_cons.hpp"
#include <iostream>


void Hand_Generator_GA::_initialize()
{
    this->_pos[0] = cards::NUM_CARDS_PER_DECK;
    for (int i=1; i < cards::NUM_CARDS_PER_GAMMA; i++) {
        this->_pos[i] = this->_pos[i - 1] - 1;
    }
    this->_update();
}


void Hand_Generator_GA::_update()
{
    this->_hand = 
        (cards::TWO_OF_CLUBS << (this->_pos[0]-1) ) |
        (cards::TWO_OF_CLUBS << (this->_pos[1]-1) ) |
        (cards::TWO_OF_CLUBS << (this->_pos[2]-1) );
}


//Ugliest Function in the whole world that works perfectly
void Hand_Generator_GA::_next_hand()
{
    this->_pos[2] -= 1;
    if (!this->_pos[2]) {
        this->_pos[1] -= 1;
        if (this->_pos[1] - 1 == 0) {
            this->_pos[0] -= 1;
            if (this->_pos[0] - 2 == 0) {
                this->_initialize();
                return;
            }
            this->_pos[1] = this->_pos[0] - 1;
        }
        this->_pos[2] = this->_pos[1] - 1;
    }
    this->_update();
}
