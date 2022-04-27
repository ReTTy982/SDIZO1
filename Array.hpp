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


    void resize(const int &size); //done

    void print(); //done

    void push_back(const T &value); //done

    void push_front(const T &value); //done

    void pop_back(); //done

    void pop_front(); //done

    void push(const T &value, const int &index); //done
 
    void pop(const T &index);  //done

    void index_check(const int &index); //done

    int get_array_size();

    bool search(const T &value); //done

    T &get_value(const int &at);
};
