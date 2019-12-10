#ifndef DATATABLE_H
#define DATATABLE_H

#include <map>
#include <vector>

class DataTable {

public:

    // we need empty constructor because of Node member variable outputDataTable
    DataTable();

    DataTable(int nRows);

    // TODO: implement copy constuctor and operator =

    ~DataTable();

    std::map<std::string, std::vector<double>> DoubleColumns() const;

    // sets field where column is columnName and row is index
    void SetField(std::string columnName, unsigned long index, double value);

private:

    //map that stores all columns of data
    //TODO: generic ?
    std::map<std::string, std::vector<double>> doubleColumns;

    int numberOfRows;
};

#endif // DATATABLE_H
