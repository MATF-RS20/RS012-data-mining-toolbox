#include "csvreader.hpp"

csvReader::csvReader(std::string filename)
{
    file = std::ifstream(filename);
}

csvReader::~csvReader()
{
    file.close();
}

std::vector<std::vector<std::string>> csvReader::read() {

    std::vector<std::string> rows;
    std::vector<std::vector<std::string>> splitRows;

    if(!file.is_open()) {
        std::cerr << "Invalid path to file" << std::endl;
        return splitRows;
    }
    unsigned long n = 0;

    std::string line;

    while(getline(file, line))
    {
        rows.push_back(line);
        n++;
    }

    //Spliting csv data
    for(unsigned i = 0; i < rows.size(); i++) {
        std::vector<std::string> tmp;
        boost::split(tmp, rows[i], boost::is_any_of(","));
        splitRows.push_back(tmp);
    }

    return splitRows;
}
