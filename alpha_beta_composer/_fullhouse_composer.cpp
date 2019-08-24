#include "_fullhouse_composer.hpp"


void _Fullhouse_Composer::_reset_generators()
{
    this->_num_doubles = 0;
    this->_num_triples = 0;
    this->_shift1 = cards::ACE - 1;
    this->_shift2 = cards::KING - 1;
    this->_sequence2 = 0;
    this->_sequence3 = 0;
    this->_trip_kind = 0;
}


Card_Flags _Fullhouse_Composer::_generate_double()
{
    Card_Flags result;
    switch (this->_sequence2) {
        case 0 : result = 0x0C; break;
        case 1 : result = 0x0A; break;
        case 2 : result = 0x09; break;
        case 3 : result = 0x06; break;
        case 4 : result = 0x05; break;
        case 5 : result = 0x03;
            this->_sequence2 = -1;  
            break;
    }
    this->_sequence2++;
    return result; 
}


Card_Flags _Fullhouse_Composer::_generate_triple(int repeats)
{
    Card_Flags result;
    switch (this->_sequence3) {
        case 0 : result = 0x0E; break;
        case 1 : result = 0x0D; break;
        case 2 : result = 0x0B; break;
        case 3 : result = 0x07; break;
    }
    this->_trip_kind++;
    if (this->_trip_kind == repeats) {
        this->_sequence3 = (this->_sequence3 + 1) %
            cards::COMBO_TRIPS;
        this->_trip_kind = 0;
    }
    return result;
}


Payoff _Fullhouse_Composer::full_house()
{
    Payoff result(this->_generate_triple(cards::COMBO_DUBS) << 
        (this->_shift1 * cards::NUM_SUITS) |
        this->_generate_double() <<
        (this->_shift2 * cards::NUM_SUITS),
        this->_rank, cards::FULLHOUSE);

    this->_num_doubles++;
    if (this->_num_doubles == cards::COMBO_DUBS) {
        this->_num_doubles = 0;
        this->_num_triples++;
        if (this->_num_triples == cards::COMBO_TRIPS) 
            this->_next_rank();
    }
    return result;
}


void _Fullhouse_Composer::_next_rank()
{
    this->_num_triples = 0;
    this->_rank++;            
    this->_shift2--;
    if (this->_shift1 == this->_shift2) this->_shift2--;
    if (this->_shift2 < 0) {
        this->_shift2 = cards::ACE - 1;
        this->_shift1--;
        if (this->_shift1 < 0) {
            this->_is_finished = true;
            this->_reset_generators();
        }
    }
}

