#ifndef THREE_CARD_COMPARE
#define THREE_CARD_COMPARE

#include "../card_cons.hpp"


class Three_Card_Compare
{
private:
    Three_Card_Compare();
    Three_Card_Compare(Three_Card_Compare &other);
    Three_Card_Compare& operator=(Three_Card_Compare &other);

    int _find_pair(Card_Flags cards);
    int _find_kicker(Card_Flags cards);


public:
    void compare_pairs(Card_Flags cards1,
        Card_Flags cards2, int &score1, int &score2);
};


#endif
