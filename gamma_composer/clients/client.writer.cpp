#include "../card_cons.hpp"
#include "three_trips_composer.hpp"
#include "three_dubs_composer.hpp"
#include <iostream>
#include <bitset>
#include <utility>
#include <fstream>
#include <string>


const int NUM_TOTAL_PAYOFFS = 1296420;
const std::string I_FILE_NAME = "payoffs.bin";
const std::string D_FILE_NAME = "3c_dubs.bin";
const std::string T_FILE_NAME = "3c_trips.bin";
Payoff payoffs[NUM_TOTAL_PAYOFFS];


void grab_payoffs(std::string file_name);


template<typename T>
void write_bin(const std::string &filename, const T* input, int size);


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
