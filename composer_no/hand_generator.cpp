#include "hand_generator.hpp"
#include "../card_cons.hpp"
#include <iostream>
#include <bitset>


void Hand_Generator::_initialize()
{
    this->_pos[0] = cards::NUM_KINDS * cards::NUM_SUITS;
    for (int i=1; i < cards::NUM_CARDS_ALPHA_BETA; i++) {
        this->_pos[i] = this->_pos[i - 1] - cards::NUM_SUITS;
        this->_cap[i] = 0;
    }
    this->_cap[0] = 0;
    this->_update();
}


void Hand_Generator::_update()
{
    this->_hand = 
        (cards::TWO_OF_CLUBS << (this->_pos[0]-1) ) |
        (cards::TWO_OF_CLUBS << (this->_pos[1]-1) ) |
        (cards::TWO_OF_CLUBS << (this->_pos[2]-1) ) |
        (cards::TWO_OF_CLUBS << (this->_pos[3]-1) ) |
        (cards::TWO_OF_CLUBS << (this->_pos[4]-1) );
}


//Ugliest Function in the whole world
void Hand_Generator::_next_hand()
{
    for (int i =0; i < 5; i++) {
        std::cout << this->_pos[i] << '\t';
    }
    std::cout << std::bitset<52>(this->_hand) << std::endl;
    if (this->_cap[cards::NUM_CARDS_ALPHA_BETA-1] == cards::NUM_SUITS-1) {
        this->_pos[cards::NUM_CARDS_ALPHA_BETA-1] += cards::NUM_SUITS-1;
        this->_cap[cards::NUM_CARDS_ALPHA_BETA-1] = 0;
        if (this->_cap[cards::NUM_CARDS_ALPHA_BETA-2] == cards::NUM_SUITS-1) {
            this->_pos[cards::NUM_CARDS_ALPHA_BETA-2] += cards::NUM_SUITS-1;
            this->_cap[cards::NUM_CARDS_ALPHA_BETA-2] = 0;
            if (this->_cap[cards::NUM_CARDS_ALPHA_BETA-3] == cards::NUM_SUITS-1) {
                this->_pos[cards::NUM_CARDS_ALPHA_BETA-3] += cards::NUM_SUITS-1;
                this->_cap[cards::NUM_CARDS_ALPHA_BETA-3] = 0;
                if (this->_cap[cards::NUM_CARDS_ALPHA_BETA-4] == cards::NUM_SUITS-1) {
                    this->_pos[cards::NUM_CARDS_ALPHA_BETA-4] += cards::NUM_SUITS-1;
                    this->_cap[cards::NUM_CARDS_ALPHA_BETA-4] = 0;
                    if (this->_cap[cards::NUM_CARDS_ALPHA_BETA-5] == cards::NUM_SUITS-1) {
                        this->_pos[cards::NUM_CARDS_ALPHA_BETA-5] += cards::NUM_SUITS-1;
                        this->_cap[cards::NUM_CARDS_ALPHA_BETA-5] = 0;
                        this->_drop();
                    } else {
                        this->_pos[cards::NUM_CARDS_ALPHA_BETA-5]--;
                        this->_cap[cards::NUM_CARDS_ALPHA_BETA-5]++;
                    }
                } else {
                    this->_pos[cards::NUM_CARDS_ALPHA_BETA-4]--;
                    this->_cap[cards::NUM_CARDS_ALPHA_BETA-4]++;
                }
            } else {
                this->_pos[cards::NUM_CARDS_ALPHA_BETA-3]--;
                this->_cap[cards::NUM_CARDS_ALPHA_BETA-3]++;
            }
        } else {
            this->_pos[cards::NUM_CARDS_ALPHA_BETA-2]--;
            this->_cap[cards::NUM_CARDS_ALPHA_BETA-2]++;
        }
    } else {
        this->_pos[cards::NUM_CARDS_ALPHA_BETA-1]--;
        this->_cap[cards::NUM_CARDS_ALPHA_BETA-1]++;
    }
    this->_update();
}


void Hand_Generator::_drop()
{
    std::cout << "dropped" << std::endl;
    this->_pos[cards::NUM_CARDS_ALPHA_BETA-1] -= cards::NUM_SUITS;
    if (this->_pos[cards::NUM_CARDS_ALPHA_BETA-1] == 0) {
        this->_pos[cards::NUM_CARDS_ALPHA_BETA-2] -= cards::NUM_SUITS;
        if (this->_pos[cards::NUM_CARDS_ALPHA_BETA-2] == cards::NUM_SUITS * 1) {
            this->_pos[cards::NUM_CARDS_ALPHA_BETA-3] -= cards::NUM_SUITS;
            if (this->_pos[cards::NUM_CARDS_ALPHA_BETA-3] == cards::NUM_SUITS * 2) {
                    this->_pos[cards::NUM_CARDS_ALPHA_BETA-4] -= cards::NUM_SUITS;
                    if (this->_pos[cards::NUM_CARDS_ALPHA_BETA-4] == cards::NUM_SUITS * 3) {
                        this->_pos[cards::NUM_CARDS_ALPHA_BETA-5] -= cards::NUM_SUITS;
                        if (this->_pos[cards::NUM_CARDS_ALPHA_BETA-5] == cards::NUM_SUITS * 4) {
                            this->_initialize();
                            this->_update();
                            std::cout << "complete" << std::endl;
                            return;
                    }
                    this->_pos[cards::NUM_CARDS_ALPHA_BETA-4] = this->_pos[cards::NUM_CARDS_ALPHA_BETA-5] - cards::NUM_SUITS;
                }
                this->_pos[cards::NUM_CARDS_ALPHA_BETA-3] = this->_pos[cards::NUM_CARDS_ALPHA_BETA-4] - cards::NUM_SUITS;
            }
            this->_pos[cards::NUM_CARDS_ALPHA_BETA-2] = this->_pos[cards::NUM_CARDS_ALPHA_BETA-3] - cards::NUM_SUITS;
        }
        this->_pos[cards::NUM_CARDS_ALPHA_BETA-1] = this->_pos[cards::NUM_CARDS_ALPHA_BETA-2] - cards::NUM_SUITS;
    }
}
