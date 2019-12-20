#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <iostream>
#include <fstream>

class csvReader
{
public:
    csvReader(std::string filename);
    ~csvReader();

    //Da li su neophodni konstruktor kopije i operator dodele?
    //csvReader(csvReader& cr);


    std::ifstream file;
};

#endif // CSVREADER_HPP
