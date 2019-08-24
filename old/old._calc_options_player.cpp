#include "_calc_options_player.hpp"
#include "../utils/sort.hpp"


int _Calc_Options_Player::_count_alphas()
{
    int result = 1;
    bool is_found = false;
    do {
        if (this->_payoffs[0]->second ==
            this->_payoffs[result]->second) {
            result++;
        } else {
            is_found = true;
        }
    } while (!is_found);

    return result;
}


Payoff* _Calc_Options_Player::_find_alpha(Payoff* beta, int end)
{
    Payoff* result = nullptr;
    Card_Flags cards = this->get_cards() & ~beta->second;

    int i=0;
    bool is_found = false;
    do {
        Card_Flags free_cards = cards & this->_payoffs[i]->first;
        if (this->_payoffs[i]->first == free_cards) {
            result = this->_payoffs[i];
            is_found = true;
        }
        i++;
    } while (!is_found && (i < end));

}


Payoff* _Calc_Options_Player::_find_beta(Payoff* alpha, int start)
{
    Payoff* result = nullptr;
    Card_Flags cards = this->get_cards() & ~alpha->first;

    int i=start;
    do {
        Card_Flags free_cards = cards & this->_payoffs[i]->first;
        if (this->_payoffs[i]->first == free_cards) {
            result = this->_payoffs[i];
        } else {
            i++;
        }
    } while (!result && (i < this->_num_payoffs));
    if (!result) {
        this->_reset();
        result = this->_create_nothing_payoff(cards);
    }
    return result;
}

#include <iostream>
#include <bitset>
#define BREAK(a) std::cout << a << std::endl;
#define BITS(a)  std::bitset<52>( (a) )
/*
void _Calc_Options_Player::_calc_alpha()
{
    Sort::quick_sort(this->_payoffs, 0, this->_num_payoffs-1);
    Sort::quick_sort(this->_payoffs_3c, 0, this->_num_payoffs_3c-1);
    this->_alpha = this->_payoffs[0];

    std::cout << BITS(this->_alpha->first) << '\t';
    std::cout << this->_alpha->second << ' ' << this->_alpha->third << std::endl;
    this->_beta = this->_find_beta(this->_alpha, 0);

    int num_alphas = this->_count_alphas();
    for (int i=0; i < num_alphas; i++) {
        Payoff* contender = this->_find_beta(this->_payoffs[i], i);
        if (contender->second  < this->_beta->second ||
            contender->second == this->_beta->second &&
            contender->first   > this->_beta->first) {
            this->_alpha = this->_payoffs[i];
            this->_beta = contender;
        }
    }
    std::cout << BITS(this->_alpha->first) << '\t';
    std::cout << this->_alpha->second << ' ' << this->_alpha->third << std::endl;
    _remaining_to_gamma();
}
*/


void _Calc_Options_Player::_calc_alpha()
{
    Sort::quick_sort(this->_payoffs, 0, this->_num_payoffs-1);
    Sort::quick_sort(this->_payoffs_3c, 0, this->_num_payoffs_3c-1);

    this->_alpha = this->_payoffs[0];
    int num_alphas = this->_count_alphas();
    for (int i=0; i < num_alphas; i++) {
        for (int i=0; i < this->_num_payoffs_3c) {
            
            Payoff* highest = find_option();
        Payoff* contender = this->_find_beta(this->_payoffs[i], i);
        if (contender->second  < this->_beta->second ||
            contender->second == this->_beta->second &&
            contender->first   > this->_beta->first) {
            this->_alpha = this->_payoffs[i];
            this->_beta = contender;
        }
    }
    std::cout << BITS(this->_alpha->first) << '\t';
    std::cout << this->_alpha->second << ' ' << this->_alpha->third << std::endl;
    _remaining_to_gamma();
}


void _Calc_Options_Player::_calc_beta()
{
    this->_alpha = nullptr;

    int i=1;
    do {
        this->_beta = this->_payoffs[i];
        this->_alpha = this->_find_alpha(this->_beta, i);
        i++;
    } while (!this->_alpha);

    _remaining_to_gamma();
}


void _Calc_Options_Player::_remaining_to_gamma()
{
    Card_Flags remaining = this->get_cards() &
        ~(this->_alpha->first | this->_beta->first);

    int i=0;
    bool is_found = false;
    do {
        Card_Flags free = this->_payoffs_3c[i]->first & remaining;
        if (free == this->_payoffs_3c[i]->first) {
            this->_gamma = this->_payoffs_3c[i];
            is_found = true;
        }
        i++;
    } while (!is_found && i < this->_num_payoffs_3c);
    if (!this->_gamma)
        this->_gamma = this->_rank_nothing_payoff(remaining);
}


void _Calc_Options_Player::_calc_gamma()
{

}


void _Calc_Options_Player::draw(int num_cards)
{
    _Base_Player::draw(num_cards);
    this->_alpha = nullptr;
    this->_beta = nullptr;
    this->_gamma = nullptr;
}
