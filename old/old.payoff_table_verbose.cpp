#include <iostream>
#include <bitset>
#include <iomanip>
#include "../card_cons.hpp"
#include "reader.hpp"


void print_list_sizes(int list_sizes[][cards::NUM_CARDS_PER_DECK]);


void Payoff_Table::initialize_verbose(const std::string &path)
{
    int hash1;
    int hash2;
    Read read(path);
    int list_sizes[cards::NUM_CARDS_PER_DECK][
        cards::NUM_CARDS_PER_DECK] = {};
    std::cout <<
        "Hashes\t\t|\t\tBits\t\t\t      | Rank  | Size |  Total"<<
        std::endl;
    int i =0;
    while (!read.peek_eof()) {
        read.one(Payoff_Table::current);
        hash1 = Payoff_Table::hash(Payoff_Table::current.first);
        hash2 = Payoff_Table::hash(hash1);
        std::cout << hash1 << ' ' << hash2 << '\t';
        Payoff_Table::insert(hash1, hash2);
        list_sizes[hash1][hash2]++;
        std::cout << list_sizes[hash1][hash2] << '\t';
        std::cout << i << std::endl;
        i++;
    }
    std::cout <<
        "Hashes\t\t|\t\tBits\t\t\t      | Rank  | Size |  Total" <<
        std::endl << std::endl;
    print_list_sizes(list_sizes);

}


void print_list_sizes(int list_sizes[][cards::NUM_CARDS_PER_DECK])
{
#define PRINT(a, b, c, w) std::cout << std::left << std::setw(w) << \
    a << std::setw(w) << b << std::setw(w) <<  c << std::endl

    const int WS = 15;
    PRINT("Hash1", "Hash2", "Size", WS);
    for (int i=0; i<cards::NUM_CARDS_PER_DECK; i++) {
        for (int j=0; j < cards::NUM_CARDS_PER_DECK; j++) {
            if (j < i) {
                PRINT(i, j, list_sizes[i][j], WS);
            }
        }
    }
#undef PRINT
}
