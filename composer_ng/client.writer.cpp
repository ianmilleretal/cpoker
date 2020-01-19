#include "composer_no_ga.hpp"
#include <string>


const std::string trips = "../bins/trips_ga.bin";
const std::string pairs = "../bins/pairs_ga.bin";
const std::string no_ab = "../bins/nothing.bin";
const std::string no_ga = "../bins/nothing_ga.bin";

int main()
{
    Composer_No_GA composer(trips, pairs, no_ab, no_ga);

    return 0;
}
