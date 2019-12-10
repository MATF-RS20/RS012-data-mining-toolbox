#include "Node.hpp"

Node::Node(std::string name) : nodeName(name){}

Node::~Node(){}

const DataTable* Node::InputDataTable() const{
    return inputDataTable;
}

DataTable Node::OutputDataTable() const {
    return outputDataTable;
}


