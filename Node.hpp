#ifndef NODE_H
#define NODE_H

#include "DataTable.hpp"

class Node{

public:

    Node(std::string name);

    virtual ~Node();

    const DataTable* InputDataTable() const;

    DataTable OutputDataTable() const;

    // run is an action that a Node can do (preform clustering/classification, normalize, standardize...)
    virtual void run() = 0;

private:

    // inputDataTable of Node B points to outputDataTable of Node A where A -> B
    const DataTable* inputDataTable;
    DataTable outputDataTable;
    std::string nodeName;



};

#endif // NODE_H
