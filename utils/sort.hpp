#ifndef SORT_CARDS_
#define SORT_CARDS_


#include "../card_cons.hpp"


class Sort
{
private:
    Sort();
    Sort(Sort &other);
    Sort& operator=(Sort& other);

    static int _partition(Payoff* arr[], int low, int high);


public:
    template<typename T>
    static void quick_sort(T arr[], int low, int high);



};


template<typename T>
void Sort::quick_sort(T arr[], int low, int high)
{  
    if (low < high)
    {  
        int partition = Sort::_partition(arr, low, high);

        Sort::quick_sort(arr, low, partition - 1);
        Sort::quick_sort(arr, partition + 1, high);
    }  
}


#endif
