#ifndef GAMMA_TRIPS_COMPOSER
#define GAMMA_TRIPS_COMPOSER


#include "../card_cons.hpp"
#include "../alpha_beta_composer/trips_generator.hpp"


class Three_Trips_Composer
{
private:
    Trips_Generator _generator;
    int _kind;

    void _compose_set(int kind, int rank, int &index);

protected:
    static const int _NUM_TRIPS;
    static const int _BEG_RANGE;

    Payoff* _5c_trips;
    Payoff _3c_trips[cards::NUM_CARDS_PER_HAND * cards::COMBO_TRIPS];


public:
    Three_Trips_Composer(Payoff* full_list);

    void parse_trips();

    Payoff* get()
        {return this->_3c_trips;}
    int size()
        {return cards::NUM_CARDS_PER_HAND * cards::COMBO_TRIPS;}
};


#endif
