#ifndef _FLUSH_COMPOSER_
#define _FLUSH_COMPOSER_


#include "../card_cons.hpp"
#include "_base_composer.hpp"


class _Flush_Composer : virtual public _Base_Composer
{
private:
    int _cards[cards::NUM_CARDS_PAYOFF_1];

    void _reorder();
    void _unstraighten();
    Card_Flags _generate_hand();
    void _skip_bottom_straight();


public:
    _Flush_Composer();

    Payoff flush();
};


#endif
