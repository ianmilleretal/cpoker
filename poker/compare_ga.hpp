#ifndef THREE_CARD_COMPARE
#define THREE_CARD_COMPARE

#include "../card_cons.hpp"


class Compare_GA
{
private:
    Compare_GA();
    Compare_GA(Compare_GA &other);
    Compare_GA& operator=(Compare_GA &other);

    int _find_pair(Card_Flags cards);
    int _find_kicker(Card_Flags cards);


public:
    void compare_pairs(Card_Flags cards1,
        Card_Flags cards2, int &score1, int &score2);
};


#endif
