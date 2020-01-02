#include "DataTable.hpp"

#include <iostream>
#include <vector>

DataTable::DataTable(){

    isPartitioned = false;
    hasClassTargetVariable = false;
}

DataTable::~DataTable(){}

//TODO: Check if this is necessary! Added for copy constructor of class Stream, so it can deep copy instances of class Node.
//But this has nothing to do with copy constructor of Stream class. Check if this has anything to do with copy construcotr of class Node.
DataTable::DataTable(const DataTable& dt)
    : dataMatrix(dt.DataMatrix()),
      columnNames(dt.ColumnNames()),
      categoricalValues(dt.CategoricalValues()),
      classTargetVariable(dt.ClassTargetVariable()),
      hasClassTargetVariable(dt.HasClassTargetVariable()){}

arma::mat DataTable::DataMatrix() const {
    return dataMatrix;
}

std::vector<std::string> DataTable::ColumnNames() const {
    return columnNames;
}

std::map<std::string, std::set<std::string>> DataTable::CategoricalValues() const {
    return categoricalValues;
}

std::vector<std::string> DataTable::ClassTargetVariable() const{
    return classTargetVariable;
}

bool DataTable::HasClassTargetVariable() const{
    return hasClassTargetVariable;
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

void DataTable::SetClassTargetVariable(const std::vector<std::string>& stringColumn){
    classTargetVariable = stringColumn;
}

void DataTable::SetHasClassTargetVariable(const bool & isSet){
    hasClassTargetVariable = isSet;
}

void DataTable::addKey(const std::string& keyName) {
    columnNames.emplace_back(keyName);
}

void DataTable::addCategoricalValues(unsigned columnIndex, std::set<std::string> setOfValues) {
    categoricalValues[columnNames[columnIndex]] = setOfValues;
}

void DataTable::SetPartition(const std::vector<bool>& vector){
    partition = vector;
}

void DataTable::SetIsPartitioned(const bool & isSet){
    isPartitioned = isSet;
}
