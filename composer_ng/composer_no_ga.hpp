#ifndef _COMPOSER_NO
#define _COMPOSER_NO


#include "hand_generator_ga.hpp"
#include "../card_cons.hpp"
#include <string>


class Composer_No_GA : public Hand_Generator_GA
{
protected:
    void _generate_payoffs_ng(Payoff* all, Payoff* nothing);

    Payoff* _payoffs_ng;


public:
    Composer_No_GA(
        const std::string payoff_trips_path,
        const std::string payoff_pairs_path,
        const std::string payoff_no_path,
        const std::string payoff_ng);

    Payoff* get_payoffs_no()
        {return this->_payoffs_ng;}
};


#endif
