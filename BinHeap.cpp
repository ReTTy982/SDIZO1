#include <iostream>
#include "BinHeap.hpp"

template <typename T>
int BinHeap<T>::parent(int index)
{
    return (index - 1) / 2;
}

template <typename T>
int BinHeap<T>::left(int index)
{
    return (index * 2) + 1;
}

template <typename T>
int BinHeap<T>::right(int index)
{
    return (index * 2) + 2;
}

template <typename T>
int BinHeap<T>::look_for_index(const T &value)
{
    int index = 0;
    while (index != array.get_array_size())
    {
        if (array.get_value(index) == value)
        {
            return index;
        }
        index++;
    }
    return -1;
}

template <typename T>
bool BinHeap<T>::search(const T &value)
{
    return array.search(value);
}
template <typename T>
void BinHeap<T>::push(const T &value)
{

    array.push_back(value);
    int i = array.get_array_size() - 1;

    while (i != 0 && array.get_value(parent(i)) < array.get_value(i))
    {
        // std::cout << "SWAPPING: " << array.get_value(i) << " : " << array.get_value(parent(i)) << std::endl;
        std::swap(array.get_value(i), array.get_value(parent(i)));
        i = parent(i);
    }
}

template <typename T>
bool BinHeap<T>::pop(const T &value)
{

    int max_index = array.get_array_size() - 1;
    int index = look_for_index(value);

    if (index < -1)
    {
        return false;
    }
    array.get_value(index) = array.get_value(max_index);
    array.resize(max_index);

    if (index == max_index)
    {
        return true;
    }

    // naprawa kopca

    if (index > 0 && array.get_value(index) > array.get_value(parent(index)))
    {

        // std::cout << "SWAPPING: " << array.get_value(index) << " : " << array.get_value(parent(index)) << std::endl;
        std::swap(array.get_value(index), array.get_value(parent(index)));
        index = parent(index);
    }
    else
    {
        while (1)
        {

            int temp = index;

            if (left(index) < max_index && array.get_value(temp) < array.get_value(left(index)))
            {
                temp = left(index);
            }

            if (right(index) < max_index && array.get_value(temp) < array.get_value(right(index)))
            {
                temp = right(index);
            }

            if (temp != index)
            {
                // std::cout << "SWAPPING: " << array.get_value(index) << " : " << array.get_value(temp)<< std::endl;
                std::swap(array.get_value(index), array.get_value(temp));
                index = temp;
            }
            else
            {

                break;
            }
        }
    }
    return true;
}

template <typename T>
void BinHeap<T>::print()
{
    int row = 0, pow = 1;

    for (int i = 0; i < array.get_array_size(); i++)
    {

        std::cout << array.get_value(i) << " ";
        if (i == row)
        {

            pow *= 2;
            row += pow;
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
}

/*
int main()
{

    BinHeap<int> obj;
    obj.push(69);
    obj.push(5);
    obj.push(8);
    obj.push(3);
    obj.push(0);
    obj.push(53);
    obj.push(56);
    obj.print();

    return 0;
}
*/
template class BinHeap<int>;
