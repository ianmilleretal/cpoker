#include "../card_cons.hpp"
#include "gamma_trips.hpp"
#include "gamma_pairs.hpp"
#include <iostream>
#include <bitset>
#include <utility>
#include <fstream>
#include <string>


const int NUM_TOTAL_PAYOFFS = 1296420;
const std::string I_FILE_NAME = "../bins/payoffs.bin";
const std::string D_FILE_NAME = "../bins/gamma_pairs.bin";
const std::string T_FILE_NAME = "../bins/gamma_trips.bin";
Payoff payoffs[NUM_TOTAL_PAYOFFS];


void grab_payoffs(std::string file_name);


template<typename T>
void write_bin(const std::string &filename, const T* input, int size);
template<typename T>
void read_bin(std::fstream &ifile, T* store);


int main()
{
    Three_Dubs_Composer d_composer(payoffs);
    Three_Trips_Composer t_composer(payoffs);

    grab_payoffs(I_FILE_NAME);

    d_composer.parse_dubs();
    t_composer.parse_trips();

    write_bin(D_FILE_NAME, d_composer.get(), d_composer.size());
    write_bin(T_FILE_NAME, t_composer.get(), t_composer.size());

    return 0;
}


void grab_payoffs(std::string file_name)
{
    std::fstream ifile;
    ifile.open(file_name, std::ios_base::binary | std::ios_base::in);

    //Payoffs declared off stack to account for its large size
    read_bin(ifile, payoffs);
    ifile.close();
}


#include <iostream>
#include <bitset>
template<typename T>
void write_bin(const std::string &filename, const T* input, int size)
{
    std::ofstream ofile;
    ofile.open(filename, std::ios_base::binary | std::ios_base::out);
    
    for (int i=0; i < size; i++) {
        T element = input[i];
        ofile.write((char*) &element, sizeof(element));
    }
    ofile.close();
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
