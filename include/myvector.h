#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <cstddef>

template <typename T>
class MyVector
{
private:
    unsigned int total_items;
    T *items;
    unsigned int total_memory_size; // actually it means capacity, not available bytes.

public:
    MyVector();
    MyVector(const MyVector<T> &x);
    ~MyVector();
    unsigned int size();
    unsigned int size() const;
    bool empty();
    bool empty() const;
    void push_back(const T &x);
    void pop_back();
    void reserve(int new_mem_size);
    T& at(int idx);
    T back();
    T& operator[](int idx);
    const T& operator[](int idx) const;
    MyVector<T>& operator=(const MyVector<T> &x);

public:
    class iterator;
    iterator begin();
    const iterator begin() const;
    iterator end();
    const iterator end() const;
};

template <typename T>
MyVector<T>::MyVector()
{
    total_items = 0;
    items = NULL;
    total_memory_size = 0;
}
template <typename T>
MyVector<T>::MyVector(const MyVector<T> &x)
{
    total_items = x.total_items;
    items = new T[total_items];
    total_memory_size = x.total_items;

    for (int i = 0; i < total_items; i++)
    {
        items[i] = x[i];
    }
}
template <typename T>
MyVector<T>::~MyVector()
{
    delete[] items;
}
template <typename T>
unsigned int MyVector<T>::size()
{
    return total_items;
}

template <typename T>
unsigned int MyVector<T>::size() const
{
    return total_items;
}

template <typename T>
bool MyVector<T>::empty()
{
    return (total_items == 0);
}

template <typename T>
bool MyVector<T>::empty() const
{
    return (total_items == 0);
}

template <typename T>
void MyVector<T>::push_back(const T &x)
{
    if (total_memory_size == 0)
    {
        reserve(2);
    }

    if (total_items == total_memory_size)
    {
        reserve(total_memory_size << 1);
    }

    items[total_items++] = x;
}

template <typename T>
void MyVector<T>::pop_back()
{
    items[total_items--] = T();
}

template <typename T>
void MyVector<T>::reserve(int new_mem_size)
{
    // the capacity of the vector can only increase.
    if (new_mem_size <= total_memory_size)
        return;

    T *temp = new T[new_mem_size];

    for (int i = 0; i < total_items; i++)
    {
        temp[i] = items[i];
    }

    delete[] items;

    items = temp;
    total_memory_size = new_mem_size;
}

template <typename T>
T &MyVector<T>::at(int idx)
{
    return items[idx];
}
template <typename T>
T MyVector<T>::back()
{
    return items[total_items - 1];
}

template <typename T>
T &MyVector<T>::operator[](int idx)
{
    return at(idx);
}

template <typename T>
const T &MyVector<T>::operator[](int idx) const
{
    return at(idx);
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &x)
{
    if (this == &x)
        return *this;

    if (x.total_items <= total_memory_size)
    {
        for (int i = 0; i < x.total_items; i++)
        {
            items[i] = x[i];
        }
        total_items = x.total_items;
        return *this;
    }

    T *temp = new T[x.total_items];

    for (int i = 0; i < x.total_items; i++)
    {
        temp[i] = x[i];
    }
    delete[] items;
    items = temp;
    total_items = x.total_items;
    total_memory_size = x.total_memory_size;

    return *this;
}
template <typename T>
class MyVector<T>::iterator
{
private:
    T *itr;

public:
    iterator(T *ptr)
    {
        itr = ptr;
    }
    iterator& operator++()
    {
        itr++;
        return *this;
    }
    iterator& operator--()
    {
        itr--;
        return *this;
    }
    T& operator*()
    {
        return *itr;
    }
    bool operator==(const iterator& y) const
    {
        return *itr == *y.itr;
    }
    bool operator!=(const iterator& y) const
    {
        return *itr != *y.itr;
    }
    iterator& operator-(const iterator& y) 
    {
        return *itr - *y.itr;
    }
};

template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin()
{
    return MyVector<T>::iterator(&items[0]);
}

template <typename T>
const typename MyVector<T>::iterator MyVector<T>::begin() const
{
    return MyVector<T>::iterator(&items[0]);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end()
{
    return MyVector<T>::iterator(&items[total_items]);
}

template <typename T>
const typename MyVector<T>::iterator MyVector<T>::end() const
{
    return MyVector<T>::iterator(&items[total_items]);
}
#endif