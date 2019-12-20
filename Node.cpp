#include "Node.hpp"

Node::Node(std::string name) : nodeName(name){}

Node::~Node(){}

const DataTable* Node::InputDataTable() const{
    return inputDataTable;
}

DataTable Node::OutputDataTable() const {
    return outputDataTable;
}

//TODO: Proveriti da li je ovo neophodno! Dodato u pokusaju da se pozove konstruktor Node klase u konstruktoru kopije klase SourceNode
std::string Node::NodeName() const {
    return nodeName;
}

//TODO: Proveriti da li je ovo neophodno! Dodato u pokusaju da proradi destruktor Stream klase
DataTable * Node::RefOutputDataTable(){
    return &outputDataTable;
}

void Node::setInputDataTable(DataTable* inDataTable)
{
    inputDataTable = inDataTable;
}

void Node::setOutDataTable(DataTable outDataTable)
{
    outputDataTable = outDataTable;
}
