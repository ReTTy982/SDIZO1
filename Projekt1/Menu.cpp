#include <iostream>
#include <fstream>

#include "Array.hpp"
#include "List.hpp"
#include "BinHeap.hpp"
#include "Timer.hpp"
#include "AvarageTimeMeasure.hpp"
#include "RBTree.hpp"
using namespace std;

typedef int datatype;

const string commonOperations = "r - read from file\na - add value\nx - remove value\nc - search if value exists\np - print container contents\nq - quit\n";
const string appendOperations = "f - push front\nb - push back\nx- exit append mode\n";
const string deleteOperations = "f - pop front\nb- pop back\nx - exit delete mode\n";

vector<datatype> readFromFile()
{
    string fileName;

    cout << "Enter file name\n";
    cin >> fileName;

    ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Error");

    vector<datatype> values;
    int len;
    file >> len;
    datatype val;

    for (; len > 0; len--)
    {
        file >> val;
        values.push_back(val);
        cout << val;
    }
    file.close();

    return values;
}

datatype getDataFromUser()
{
    datatype val;
    cout << "Podaj wartosc:\n";
    cin >> val;

    cin.clear();
    cin.ignore(10000, '\n');

    return val;
}

char getOptionFromUser()
{
    char input;
    std::cin >> input;

    cin.clear();
    cin.ignore(10000, '\n');

    return input;
}

void rbTreeMenu()
{
    char input;
    RBTree<datatype> container;
repeat:
    cout << commonOperations;
    input = getOptionFromUser();

    switch (input)
    {
    case 'q':
        return;
        break;
    case 'r':
    {
        auto data = readFromFile();
        for (auto val : data)
            container.push(val);
        break;
    }
    case 'a':
    {
        container.push(getDataFromUser());
        break;
    }
    case 'x':
        container.pop(getDataFromUser());
        break;
    case 'c':
        cout << container.search(getDataFromUser()) << endl;
        break;
    case 'p':
        container.print();
        std::cin.get();
        break;
    }

    goto repeat;
}

void listMenu()
{
    char input;
    List<datatype> container;
repeat:
    cout << commonOperations;
    input = getOptionFromUser();

    switch (input)
    {
    case 'q':
        return;
        break;

    case 'r':
    {
        auto data = readFromFile();
        for (auto val : data)
            container.push_back(val);
        break;
    }

    case 'a':
    {
    repeat_append:
        cout << appendOperations;
        input = getOptionFromUser();
        switch (input)
        {
        case 'b':
            container.push_back(getDataFromUser());
            break;
        case 'f':
            container.push_front(getDataFromUser());
            break;

        case 'x':
            goto repeat;
        }
        container.print();
        goto repeat_append;
    }
    case 'x':
    repeat_delete:
        cout << deleteOperations;
        input = getOptionFromUser();
        switch (input)
        {
        case 'b':
            container.pop_back();
            break;
        case 'f':
            container.pop_front();
            break;

        case 'x':
            goto repeat;
        }
        container.print();
        goto repeat_delete;
    case 'c':
        cout << container.search(getDataFromUser()) << endl;
        break;
    case 'p':
        container.print();
        std::cin.get();
        break;
    }

    goto repeat;
}

void arrayMenu()
{
    char input;
    Array<datatype> container;
repeat:
    cout << commonOperations;
    input = getOptionFromUser();

    switch (input)
    {
    case 'q':
        return;
        break;
    case 'r':
    {

        auto data = readFromFile();
        for (auto val : data)
            container.push_back(val);

        break;
    }
    case 'a':
    {
    repeat_append:
        cout << appendOperations;
        input = getOptionFromUser();
        switch (input)
        {
        case 'b':
            container.push_back(getDataFromUser());
            break;
        case 'f':
            container.push_front(getDataFromUser());
            break;

        case 'x':
            goto repeat;
        }
        container.print();
        goto repeat_append;
    }
    case 'x':
    {
    repeat_delete:
        cout << deleteOperations;
        input = getOptionFromUser();
        switch (input)
        {
        case 'b':
            container.pop_back();
            break;
        case 'f':
            container.pop_front();
            break;

        case 'x':
            goto repeat;
        }
        container.print();
        goto repeat_delete;
    }
    case 'c':
        cout << container.search(getDataFromUser()) << endl;
        break;
    case 'p':
        container.print();
        std::cin.get();
        break;
    }

    goto repeat;
}

void binHeapMenu()
{
    char input;
    BinHeap<datatype> container;
repeat:
    cout << commonOperations;
    input = getOptionFromUser();

    switch (input)
    {
    case 'q':
        return;
        break;

    case 'r':
    {
        auto data = readFromFile();
        for (auto val : data)
            container.push(val);
        break;
    }

    case 'a':
        container.push(getDataFromUser());
        break;
    case 'x':
        container.pop(getDataFromUser());
        break;
    case 'c':
        cout << container.search(getDataFromUser()) << endl;
        break;
    case 'p':
        container.print();
        std::cin.get();
        break;
    }

    goto repeat;
}

int main()
{
    char input;
    cout << "SDiZO Projekt 1.\n"
         << "Autor: Paul Paczyński ITE 4 semestr\n"
         << "b - test automatyczny kontenerów\n"
         << "m - test manualny\n";
    input = getOptionFromUser();

    if (input == 'b')
    {

        Timer timer;
        timer.run();
        return 0;
    }

    cout << "Wybierz strukture:\n"
         << "h - BinHeap\n"
         << "a - Array\n"
         << "r - RBTree\n"
         << "l - List\n";
    input = getOptionFromUser();

    switch (input)
    {
    case 'h':
        binHeapMenu();
        break;
    case 'a':
        arrayMenu();
        break;
    case 'r':
        rbTreeMenu();
        break;
    case 'l':
        listMenu();
        break;
    }

    return 0;
}