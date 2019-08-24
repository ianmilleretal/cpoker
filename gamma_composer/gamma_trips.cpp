#include "gamma_trips.hpp"
#include "../card_cons.hpp"
#include "../alpha_beta_composer/trips_generator.hpp"


//sum of num of SF, 4-o-a-kind, full house, flush, and straights
const int Three_Trips_Composer::_BEG_RANGE = 
    40 + 624 + 3744 + 5108 + 10200;
const int Three_Trips_Composer::_NUM_TRIPS = 54912;


static bool has_trips(Card_Flags cards, int kind)
{
    Card_Flags flag = 0x01;
    flag <<= (kind * cards::NUM_SUITS);

    int num_bits = 0;
    for (int i=0; i < cards::NUM_SUITS; i++) {
        if (flag & cards) num_bits++;
        flag <<= 1;
    }
    return num_bits == 3;
}


Three_Trips_Composer::Three_Trips_Composer(Payoff* all_payoffs)
{
    this->_5c_trips = all_payoffs + this->_BEG_RANGE;
    this->_kind = cards::ACE - 1;
}


void Three_Trips_Composer::parse_trips()
{
    int rank;
    int index=0;
    for (int i=1; i < this->_NUM_TRIPS+1; i++) {
        if ( !(has_trips(this->_5c_trips[i].first, this->_kind) ) ) {
            rank = this->_5c_trips[i-1].second;
            this->_compose_set(this->_kind, rank, index);
            this->_kind--;
        }
    }
}


void Three_Trips_Composer::_compose_set(int kind, int rank, int &index)
{
    Trips_Generator generator;
    Card_Flags cards;
    for (int i=0; i < cards::COMBO_TRIPS; i++) {
        cards = generator.next() << (kind * cards::NUM_SUITS);
        this->_3c_trips[index] = Payoff(
            cards, rank, cards::THREE_OF_A_KIND);
        index++;
    }
}
