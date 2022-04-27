#pragma once

#include "Array.hpp"
#include "iostream"

template <typename T>
class BinHeap
{
    Array<T> array;

public:
    int parent(int index);
    int left(int index);
    int right(int index);

    void swap(T x, T y);

    void push(const T &value);
    bool pop(const T &value);

    bool search(const T &value);
    void print_array();
    void print();
    int look_for_index(const T &value);

};