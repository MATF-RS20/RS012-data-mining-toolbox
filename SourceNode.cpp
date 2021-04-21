#include "SourceNode.hpp"

#include <utility>

// Constructor
SourceNode::SourceNode(std::string name) : Node(std::move(name)) {
  this->setInputDataTable(nullptr);
  isRead = false;
}

// Copy constructor
SourceNode::SourceNode(const SourceNode &sn) : Node(sn.NodeName()) {
  this->setFilename(sn.filename);
  this->setOutDataTable(sn.OutputDataTable());
}

// Setter for filename
void SourceNode::setFilename(const std::string &fName) {
  if (filename != fName) {
    isRead = false;
    filename = fName;
  }
}

// Getter for filename
std::string SourceNode::getFileName() { return filename; }

// A helper function, used in read()
double helper(const std::string &value, const std::string &comparingValue) {
  if (comparingValue == value) {
    return 1;
  }
  return 0;
}

// A helper function, used in read()
bool isDouble(const std::string &s) {

  try {
    std::stod(s);
  } catch (std::invalid_argument) {
    return false;
  }
  return true;
}

void SourceNode::read() {

  // Reading from file
  std::vector<std::vector<std::string>> rows = csvReader(filename).read();

  // Taking and erasing column names (first row/first vector) from read data
  std::vector<std::string> columns = rows.front();
  rows.erase(rows.begin());

  // Checking and memorizing indexes of columns and columns that are
  // categorical/numeric and casting numerical data into double
  bool isCategorical = false;
  // Map that contains categorical columns (key is index of column)
  std::map<unsigned, std::vector<std::string>> categoricalColumns;
  // Map that contains numerical columns (key is index of column)
  std::map<unsigned, std::vector<double>> numericalColumns;

  // When iterating through columns, we have two vectors: one is with double,
  // one is with string values. When iterating through a column, we try to cast
  // every element into double. If casting succeeds, we put the element in both
  // vectors, otherwise just in one with string values and every other element
  // in that column is put just in the vector with string values.
  for (unsigned i = 0; i < rows[0].size(); i++) {
    std::vector<std::string> catCol;
    std::vector<double> numCol;
    for (auto &row : rows) {
      catCol.push_back(row[i]);
      if (!isCategorical) {
        isCategorical = !isDouble(row[i]);
        if (!isCategorical) {
          numCol.push_back(std::stod(row[i]));
        }
      }
    }
    // If we managed to put all elements in the vector with double values, we
    // put that vector in the map numericalColumns otherwise we put the vector
    // with string values into map categoricalColumns.
    if (isCategorical) {
      isCategorical = false;
      categoricalColumns[i] = catCol;
    } else {
      numericalColumns[i] = numCol;
    }
  }

  // Adding column names into DataTable
  // Why not dt.SetColumnNames(columns); ?
  DataTable dt;
  for (unsigned i = 0; i < columns.size(); i++) {
    if (numericalColumns.find(i) != numericalColumns.end()) {
      dt.addKey(columns[i]);
    } else {
      dt.addKey(columns[i]);
    }
  }

  // Inserting binarized categorical columns and adding set of their categories
  // in DataTable dt.categoricalValues
  unsigned added = 0;
  for (auto c : categoricalColumns) {

    // Making a set of values for this column
    std::set<std::string> categories(c.second.begin(), c.second.end());
    // Adding that set into the map categoricalValues of dt
    dt.addCategoricalValues(c.first, categories);

    // We need to increase indexes of columns that come after the columns we
    // want to insert by the number of columns we want to insert. That number is
    // equal to number of values in set of values for that columns.

    // Size of the set.
    size_t numOfCategories = categories.size();
    // Vector of indexes we need to change.
    std::vector<unsigned int> keysOfNumerical(numericalColumns.size());
    std::transform(numericalColumns.begin(), numericalColumns.end(),
                   keysOfNumerical.begin(),
                   [](const std::pair<unsigned int, std::vector<double>> &x) {
                     return x.first;
                   });

    for (long int i = keysOfNumerical.size() - 1; i >= 0; i--) {

      // Changing every index biger than the index of the first column we want
      // to add
      if (keysOfNumerical[i] <= c.first + added) {
        break;
      }

      std::vector<double> tmp = numericalColumns[keysOfNumerical[i]];
      numericalColumns[keysOfNumerical[i] + numOfCategories - 1] = tmp;
    }

    /*std::reverse(keysOfNumerical.begin(), keysOfNumerical.end());
     std::transform(keysOfNumerical.begin(), keysOfNumerical.end(),
     numericalColumns.begin(),
     [c, added](unsigned long int x){if(x > c.first + added)
     numericalColumns[x+numOfCategories-1]=numericalColumns[x] return ;});*/

    // For every value in the set of values for current column, we add a new
    // column.
    for (const auto &v : categories) {
      std::vector<double> binCol((*numericalColumns.begin()).second.size());
      std::transform(c.second.begin(), c.second.end(), binCol.begin(),
                     std::bind(helper, std::placeholders::_1, v));
      numericalColumns[c.first + added] = binCol;
      added++;
    }
    added--;
  }

  std::cout << std::endl;

  // Putting values from numericalColumns into arma::mat that will be
  // dt.dataMatrix
  arma::mat matrix((*numericalColumns.begin()).second.size(),
                   numericalColumns.size());
  for (unsigned j = 0; j < numericalColumns.size(); j++) {
    for (unsigned i = 0; i < numericalColumns[j].size(); i++) {

      matrix(i, j) = numericalColumns[j][i];
    }
  }

  // Setting dt. Setting inputDataTable and outputDataTable with dt.
  dt.SetDataMatrix(matrix);

  this->setOutDataTable(dt);
  setInputDataTable(&(this->outputDataTable));

  isRead = true;
}

// Run just calls read if necessary.
void SourceNode::run() {
  if (!isRead) {
    this->read();
  }
}
