#ifndef HEADERS_CARDS_
#define HEADERS_CARDS_


#include <cstdint>
#include <random>
#include <forward_list>
#include <utility>


typedef uint_fast64_t Card_Flags;
typedef uint_fast8_t Short_U;
typedef std::mt19937 Random;
typedef std::forward_list<std::pair<Card_Flags, int>> Payoff_List;
typedef Payoff_List ::iterator Payoff_List_It;
typedef std::pair<Card_Flags, int> Payoff;

namespace cards
{
    const int NUM_PAYOFF_TYPES = 2;
    const int NUM_CARDS_PER_DECK = 52;
    const int NUM_CARDS_PER_HAND = 13;
    const int NUM_CARDS_PAYOFF_1 = 5;
    const int NUM_CARDS_PAYOFF_2 = 5;
    const int NUM_CARDS_PAYOFF_3 = 3;

    const int ACE = 13;
    const int KING = 12;
    const int QUEEN = 11;
    const int JACK = 10;
    const int TEN = 9;
    const int NINE = 8;
    const int EIGHT = 7;
    const int SEVEN = 6;
    const int SIX = 5;
    const int FIVE = 4;
    const int FOUR = 3;
    const int THREE = 2;
    const int TWO = 1;

    const int NUM_SUITS = 4;
    const int NUM_KINDS = 13;
    const int COMBO_TRIPS = 4;
    const int COMBO_DUBS = 6;
}


#endif
