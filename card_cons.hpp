#ifndef HEADERS_CARDS_
#define HEADERS_CARDS_


#include <cstdint>
#include <random>
#include <forward_list>
#include "utils/tripartite.hpp"


typedef uint_fast64_t Card_Flags;
typedef uint_fast8_t Short_U;
typedef std::mt19937 Random;
typedef Tripartite<Card_Flags, int, int> Payoff;
typedef std::forward_list<Payoff> Payoff_List;
typedef Payoff_List ::iterator Payoff_List_It;
typedef Tripartite<Payoff*, Payoff*, Payoff*> Turnin;


namespace cards
{
    const int SENTINEL = -1;
    const int NUM_PAYOFF_TYPES = 2;
    const int NUM_CARDS_PER_DECK = 52;
    const int NUM_CARDS_PER_HAND = 13;
    const int NUM_CARDS_ALPHA_BETA = 5;
    const int NUM_CARDS_PER_GAMMA = 3;
    const int NUM_CARDS_PAYOFF_1 = 5;
    const int NUM_CARDS_PAYOFF_2 = 5;
    const int NUM_CARDS_PAYOFF_3 = 3;
    const int NUM_CARDS_PER_PAIR = 2;

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

    const char STRAIGHT_FLUSH = 0;
    const char FOUR_OF_A_KIND = 1;
    const char FULLHOUSE = 2;
    const char FLUSH = 3;
    const char STRAIGHT = 4;
    const char THREE_OF_A_KIND = 5;
    const char TWO_PAIR = 6;
    const char PAIR = 7;
    const char NOTHING = 8;

    const int NUM_SUITS = 4;
    const int NUM_KINDS = 13;
    const int COMBO_TRIPS = 4;
    const int COMBO_DUBS = 6;

    const Card_Flags ACE_OF_SPADES = 0x8000000000000;
    const Card_Flags TWO_OF_CLUBS = 1;
}


#endif
