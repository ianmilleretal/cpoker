#ifndef TRIPS_GENERATOR_
#define TRIPS_GENERATOR_


#include "../card_cons.hpp"


class Trips_Generator
{
private:
    int _sequence;


protected:
    Card_Flags _current;


public:
    Trips_Generator();

    Card_Flags next();
    Card_Flags get()
        {return this->_current;}

    void reset();
};


#endif
