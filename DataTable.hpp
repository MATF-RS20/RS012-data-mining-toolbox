#ifndef DATATABLE_H
#define DATATABLE_H

#include <map>
#include <vector>

class DataTable {

public:

    // we need empty constructor because of Node member variable outputDataTable
    DataTable();

    DataTable(unsigned long nRows);

    // TODO: implement copy constuctor and operator =

    ~DataTable();

    std::map<std::string, std::vector<double>> DoubleColumns() const;
    std::vector<std::string> ColumnNames() const;
    unsigned long NumberOfRows() const;


    void addKey(const std::string& keyName);

    // sets field where column is columnName and row is index
    void SetField(std::string columnName, unsigned long index, double value);

private:

    //map that stores all columns of data
    //TODO: generic ?
    std::map<std::string, std::vector<double>> doubleColumns;

    std::vector<std::string> columnNames;

    unsigned long numberOfRows;
};

#endif // DATATABLE_H
