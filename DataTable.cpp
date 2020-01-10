#include "DataTable.hpp"

#include <iostream>
#include <vector>

DataTable::DataTable(){
    isPartitioned = 0;
    testSize = 0;
}

DataTable::~DataTable(){}

//TODO: Check if this is necessary! Added for copy constructor of class Stream, so it can deep copy instances of class Node.
//But this has nothing to do with copy constructor of Stream class. Check if this has anything to do with copy construcotr of class Node.
DataTable::DataTable(const DataTable& dt)
    : dataMatrix(dt.DataMatrix()),
      columnNames(dt.ColumnNames()),
      categoricalValues(dt.CategoricalValues()),
      partition(dt.Partition()),
      isPartitioned(dt.IsPartitioned()),
      testSize(dt.TestSize()){}

arma::mat DataTable::DataMatrix() const {
    return dataMatrix;
}

std::vector<std::string> DataTable::ColumnNames() const {
    return columnNames;
}

std::map<std::string, std::set<std::string>> DataTable::CategoricalValues() const {
    return categoricalValues;
}

std::vector<bool> DataTable::Partition() const {
    return partition;
}

bool DataTable::IsPartitioned() const {
    return isPartitioned;
}

void DataTable::SetDataMatrix(const arma::mat& matrix){
    dataMatrix = matrix;
}

void DataTable::addKey(const std::string& keyName) {
    columnNames.emplace_back(keyName);
}

void DataTable::addCategoricalValues(unsigned columnIndex, std::set<std::string> setOfValues) {
    categoricalValues[columnNames[columnIndex]] = setOfValues;
}

void DataTable::SetCategoricalValues(const std::map<std::string, std::set<std::string>> & catVal){
    categoricalValues = catVal;
}
   
void DataTable::SetColumnNames(const std::vector<std::string>& colNames){
    columnNames = colNames;
}

/************************************************************************/
void DataTable::SetPartition(const std::vector<bool>& vector){
    partition = vector;
}

void DataTable::SetIsPartitioned(const bool & isSet){
    isPartitioned = isSet;
}

void DataTable::SetTestSize(const unsigned long & size){
    testSize = size;
}

unsigned long DataTable::TestSize() const {
    return testSize;
}

/*************************************************************************/
