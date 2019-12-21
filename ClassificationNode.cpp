#include <ClassificationNode.hpp>

ClassificationNode::ClassificationNode(std::string name) : Node::Node(name){
    targetVariable = std::vector<std::string>(Node::InputDataTable()->DataMatrix().n_rows);
}

bool ClassificationNode::IsVariableSelected(){
    return !targetVariable.empty();
}

std::vector<std::string> ClassificationNode::TargetVariable() const{
    return targetVariable;
}

void ClassificationNode::SetTargetVariable(std::vector<std::string> Variable){
    targetVariable = Variable;
}
