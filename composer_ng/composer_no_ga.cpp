#include "composer_no_ga.hpp"
#include <iostream>
#include <fstream>
#include <bitset>


//The payoffs pair and higher total; (3*4*52) + (6*48*13) = 4368;  3796???
const int NUM_TOTAL_PAYOFFS_GA = 4368;

// 52 choose 3 - ((3*4*52) + (6*48*13))
const int NUM_TOTAL_PAYOFFS_NG = 17714;

//[trips G](3*4*52) + [pairs G](6*48*13) = size
const int NUM_PAYOFFS_TOTAL = 624+3744;

//[NO]
const int NUM_NOTHING_TOTAL = 1302540;

//[NG] = 52 choose 3 - 3744+624
const int NUM_NOTHING_GAMMA = 17732;

//[GA] = 
const int NUM_GAMMA_GENERATED = 18304;


int read_file(std::fstream &ifile, Payoff* payoffs, int i=0);


Composer_No_GA::Composer_No_GA(
    const std::string payoff_trips_path,
    const std::string payoff_pairs_path,
    const std::string payoff_no_path,
    const std::string payoff_ng_path
)
{
    //Allocate memory
    Payoff* all_payoffs = new Payoff[NUM_PAYOFFS_TOTAL];
    Payoff* all_nothing = new Payoff[NUM_NOTHING_TOTAL];
    this->_payoffs_ng = new Payoff[NUM_NOTHING_GAMMA];


    //Open streams
    std::fstream file_trips_ga(
        payoff_trips_path, std::ios_base::binary | std::ios_base::in);
    std::fstream file_pairs_ga(
        payoff_pairs_path, std::ios_base::binary | std::ios_base::in);
    std::fstream file_no(
        payoff_no_path, std::ios_base::binary | std::ios_base::in);
    std::fstream file_ng(
        payoff_ng_path, std::ios_base::binary | std::ios_base::out);


    //Read in; close
    int i = 0;
    i = read_file(file_trips_ga, all_payoffs, i);
    file_trips_ga.close();
    i = read_file(file_pairs_ga, all_payoffs, i);
    file_pairs_ga.close();
    read_file(file_no, all_nothing);
    file_no.close();


    //All Generation here
    this->_generate_payoffs_ng(all_payoffs, all_nothing);
    

    //Write out; close
    for (int i=0; i < NUM_TOTAL_PAYOFFS_NG; i++) {
        file_ng.write((char*) &this->_payoffs_ng[i], sizeof(this->_payoffs_ng[i]));
    }
    file_ng.close();

    //Deallocate
    delete [] all_payoffs;
    all_payoffs = NULL;
    delete [] all_nothing;
    all_nothing = NULL;
    delete [] this->_payoffs_ng;
    this->_payoffs_ng = NULL;
}


void Composer_No_GA::_generate_payoffs_ng(Payoff* all_payoffs, Payoff* all_nothing)
{
    for (int i=0; i < NUM_GAMMA_GENERATED; i++){
        Payoff make;
        Card_Flags hand = this->_get_hand();

        int j = 0;
        bool is_collision = false;
        do {
            if (hand & all_payoffs[j].first == hand)
                is_collision = true;
            j++;
        } while (!is_collision && (j < NUM_PAYOFFS_TOTAL));
        if (!is_collision) {
            make.first = hand;
            make.third = cards::NOTHING;
            for (int j=0; j < NUM_NOTHING_TOTAL; j++) {
                if ((hand & all_nothing[j].first) == hand) {
                    make.second = all_nothing[j].second;
                }
            }
            std::cout << std::bitset<52>(hand) << '\t' << make.second << '\t' << make.third << '\n';
            this->_payoffs_ng[i] = make;
        }
        this->_next_hand();
    }
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


#undef NEW_PAYOFF
