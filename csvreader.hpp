#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

//Class for reading from csv file:
//    -Constructor opens and destructor closes the file.
//    -Method read returns vector of lines from file.

class csvReader
{
public:
    csvReader(std::string filename);
    ~csvReader();

    //Are copy constructor and '=' operator necessary?
    //csvReader(csvReader& cr);


    std::vector<std::vector<std::string>> read();


    std::ifstream file;
};

#endif // CSVREADER_HPP
