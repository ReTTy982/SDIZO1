#include <iostream>
#include <chrono>
#include "AvarageTimeMeasure.hpp"


template <typename T>
void AveragedTimeMeasure<T>::benchmarkStart()
{
    start = std::chrono::high_resolution_clock::now();
}
template <typename T>
void AveragedTimeMeasure<T>::benchmarkStop()
{
    end = std::chrono::high_resolution_clock::now();
    elapsed += end - start;
    times++;
}
template <typename T>
T AveragedTimeMeasure<T>::getAvgElapsedNsec()
{

    return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() / times;
}

template class AveragedTimeMeasure<unsigned long long>;