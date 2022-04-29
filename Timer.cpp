#include <iostream>
#include <random>
#include <chrono>
#include "Array.hpp"
#include <fstream>
#include "Logger.hpp"
#include <functional>
#include "List.hpp"
#include "BinHeap.hpp"
#include "RBTree.hpp"

#include "Timer.hpp"
#include "AvarageTimeMeasure.hpp"

unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
static std::default_random_engine generator(seed);

FileHandler logger;

int loopCount = 10;
int datasetGenerationCount = 100;

std::vector<int> datasetSizesToTest =
    {1000, 2000, 3000, 4000, 5000, 10000, 15000, 20000};

int datasetSize = 2000;

template <typename T>
T Timer::randomNumberWithinRange(const T &first, const T &second)
{
    std::uniform_int_distribution<T> distribution(first, second);

    return distribution(generator);
}

typedef int datatype;
typedef unsigned long long timedata;

template <typename T>
std::vector<T> Timer::generateRandomData(std::size_t datasetSize)
{
    std::vector<T> dataset;

    for (int i = 0; i < datasetSize; i++)
    {
        dataset.push_back(randomNumberWithinRange(INT32_MIN, INT32_MAX));
    }

    return dataset;
}

template <typename T>
T Timer::getDataForSearch(std::vector<T> &dataset)
{
    int index = randomNumberWithinRange((std::size_t)0, dataset.size() - 1);
    dataset.erase(dataset.begin() + index);
    return dataset[index];
}

template <typename T>
unsigned long long Timer::ArrayInsert()
{
    AveragedTimeMeasure<timedata> containerTimeAvarage;

    for (int i = 0; i < datasetGenerationCount; i++)
    {
        std::vector<int> dataset = generateRandomData<int>(datasetSize);

        for (int j = 0; j < loopCount; j++)
        {
            Array<T> container;
            container.push_back(dataset[0]);

            for (int datasetIndex = 1; datasetIndex < datasetSize; datasetIndex++)
            {
                int insertIndex = randomNumberWithinRange(0, datasetIndex - 1);
                containerTimeAvarage.benchmarkStart();
                container.push(dataset[datasetIndex], insertIndex);
                containerTimeAvarage.benchmarkStop();
            }
        }
    }

    return containerTimeAvarage.getAvgElapsedNsec();
}
template <typename T>
unsigned long long Timer::ListInsert()
{

    AveragedTimeMeasure<timedata> containerTimeAvarage;

    for (int i = 0; i < datasetGenerationCount; i++)
    {
        std::vector<int> dataset = generateRandomData<int>(datasetSize);

        for (int i = 0; i < loopCount; i++)
        {

            List<T> container;
            container.push_back(dataset[0]);

            for (int datasetIndex = 1; datasetIndex < datasetSize; datasetIndex++)
            {
                int insertIndex = randomNumberWithinRange(0, datasetIndex - 1);
                auto *node = container.get_node(dataset[insertIndex]);

                containerTimeAvarage.benchmarkStart();
                container.push(dataset[datasetIndex], node);
                containerTimeAvarage.benchmarkStop();
            }
        }
    }
    return containerTimeAvarage.getAvgElapsedNsec();
}

template <template <typename> typename T, typename D>
unsigned long long Timer::GenericInsert(std::function<void(T<D> &, D)> func)
{

    AveragedTimeMeasure<timedata> containerTimeAvarage;

    for (int i = 0; i < datasetGenerationCount; i++)
    {
        std::vector<D> dataset = generateRandomData<D>(datasetSize);

        for (int i = 0; i < loopCount; i++)
        {

            T<D> container;

            for (const auto &value : dataset)
            {

                containerTimeAvarage.benchmarkStart();
                func(container, value);
                containerTimeAvarage.benchmarkStop();
            }
        }
    }

    return containerTimeAvarage.getAvgElapsedNsec();
}

template <template <typename> typename T, typename D>
timedata Timer::GenericRemoveFunc(std::function<void(T<D> &, D)> funcAdd,
                                  std::function<void(T<D> &)> funcRemove)
{
    AveragedTimeMeasure<timedata> containerTimeAvarage;

    for (int i = 0; i < datasetGenerationCount; i++)
    {
        std::vector<D> dataset = generateRandomData<D>(datasetSize);

        for (int i = 0; i < loopCount; i++)
        {

            T<D> container;

            for (const auto &value : dataset)
            {
                funcAdd(container, value);
            }

            for (const auto &value : dataset)
            {
                containerTimeAvarage.benchmarkStart();
                funcRemove(container);
                containerTimeAvarage.benchmarkStop();
            }
        }
    }

    return containerTimeAvarage.getAvgElapsedNsec();
}

template <template <typename> typename T, typename D>
timedata Timer::GenericRemove(std::function<void(T<D> &, D)> funcAdd)
{
    AveragedTimeMeasure<timedata> containerTimeAvarage;

    for (int i = 0; i < datasetGenerationCount; i++)
    {
        std::vector<D> dataset = generateRandomData<D>(datasetSize);

        for (int i = 0; i < loopCount; i++)
        {

            T<D> container;

            for (const auto &value : dataset)
            {
                funcAdd(container, value);
            }

            for (const auto &value : dataset)
            {
                containerTimeAvarage.benchmarkStart();
                container.pop(value);
                containerTimeAvarage.benchmarkStop();
            }
        }
    }

    return containerTimeAvarage.getAvgElapsedNsec();
}

template <template <typename> typename T, typename D>
timedata Timer::GenericSearch(std::function<void(T<D> &, D)> funcAdd)
{
    AveragedTimeMeasure<timedata> containerTimeAvarage;

    for (int i = 0; i < datasetGenerationCount; i++)
    {

        std::vector<D> dataset = generateRandomData<D>(datasetSize);

        T<D> container;

        for (const auto &value : dataset)
        {
            funcAdd(container, value);
        }

        for (int i = 0; i < loopCount; i++)
        {
            while (!dataset.empty())
            {
                auto value = getDataForSearch(dataset);
                containerTimeAvarage.benchmarkStart();
                bool found = container.search(value);
                if (!found)
                {
                    throw std::runtime_error("Cos jest nie tak");
                }
                containerTimeAvarage.benchmarkStop();
            }
        }
    }
    return containerTimeAvarage.getAvgElapsedNsec();
}

void Timer::run()
{
    auto array_push_front = [](Array<datatype> &array, const datatype &value)
    { array.push_front(value); };
    auto array_push_back = [](Array<datatype> &array, const datatype &value)
    { array.push_back(value); };
    auto array_pop_front = [](Array<datatype> &array)
    { array.pop_front(); };
    auto array_pop_back = [](Array<datatype> &array)
    { array.pop_back(); };
    auto list_push_front = [](List<datatype> &list, const datatype &value)
    { list.push_front(value); };
    auto list_push_back = [](List<datatype> &list, const datatype &value)
    { list.push_back(value); };
    auto list_pop_front = [](List<datatype> &list)
    { list.pop_front(); };
    auto list_pop_back = [](List<datatype> &list)
    { list.pop_back(); };
    auto heap_push = [](BinHeap<datatype> &heap, const datatype &value)
    { heap.push(value); };
    auto tree_push = [](RBTree<datatype> &tree, const datatype &value)
    { tree.push(value); };

    GenericInsert<Array, datatype>(array_push_front); // Nie wiem czemu ale to naprawia bardzo niski czas pierwszej operacji.
    for (auto size : datasetSizesToTest)
    {
        datasetSize = size;
        /*
                // ARRAY
                logger.logToFile(GenericInsert<Array, datatype>(array_push_front));
                logger.logToFile(GenericInsert<Array, datatype>(array_push_back));
                logger.logToFile(GenericRemoveFunc<Array, datatype>(array_push_back, array_pop_front));
                logger.logToFile(GenericRemoveFunc<Array, datatype>(array_push_back, array_pop_back));
                logger.logToFile(GenericSearch<Array, datatype>(array_push_back));


                // LIST

                logger.logToFile(GenericInsert<List, datatype>(list_push_front));
                logger.logToFile(GenericInsert<List, datatype>(list_push_back));
                logger.logToFile(GenericRemoveFunc<List, datatype>(list_push_back, list_pop_front));
                logger.logToFile(GenericRemoveFunc<List, datatype>(list_push_back, list_pop_back));
                logger.logToFile(GenericSearch<List, datatype>(list_push_back));


                // BinHeap
                logger.logToFile(GenericInsert<BinHeap, datatype>(heap_push));
                logger.logToFile(GenericRemove<BinHeap, datatype>(heap_push));
                logger.logToFile(GenericSearch<BinHeap, datatype>(heap_push));
*/
                // RBTree
                logger.logToFile(GenericInsert<RBTree, datatype>(tree_push));
                logger.logToFile(GenericRemove<RBTree, datatype>(tree_push));
                logger.logToFile(GenericSearch<RBTree, datatype>(tree_push));
                    
        // logger.logToFile(ArrayInsert<datatype>());
        // logger.logToFile(ListInsert<datatype>());


        logger.array_file
            << std::endl;
    }
}
