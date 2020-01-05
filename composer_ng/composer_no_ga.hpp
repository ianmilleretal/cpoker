#ifndef _COMPOSER_NO
#define _COMPOSER_NO


#include "hand_generator_ga.hpp"
#include "../card_cons.hpp"
#include <string>


class Composer_No_GA : public Hand_Generator_GA
{
protected:
    void _generate_payoffs_ng();

    Payoff* _payoffs_ga;
    Payoff* _payoffs_ng;


public:
    Composer_No_GA(
        std::string payoff_trips_path,
        std::string payoff_pairs_path,
        std::string payoff_no_path);

    Payoff* get_payoffs_no()
        {return this->_payoffs_ng;}
};


#endif
