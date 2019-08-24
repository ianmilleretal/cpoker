#include <iostream>
#include <fstream>
#include <bitset>
#include "../card_cons.hpp"


template<typename T>
void read_bin(std::fstream &ifile, T* store);


const int PAIRS_SIZE = cards::NUM_KINDS *
                       cards::NUM_SUITS *
                       cards::COMBO_DUBS;
const int TRIPS_SIZE = cards::NUM_CARDS_PER_HAND * cards::COMBO_TRIPS;


int main()
{
    std::fstream d_file("../bins/3c_pairs.bin");
    std::fstream t_file("../bins/3c_trips.bin");
    Payoff pairs[PAIRS_SIZE];
    Payoff trips[TRIPS_SIZE];
    read_bin(d_file, pairs);
    read_bin(t_file, trips);

    for (int i=0; i < PAIRS_SIZE; i++) {
        std::cout << std::bitset<52>(pairs[i].first) << '\t';
        std::cout << pairs[i].second << std::endl;
    }
    for (int i=0; i < TRIPS_SIZE; i++) {
        std::cout << std::bitset<52>(trips[i].first) << '\t';
        std::cout << trips[i].second << std::endl;
    }
    return 0;
}


template<typename T>
void read_bin(std::fstream &ifile, T* store)
{
    T buffer;
    int i=0;
    while(ifile.peek() != EOF) {
        ifile.read((char*) &buffer, sizeof(buffer));
        store[i] = buffer;
        i++;
    }
}
