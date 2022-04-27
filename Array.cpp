#include <iostream>
#include "Array.hpp"
typedef int datatype;

template <typename T>
Array<T>::Array(const int &size)
{
    if (size == 0)
        return;
    array = new T[size];
}

template <typename T>
Array<T>::~Array()
{
    delete[] array;
}

template <typename T>
void Array<T>::resize(const int &size)
{

    T *new_array = new T[size];

    std::copy(array, array + std::min(array_size, size), new_array);

    delete[] array;
    array = new_array;
    array_size = size;
}

template <typename T>
void Array<T>::print()
{
    for (int i = 0; i < array_size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}


template <typename T>
void Array<T>::push_back(const T &value)
{
    resize(array_size + 1);
    array[array_size - 1] = value;
}
template <typename T>
void Array<T>::push_front(const T &value)
{
    int new_size = array_size + 1;
    T *new_array = new T[new_size];

    std::copy(array, array + array_size, new_array + 1);
    new_array[0] = value;

    delete[] array;
    array = new_array;
    array_size = new_size;
}

template <typename T>
void Array<T>::index_check(const int &index)
{
    if (index >= array_size)
    {
        throw std::out_of_range("Index is out of array's range\n");
    }
}

template <typename T>
void Array<T>::push(const T &value, const int &index)
{
    index_check(index);

    size_t new_size = array_size + 1;
    T *new_array = new T[new_size];

    std::copy(array, array + index, new_array);
    std::copy(array + index, array + array_size, new_array + index + 1);

    new_array[index] = value;

    delete[] array;
    array = new_array;
    array_size = new_size;
}

template <typename T>
void Array<T>::pop(const T &index)
{
    index_check(index);

    size_t new_size = array_size - 1;
    int *new_array = new int[new_size];

    std::copy(array, array + index, new_array);
    std::copy(array + index + 1, array + array_size, new_array + index);

    delete[] array;
    array = new_array;
    array_size = new_size;
}

template <typename T>
void Array<T>::pop_back()
{
    resize(array_size - 1);
}

template <typename T>
void Array<T>::pop_front()
{

    size_t new_size = array_size - 1;
    T *new_array = new T[new_size];

    std::copy(array + 1, array + array_size, new_array);

    delete[] array;

    array = new_array;
    array_size = new_size;
}

template <typename T>
bool Array<T>::search(const T &value)
{
    for (int i = 0; i < array_size; i++)
    {
        if (array[i] == value)
            return true;
    }
    return false;
}
template <typename T>
int Array<T>::get_array_size()
{
    return array_size;
}

template <typename T>
T &Array<T>::get_value(const int &at)
{
    
    if (at >= array_size)
    {
        
        throw std::out_of_range("Array index out of range");
    }
        
    return array[at];
}

template class Array<int>;
