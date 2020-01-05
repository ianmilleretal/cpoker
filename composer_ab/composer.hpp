#ifndef COMPOSER_
#define COMPOSER_

#include "_composer_straight_flush.hpp"
#include "_composer_straight.hpp"
#include "_composer_flush.hpp"
#include "_composer_base.hpp"
#include "_composer_quad.hpp"
#include "_composer_kind.hpp"


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
