#include "DataTable.hpp"

#include <iostream>
#include <vector>

DataTable::DataTable(){}


// TODO: constructor should set all keys in the map (all column names) and allocate vectors because we've already read them
DataTable::DataTable(unsigned long nRows):numberOfRows(nRows){}

DataTable::~DataTable(){}

//TODO: Proveriti da li je ovo neophodno! Dodato u pokusaju da proradi konstruktor kopije Stream klase, odnosno da bude pravo kopiranje klase Node.
//Kopiranje Stream-a nema veze sa ovim. Proveriti da li ovo ima veze sa kopiranjem Node-a.
DataTable::DataTable(const DataTable& dt)
    : dataMatrix(dt.DataMatrix()),
      columnNames(dt.ColumnNames()),
      classTargetVariable(dt.ClassTargetVariable()),
      classTargetVariableSet(dt.ClassTargetVariableSet()),
      numberOfRows(dt.NumberOfRows()){}

arma::mat DataTable::DataMatrix() const {
    return dataMatrix;
}

std::vector<std::string> DataTable::ColumnNames() const {
    return columnNames;
}

std::vector<std::string> DataTable::ClassTargetVariable() const{
    return classTargetVariable;
}

bool DataTable::ClassTargetVariableSet() const{
    return classTargetVariableSet;
}

unsigned long DataTable::NumberOfRows() const {
    return numberOfRows;
}

void DataTable::SetDataMatrix(const arma::mat& matrix){
    dataMatrix = matrix;
}

void DataTable::SetClassTargetVariable(const std::vector<std::string>& stringColumn){
    classTargetVariable = stringColumn;
}

void DataTable::SetClassTargetVariableSet(const bool & isSet){
    classTargetVariableSet = isSet;
}

void DataTable::addKey(const std::string& keyName)
{
    columnNames.push_back(keyName);
}

