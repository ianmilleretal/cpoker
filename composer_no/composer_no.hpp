#ifndef _COMPOSER_NO
#define _COMPOSER_NO


#include "hand_generator.hpp"
#include "../card_cons.hpp"
#include <string>


class Composer_No : public Hand_Generator
{
private:
    void _capture_rank();
    void _update_rank();

    int _rank;
    int _capt[cards::NUM_CARDS_ALPHA_BETA];


protected:
    void _generate_payoffs_no();

    Payoff* _payoffs_ab;
    Payoff* _payoffs_no;


public:
    Composer_No(
        std::string payoff_ab_path, std::string payoff_no_path);
    ~Composer_No();

    Payoff* get_payoffs_no()
        {return this->_payoffs_no;}
};


#endif
