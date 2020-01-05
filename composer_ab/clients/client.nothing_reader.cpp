#include "../card_cons.hpp"
#include <iostream>
#include <bitset>
#include <fstream>
#include <string>


const int NUM_TOTAL_PAYOFFS = 1302540;
const std::string file_name = "nothing.bin";
Payoff payoffs[NUM_TOTAL_PAYOFFS];

int main()
{
    std::fstream ifile;
    ifile.open(file_name, std::ios_base::binary | std::ios_base::in);
    Payoff payoff;

    int i=0;
    while(ifile.peek() != EOF) {
        ifile.read((char*) &payoff, sizeof(payoff));
        payoffs[i] = payoff;
        std::cout << std::bitset<52>(payoff.first) << '\t' <<
        payoff.second << '\t' << payoff.third << '\t' << i << std::endl;
        i++;
    }
    ifile.close();

    return 0;
}




