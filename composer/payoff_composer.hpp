#ifndef PAYOFF_COMPOSER
#define PAYOFF_COMPOSER


#include "_base_composer.hpp"
#include "_straight_flush_composer.hpp"
#include "_quad_composer.hpp"
#include "_flush_composer.hpp"
#include "_straight_composer.hpp"
#include "_kind_composer.hpp"


class Payoff_Composer : 
    public _Straight_Flush_Composer,
    public _Quad_Composer,
    public _Flush_Composer,
    public _Straight_Composer,
    public _Kind_Composer
{
public:
    Payoff_Composer() :
        _Straight_Flush_Composer(),
        _Quad_Composer(),
        _Flush_Composer(),
        _Straight_Composer(),
        _Kind_Composer() {}
};


#endif
