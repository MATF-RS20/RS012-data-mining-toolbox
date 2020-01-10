#ifndef DATATABLE_H
#define DATATABLE_H

#include <map>
#include <vector>
#include <mlpack/core.hpp>

class DataTable {

public:

    // we need empty constructor because of Node member variable outputDataTable
    DataTable();

    // TODO: implement copy constuctor and operator '='
    DataTable(const DataTable& dt);
    /*DataTable& operator= (const DataTable& dt);
    DataTable(DataTable&& dt);
    DataTable& operator= (DataTable&& dt);*/

    ~DataTable();

    arma::mat DataMatrix() const;
    std::vector<std::string> ColumnNames() const;
    std::map<std::string, std::set<std::string>> CategoricalValues() const;

    void SetDataMatrix(const arma::mat& matrix);
    void addKey(const std::string& keyName);
    void addCategoricalValues(unsigned columnIndex, std::set<std::string>);
    void SetCategoricalValues(const std::map<std::string, std::set<std::string>> & catVal);
    void SetColumnNames(const std::vector<std::string>& colNames);


/********************************************************************************************************/
    std::vector<bool> Partition() const;
    bool IsPartitioned() const;
    unsigned long TestSize() const;

    void SetPartition(const std::vector<bool>& vector);
    void SetIsPartitioned(const bool & isSet);
    void SetTestSize(const unsigned long& size);
/********************************************************************************************************/

private:

    arma::mat dataMatrix;
    std::vector<std::string> columnNames;
    std::map<std::string, std::set<std::string>> categoricalValues;
    std::vector<bool> partition;
    unsigned long testSize;
    bool isPartitioned = false;



/********************************************************************************************************/
    
/********************************************************************************************************/
};

#endif // DATATABLE_H
