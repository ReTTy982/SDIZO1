#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include "Array.hpp"
#include <fstream>
#include "Logger.hpp"
#include <functional>
#include "List.hpp"
#include "BinHeap.hpp"
#include "AvarageTimeMeasure.hpp"

class Timer
{

    typedef int datatype;
    typedef unsigned long long timedata;

    template <typename T>
    T randomNumberWithinRange(const T &first, const T &second);
    template <typename T>
    std::vector<T> generateRandomData(std::size_t datasetSize);
    template <typename T>
    T getDataForSearch(std::vector<T> &dataset);

    template <typename T>
    unsigned long long ArrayInsert();
    template <typename T>
    unsigned long long ListInsert();
    template <template <typename> typename T, typename D>
    unsigned long long GenericInsert(std::function<void(T<D> &, D)> func);
    template <template <typename> typename T, typename D>
    timedata GenericRemoveFunc(std::function<void(T<D> &, D)> funcAdd,
                               std::function<void(T<D> &)> funcRemove);
    template <template <typename> typename T, typename D>
    timedata GenericRemove(std::function<void(T<D> &, D)> funcAdd);

    template <template <typename> typename T, typename D>
    timedata GenericSearch(std::function<void(T<D> &, D)> funcAdd);

public:
    void run();
};