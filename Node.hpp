#ifndef NODE_H
#define NODE_H

#include "DataTable.hpp"

class Node{

public:

    Node(std::string name);
    virtual ~Node() = default;

    const DataTable* InputDataTable() const;
    DataTable OutputDataTable() const;
    std::string NodeName() const;
    DataTable* RefOutputDataTable();

    void setInputDataTable(DataTable* inDataTable);
    void setOutDataTable(DataTable outDataTable);

    std::vector<std::string> unbinarize(std::string columnName);
    arma::mat filterBinarisedCol(std::string colName);
    DataTable filter(std::string colName);

    // run is an action that a Node can do (preform clustering/classification, normalize, standardize...)
    virtual void run() = 0;

protected:

    // inputDataTable of Node B points to outputDataTable of Node A where A -> B
    const DataTable* inputDataTable;
    DataTable outputDataTable;
    std::string nodeName;



};

#endif // NODE_H
