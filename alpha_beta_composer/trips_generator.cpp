#include "trips_generator.hpp"


Trips_Generator::Trips_Generator() : 
    _sequence(0)
{
    this->next();
}



Card_Flags Trips_Generator::next()
{
    switch (this->_sequence) {
        case 0 : this->_current = 0x0E; break;
        case 1 : this->_current = 0x0D; break;
        case 2 : this->_current = 0x0B; break;
        case 3 : this->_current = 0x07; break;
    }
    this->_sequence++;
    if (this->_sequence > 3) this->_sequence = 0;

    return this->_current;
}

void Trips_Generator::reset()
{
    this->_sequence = 0;
}
