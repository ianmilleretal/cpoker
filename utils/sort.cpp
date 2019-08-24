#include "../card_cons.hpp"
#include "../utils/sort.hpp"
#include <utility>


int Sort::_partition(Payoff* payoffs[], int low, int high)
{  
    Payoff* pivot = payoffs[high];
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (payoffs[j]->second <= pivot->second)
        {
            i++;
            std::swap(payoffs[i], payoffs[j]);
        }
    }
    std::swap(payoffs[i + 1], payoffs[high]);
    return (i + 1);
}

