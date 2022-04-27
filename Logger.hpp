#pragma once
#include <iostream>
#include <fstream>
#include "Array.hpp"

class FileHandler
{


public:

    std::ofstream array_file;
    std::ofstream list_file;
    
    FileHandler();


    ~FileHandler();


    void logToFile(unsigned long long time);
};