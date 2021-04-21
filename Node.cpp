#include "Node.hpp"

#include <utility>

// Constructor
Node::Node(std::string name) : nodeName(std::move(name)) {}

// Getters
const DataTable *Node::InputDataTable() const { return inputDataTable; }

DataTable Node::OutputDataTable() const { return outputDataTable; }

std::string Node::NodeName() const { return nodeName; }

// TODO: DELETE!!!
DataTable *Node::RefOutputDataTable() { return &outputDataTable; }

std::string Node::OutputMessage() const { return outputMessage; }

// Setters
void Node::setInputDataTable(DataTable *inDataTable) {
  inputDataTable = inDataTable;
}

void Node::setOutDataTable(const DataTable &outDataTable) {
  outputDataTable = outDataTable;
}

void Node::setOutputMessage(std::string message) {
  outputMessage = std::move(message);
}

// Retriving original column with given column name, from binarized columns in
// data matrix
std::vector<std::string> Node::unbinarize(const std::string &columnName) const {

  // Alocating resulting vector
  std::vector<std::string> result(InputDataTable()->DataMatrix().n_rows);
  size_t colIndex = 0;
  const std::map<std::string, std::set<std::string>> map_tmp =
      InputDataTable()->CategoricalValues();
  auto colNames = InputDataTable()->ColumnNames();

  // Geting index of column with given name
  for (auto &colName : colNames) {
    if (columnName == colName) {
      break;
    }
    if (map_tmp.find(colName) != map_tmp.end()) {

      colIndex += map_tmp.at(colName).size();

    }

    else {

      colIndex++;
    }
  }

  // For every tuple in data, for every value in the set of categories for the
  // given column, if the adequate binarized column field equals 1, then the
  // class for that tuple is that category.
  for (unsigned i = 0; i < InputDataTable()->DataMatrix().n_rows; i++) {
    unsigned long tmp = colIndex;
    for (const auto &c : map_tmp.at(columnName)) {
      // std::transform(OutputDataTable().DataMatrix().begin_col(colIndex),
      // OutputDataTable().DataMatrix().end_col(colIndex), result.begin(),
      // [c](double x){if (fabs(x-1) < 0.00001) return c;});
      if (InputDataTable()->DataMatrix()(i, colIndex) > 0) {
        result[i] = c;
        break;
      }
      colIndex++;
    }
    colIndex = tmp;
  }

  return result;
}

// Making an arma::mat without a column with name given, which is binarized
arma::mat Node::filterBinarisedCol(const std::string &colName) {
  std::vector<std::string> colNames = inputDataTable->ColumnNames();
  const std::map<std::string, std::set<std::string>> map_tmp =
      InputDataTable()->CategoricalValues();
  unsigned index = 0;

  // Finding index of the first binarized column, with given column name
  for (unsigned i = 0; i != colNames.size(); i++) {
    if (colName == colNames[i]) {
      break;
    }
    if (map_tmp.find(colNames[i]) != map_tmp.end()) {

      index += map_tmp.at(colNames[i]).size();

    }

    else {

      index++;
    }
  }

  // Number of binarized columns with given column name
  unsigned numberOfCol = map_tmp.at(colName).size();

  // Sheding those columns with indexes between index and numberOfCol
  arma::mat result = inputDataTable->DataMatrix();
  for (unsigned i = index + numberOfCol - 1; i > index; i--) {
    result.shed_col(i);
  }
  result.shed_col(index);

  return result;
}

// Making a data table without the column with given column name
DataTable Node::filter(const std::string &colName) {

  std::vector<std::string> vectorOfNames = inputDataTable->ColumnNames();

  // Finding index of the column with the given column name
  unsigned long i = 0;
  for (; i < vectorOfNames.size(); i++) {
    if (vectorOfNames[i] == colName) {
      break;
    }
  }
  if (i == vectorOfNames.size()) {
    std::cout << "Invalid column name" << std::endl;
    return *inputDataTable;
  }

  arma::mat dataMatrix;
  auto catVal = this->inputDataTable->CategoricalValues();

  // If the column is in the map categoricalValues, then we call
  // filterBinarisedCol, else just shed the column with that index.
  if (catVal.find(colName) != catVal.end()) {
    dataMatrix = this->filterBinarisedCol(colName);
    catVal.erase(colName);
  } else {
    dataMatrix = inputDataTable->DataMatrix();
    dataMatrix.shed_col(i);
  }

  // Setting parameters for the new data table
  vectorOfNames.erase(vectorOfNames.begin() + i);
  DataTable dt = DataTable();
  dt.SetDataMatrix(dataMatrix);
  dt.SetCategoricalValues(catVal);
  dt.SetColumnNames(vectorOfNames);
  if (!inputDataTable->IsPartitioned()) {
    dt.SetIsPartitioned(false);
  } else {
    dt.SetIsPartitioned(true);
    dt.SetPartition(inputDataTable->Partition());
    dt.SetTestSize(inputDataTable->TestSize());
  }
  return dt;
}
