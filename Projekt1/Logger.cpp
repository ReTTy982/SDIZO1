#include <iostream>
#include <fstream>
#include "Logger.hpp"
#include "Array.hpp"

FileHandler::FileHandler()
{
    array_file.open("Test_Results.txt");
}

FileHandler::~FileHandler()
{
    array_file.close();
}

void FileHandler::logToFile(unsigned long long time)
{
    std::cout << time << std::endl;
    array_file << time << ";";
}
