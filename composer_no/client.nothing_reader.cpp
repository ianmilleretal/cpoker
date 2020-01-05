#include "../card_cons.hpp"
#include "composer_no.hpp"

#include <iostream>
#include <bitset>
#include <string>


const std::string FILE_NO = "../bins/nothing.bin";
const std::string FILE_AB = "../bins/payoffs_ab.bin";


int main()
{
    Composer_No composer(FILE_AB, FILE_NO);

    return 0;
}


