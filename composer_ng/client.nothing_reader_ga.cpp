#include "../card_cons.hpp"
#include "composer_no_ga.hpp"

#include <iostream>
#include <bitset>
#include <string>


const std::string FILE_NG = "../bins/nothing_ga.bin";
const std::string FILE_GAP = "../bins/pairs_ga.bin";
const std::string FILE_GAT = "../bins/trips_ga.bin";


int main()
{
    Composer_No_GA composer(FILE_GAT, FILE_GAP, FILE_NG);

    return 0;
}


