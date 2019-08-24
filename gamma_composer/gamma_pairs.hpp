#ifndef GAMMA_PAIRS_COMPOSER
#define GAMMA_PAIRS_COMPOSER


#include "../card_cons.hpp"
#include "../alpha_beta_composer/pair_generator.hpp"


class Three_Dubs_Composer
{
private:
    Pair_Generator _generator;
    int _kind;
    int _kicker;

    void _compose_set(int rank, int &index);
    void _compose_bottom_set(int rank, int &index);


protected:
    static const int _NUM_DUBS;
    static const int _BEG_RANGE;

    Payoff* _5c_dubs;
    Payoff _3c_dubs[cards::NUM_KINDS     *
                    (cards::NUM_KINDS-1) *
                    cards::NUM_SUITS     *
                    cards::COMBO_DUBS];


public:
    Three_Dubs_Composer(Payoff* full_list);

    void parse_dubs();

    Payoff* get()
        {return this->_3c_dubs;}
    int size()
        {return cards::NUM_KINDS     *
                (cards::NUM_KINDS-1) *
                cards::NUM_SUITS     *
                cards::COMBO_DUBS;}
};


#endif
