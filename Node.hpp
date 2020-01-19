#ifndef NODE_H
#define NODE_H

#include "DataTable.hpp"

//Node is an abstract class that represents all the nodes in GUI. It has an abstract function run, that is specific for every 
//subclass since every node that we will have in GUI has its own purpose. Since stream in GUI consists of nodes that are connected
//and the output of one node (algorithm) is input for the next, every object of class Node will have atributes inputDataTable and
//outputDataTable which will serve above mentioned purpose. Additionally, every node has an atribute that will represent its name.
class Node{

public:

    //Constructor and destructor
    Node(std::string name);
    virtual ~Node() = default;

    //Getters
    const DataTable* InputDataTable() const;
    DataTable OutputDataTable() const;
    std::string NodeName() const;
    //TODO: DELETE!!!
    DataTable* RefOutputDataTable();

    //Setters
    void setInputDataTable(DataTable* inDataTable);
    void setOutDataTable(DataTable outDataTable);

    //Methods needed for classification:
    //for getting original "unbinarized" target categorical column that containes class, 
    std::vector<std::string> unbinarize(std::string columnName) const;
    //and removing it from data
    arma::mat filterBinarisedCol(std::string colName);
    //Method needed for linear regression: removing target column from data
    DataTable filter(std::string colName);

    // run is an action that a Node can do (preform clustering/classification, normalize, standardize...)
    virtual void run() = 0;

protected:

    // inputDataTable of Node B points to outputDataTable of Node A where A -> B
    const DataTable* inputDataTable;
    //output of Node is contained in outputDataTable
    DataTable outputDataTable;
    std::string nodeName;



};

#endif // NODE_H
