#include "../card_cons.hpp"
#include <iostream>
#include <bitset>


void get_places(Card_Flags cards, int &one, int &two, int &three);
int rank(Card_Flags cards);


int main()
{
    int previous = -1;
    int current = 0;    

    Card_Flags card1 = cards::ACE_OF_SPADES;
    Card_Flags card2 = cards::ACE_OF_SPADES >> 1 * cards::NUM_SUITS;
    Card_Flags card3 = cards::ACE_OF_SPADES >> 2 * cards::NUM_SUITS;
    for (int i = 0; i < 150; i++) {
        Card_Flags cards = card1 | card2 | card3;
        current = rank(cards);
//        if (current != previous + 1)
//            exit(1);
        previous = current;
        card3 >>= cards::NUM_SUITS;
        if (!card3) {
            card2 >>= cards::NUM_SUITS;
            card3 = card2 >> cards::NUM_SUITS;
        }
        if (card2 <= 0x8) {
            card1 >>= cards::NUM_SUITS;
            card2 = card1 >> cards::NUM_SUITS;
            card3 = card2 >> cards::NUM_SUITS;
            cards = card1 | card2 | card3;
        }
    }
    return 0;
}


void get_places(Card_Flags cards, int &one, int &two, int &three)
{
    int count = 0;
    int num_finished = 0;
    Card_Flags card = cards::ACE_OF_SPADES;
    int start = cards::NUM_CARDS_PER_DECK - 1;
    do {
        if (card & cards) {
            switch(num_finished) {
                case 0 : one = count   / cards::NUM_SUITS; break;
                case 1 : two = count   / cards::NUM_SUITS; break;
                case 2 : three = count / cards::NUM_SUITS; break;
            }
            num_finished++;
        }
        count++;
        card >>= 1;
    } while (!(num_finished == 3));
}


int rank(Card_Flags cards)
{
    int one, two, three;
    get_places(cards, one, two, three);
    std::cout << std::bitset<52>(cards) << std::endl;
    std::cout << one << ' ' <<  two << ' ' << three << std::endl;

    int result = three - two - 1;
    result += (two - one - 1) * (cards::NUM_KINDS-1);
    for (int i = 0; i < two; i++)
        result -= i;
    if (one)
        std::cout << "result " << result << std::endl;
    result += one * (cards::NUM_KINDS-1) * (cards::NUM_KINDS-1) + 1;
    for (int i = 0; i < one; i++) {
        for (int j = 0; j < cards::NUM_KINDS; j++)
            result -= j;
    }
    std::cout << result << std::endl << std::endl;
    return result;
}
