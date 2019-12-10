#include "DataTable.hpp"

#include <iostream>
#include <vector>

DataTable::DataTable(){}


// TODO: constructor should set all keys in the map (all column names) and allocate vectors because we've already read them
DataTable::DataTable(int nRows):numberOfRows(nRows){}

DataTable::~DataTable(){}

std::map<std::string, std::vector<double>> DataTable::DoubleColumns() const {
    return doubleColumns;
}

void DataTable::SetField(std::string columnName, unsigned long index, double value){

    // TODO: if is repetative
    if (doubleColumns[columnName].empty()){
        doubleColumns[columnName] = std::vector <double> (numberOfRows);
    }
    doubleColumns[columnName][index] = value;
}
