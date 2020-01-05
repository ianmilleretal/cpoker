#include "composer_no.hpp"
#include <iostream>
#include <fstream>
#include <bitset>


const int NUM_TOTAL_PAYOFFS_AB = 1296420;
const int NUM_TOTAL_PAYOFFS_NO = 1302540;
const int C5_13_X_4POWER5 = 1317888;
const int FIRST_RANK_NO = 5326;
#define NEW_PAYOFF Payoff(hand, this->_rank, cards::NOTHING);


Composer_No::Composer_No(
    std::string payoff_ab_path,
    std::string payoff_no_path
)
{
    this->_payoffs_ab = new Payoff[NUM_TOTAL_PAYOFFS_AB];
    this->_payoffs_no = new Payoff[NUM_TOTAL_PAYOFFS_NO];
    std::fstream file_no(
        payoff_no_path, std::ios_base::binary | std::ios_base::out);
    std::fstream file_ab(
        payoff_ab_path, std::ios_base::binary | std::ios_base::in);

    Payoff buffer;
    int i = 0;
    while(file_ab.peek() != EOF) {
        file_ab.read(
            (char*) &buffer, sizeof(buffer));
        this->_payoffs_ab[i] = buffer;
        i++;
    }
    file_ab.close();

    this->_generate_payoffs_no();
    for (int j=0; j < NUM_TOTAL_PAYOFFS_NO; j++) {
        file_no.write((char*) &this->_payoffs_no[j], sizeof(buffer));
    }

    file_no.close();
}


Composer_No::~Composer_No()
{
    delete [] this->_payoffs_no;
    this->_payoffs_no = NULL;
    delete [] this->_payoffs_ab;
    this->_payoffs_ab = NULL;
}


void Composer_No::_generate_payoffs_no()
{

    bool is_captured = false;
    int nothings = 0;
    this->_rank = FIRST_RANK_NO;
    for (int i=0; i < C5_13_X_4POWER5;i++){
        Card_Flags hand = this->_get_hand();
        if (i > (NUM_TOTAL_PAYOFFS_NO+NUM_TOTAL_PAYOFFS_AB - 100))
            std::cout << std::bitset<52>(hand) << std::endl;
        bool is_collision = false;
        int j =0;
        do {
            if (this->_payoffs_ab[j].first == hand) {
                is_collision = true;
            }
            j++;
        } while (!is_collision && j < NUM_TOTAL_PAYOFFS_AB);
        if (!is_collision) {
            if (!is_captured) {
                this->_payoffs_no[nothings] = NEW_PAYOFF;
                this->_capture_rank();
                is_captured = true;
            } else {
                this->_update_rank();
                this->_payoffs_no[nothings] = NEW_PAYOFF;
            }
            nothings++;
        }
        this->_next_hand();
        if (i % 1000 == 0) std::cout << i << std::endl;
    }
    std::cout << std::bitset<52>(this->_get_hand()) << std::endl;
}

void Composer_No::_capture_rank()
{
    for (int i=0; i < cards::NUM_CARDS_ALPHA_BETA; i++)
        this->_capt[i] = this->_pos[i];
}


void Composer_No::_update_rank()
{
    bool is_next_rank;
    for (int i=0; i < cards::NUM_CARDS_ALPHA_BETA; i++) {
        is_next_rank = false;
        if ((this->_pos[i]-1) / cards::NUM_SUITS !=
            (this->_capt[i]-1) / cards::NUM_SUITS )
        {
            is_next_rank = true;
        }
    }
    if (is_next_rank) {
        this->_rank++;
        this->_capture_rank();
   }
}


#undef NEW_PAYOFF
