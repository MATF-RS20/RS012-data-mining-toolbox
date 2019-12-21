#include "DataTable.hpp"

#include <iostream>
#include <vector>

DataTable::DataTable(){}


// TODO: constructor should set all keys in the map (all column names) and allocate vectors because we've already read them
DataTable::DataTable(unsigned long nRows):numberOfRows(nRows){}

DataTable::~DataTable(){}

//TODO: Proveriti da li je ovo neophodno! Dodato u pokusaju da proradi konstruktor kopije Stream klase, odnosno da bude pravo kopiranje klase Node.
//Kopiranje Stream-a nema veze sa ovim. Proveriti da li ovo ima veze sa kopiranjem Node-a.
DataTable::DataTable(const DataTable& dt) : doubleColumns(dt.DoubleColumns()), columnNames(dt.ColumnNames()), numberOfRows(dt.NumberOfRows()) {}

std::map<std::string, std::vector<double>> DataTable::DoubleColumns() const {
    return doubleColumns;
}

std::vector<std::string> DataTable::ColumnNames() const {
    return columnNames;
}

unsigned long DataTable::NumberOfRows() const {
    return numberOfRows;
}

void DataTable::addKey(const std::string& keyName)
{
    doubleColumns[keyName] = std::vector <double> (numberOfRows);
    columnNames.push_back(keyName);
}

void DataTable::SetField(std::string columnName, unsigned long index, double value){

    doubleColumns[columnName][index] = value;
}