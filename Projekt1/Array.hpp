#pragma once

#include <iostream>

template <typename T>
class Array
{
    int array_size = 0;
    int *array = nullptr;

public:
    Array(const int &size = 0);
    ~Array();

    void resize(const int &size);

    void print();

    void push_back(const T &value);

    void push_front(const T &value);

    void pop_back();

    void pop_front();

    void push(const T &value, const int &index);

    void pop_index(const T &index);

    void index_check(const int &index);

    int get_array_size();

    bool search(const T &value);

    T &get_value(const int &at);

    int get_index(const T &value);
    void pop(const T &value);
};
