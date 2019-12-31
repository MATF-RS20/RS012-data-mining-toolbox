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
    std::vector<std::string> ClassTargetVariable() const;
    bool HasClassTargetVariable() const;
    std::vector<bool> Partition() const;
    bool IsPartitioned() const;

    void SetDataMatrix(const arma::mat& matrix);
    void addKey(const std::string& keyName);
    void SetClassTargetVariable(const std::vector<std::string>& stringColumn);

    //TODO: consider a better name :)
    void SetHasClassTargetVariable(const bool & isSet);

    void SetPartition(const std::vector<bool>& vector);
    void SetIsPartitioned(const bool & isSet);

private:

    arma::mat dataMatrix;
    std::vector<std::string> columnNames;

    //TODO: consider if this needs to be in DataTable
    std::vector<std::string> classTargetVariable;
    bool hasClassTargetVariable;

    std::vector<bool> partition;
    bool isPartitioned;

};

#endif // DATATABLE_H
