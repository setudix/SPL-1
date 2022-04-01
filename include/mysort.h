#ifndef MYSORT_H
#define MYSORT_H

#include "myvector.h"

template <typename T>
bool default_cmp(T &a, T &b) 
{
    return a <= b;
}

template <typename T>
void swap (T& a, T& b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}
template <typename T>
int partition(auto *arr, int low, int high, bool(*cmp)(T&, T&))
{
    int pivot = high;
    int j = low;
    for (int i=low;i<high;i++)
    {
        // if (arr[i] <= arr[pivot])
        if (cmp(arr[i], arr[pivot]))
            swap(arr[i],arr[j++]);
    }
    swap(arr[j], arr[pivot]);
    return j;
}
template <typename T>
void quicksort(auto *arr, int low, int high, bool(*cmp)(T&,T&))
{
    if (low < high)
    {
        int partition_idx = partition(arr, low, high, cmp);
        quicksort(arr, low, partition_idx - 1, cmp);
        quicksort(arr, partition_idx + 1, high, cmp);
    }
}
template <typename T>
void quicksort(MyVector<T> &vect,bool (*cmp)(T&,T&)=default_cmp)
{
    quicksort(vect.vector_array_ptr(), 0, (int)vect.size() - 1, cmp);
}
#endif