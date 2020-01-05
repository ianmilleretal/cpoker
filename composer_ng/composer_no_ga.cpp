#include "composer_no_ga.hpp"
#include <iostream>
#include <fstream>
#include <bitset>


const int NUM_TOTAL_PAYOFFS_GA = 3796;
const int NUM_TOTAL_PAYOFFS_NG = 18305;
#define NEW_PAYOFF Payoff(hand, -1, cards::NOTHING);


int read_file(std::fstream &ifile, Payoff* payoffs, int i=0);


Composer_No_GA::Composer_No_GA(
    std::string payoff_trips_path,
    std::string payoff_pairs_path,
    std::string payoff_ab_path,
    std::string payoff_ng_path
)
{
    this->_payoffs_ga = new Payoff[NUM_TOTAL_PAYOFFS_GA];
    this->_payoffs_ng = new Payoff[NUM_TOTAL_PAYOFFS_NG];
    this->_payoffs_ab = new Payoff[NUM_TOTAL_PAYOFFS_AB];
    std::fstream file_trips_ga(
        payoff_trips_path, std::ios_base::binary | std::ios_base::in);
    std::fstream file_pairs_ga(
        payoff_pairs_path, std::ios_base::binary | std::ios_base::in);
    std::fstream file_ab(
        payoff_ab_path, std::ios_base::binary | std::ios_base::in);
    std::fstream file_ng(
        payoff_ng_path, std::ios_base::binary | std::ios_base::out);

    read_file(file_ab, this->_payoffs_ab)
    int i = read_file(file_trips_ga, this->_payoffs_ga);
    file_trips_ga.close();
    int o = read_file(file_pairs_ga, this->_payoffs_ga, i);
    file_pairs_ga.close();
    std::cout << (o) << std::endl;

    this->_generate_payoffs_ng();
    for (int i=0; i < NUM_TOTAL_PAYOFFS_NG; i++) {
        file_ng.write((char*) &this->_payoffs_ng[i], sizeof(this->_payoffs_ng[i]));
    }
    file_ng.close();
}


Composer_No_Ga::_rank()
{
    for (int i=0; i < NUM_TOTAL_PAYOFFS_NG; i++) {
        int last_rank = 0;
        for (int j=0; j < NUM_TOTAL_PAYOFFS_AB; i++) {
            if (this->_payoffs_ng[i].first & this->_payoffs_ab[j].first ==
                this->_payoffs_ng[i].first)
                last_rank = this->_payoffs_ab.second;
        }
        this->_payoffs_ng[i].second = last_rank;
        this->_payoffs_ng[i].third = ;
    }
}


Composer_No_GA::~Composer_No_GA()
{
    delete [] this->_payoffs_ng;
    this->_payoffs_ng = NULL;
    delete [] this->_payoffs_ga;
    this->_payoffs_ga = NULL;
}


int read_file(std::fstream &ifile, Payoff* payoffs, int i)
{
    Payoff buffer;
    while(ifile.peek() != EOF) {
        ifile.read(
            (char*) &buffer, sizeof(buffer));
        payoffs[i] = buffer;
        i++;
    }
    return i;
}


void Composer_No_GA::_generate_payoffs_ng()
{
    int nothings = 0;
    for (int i=0; i < NUM_TOTAL_PAYOFFS_GA + NUM_TOTAL_PAYOFFS_NG; i++){
        Card_Flags hand = this->_get_hand();
        bool is_collision = false;
        int j =0;
        do {
            if (this->_payoffs_ga[j].first == hand) is_collision = true;
            j++;
        } while (!is_collision && j < NUM_TOTAL_PAYOFFS_GA);
        if (!is_collision) {
            this->_payoffs_ng[nothings] = NEW_PAYOFF;
            nothings++;
        }
        this->_next_hand();
    }
    std::cout << nothings << std::endl;
}


#undef NEW_PAYOFF
