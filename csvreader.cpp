#include "csvreader.hpp"

csvReader::csvReader(const std::string &filename) {
  file = std::ifstream(filename);
}

csvReader::~csvReader() { file.close(); }

// read() method reads from file and returns vector of lines (vectors of strings
// that are made from lines by spliting on ",").
std::vector<std::vector<std::string>> csvReader::read() {

  std::vector<std::string> rows;
  std::vector<std::vector<std::string>> splitRows;

  if (!file.is_open()) {
    std::cerr << "Invalid path to file" << std::endl;
    return splitRows;
  }
  unsigned long n = 0;

  std::string line;

  // Getting all lines, and puting them in rows.
  while (getline(file, line)) {
    rows.push_back(line);
    n++;
  }

  // Spliting csv data and triming results. Puting results in splitRows.
  for (auto &row : rows) {
    std::vector<std::string> tmp;
    // Split
    boost::split(tmp, row, boost::is_any_of(","));
    // Trim
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](std::string x) {
      return x.erase(x.find_last_not_of(" \n\r\t") + 1);
    });
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](std::string x) {
      return x.erase(0, x.find_first_not_of(" \n\r\t"));
    });

    splitRows.push_back(tmp);
  }

  return splitRows;
}
