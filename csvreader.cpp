#include "csvreader.hpp"

csvReader::csvReader(std::string filename)
{
    file = std::ifstream(filename);
}

csvReader::~csvReader()
{
    file.close();
}
