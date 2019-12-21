#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <iostream>
#include <fstream>

class csvReader
{
public:
    csvReader(std::string filename);
    ~csvReader();

    //Are copy constructor and '=' operator necessary?
    //csvReader(csvReader& cr);


    std::ifstream file;
};

#endif // CSVREADER_HPP
