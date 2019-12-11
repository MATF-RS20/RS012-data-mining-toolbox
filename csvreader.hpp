#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <iostream>
#include <fstream>

class csvReader
{
public:
    csvReader(std::string filename);
    ~csvReader();

    std::ifstream file;
};

#endif // CSVREADER_HPP
