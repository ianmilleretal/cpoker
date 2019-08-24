#include "pair_generator.hpp"

Card_Flags Pair_Generator::next()
{
    Card_Flags result;
    switch (this->_sequence) {
        case 0 : result = 0x0C; break;
        case 1 : result = 0x0A; break;
        case 2 : result = 0x09; break;
        case 3 : result = 0x06; break;
        case 4 : result = 0x05; break;
        case 5 : result = 0x03;
            this->_sequence = -1;  
            break;
    }
    this->_sequence++;
    return result; 
}
