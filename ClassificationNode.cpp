#include <ClassificationNode.hpp>

#include <map>

ClassificationNode::ClassificationNode(std::string name) : Node::Node(name){
    //targetVariable = std::vector<std::string>(Node::InputDataTable()->DataMatrix().n_rows);
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

arma::Row<size_t> ClassificationNode::TransformToArma(){

    std::vector<std::string> vectorOfNames = this->InputDataTable()->ClassTargetVariable();

    int label_index = 0;
    std::map<std::string, int> mapOfNames;

    mapOfNames[vectorOfNames[0]] = label_index;
    label_index++;

    for(unsigned long i = 1; i < vectorOfNames.size(); i++){
        if (mapOfNames.find(vectorOfNames[i]) == mapOfNames.end()){
            mapOfNames[vectorOfNames[i]] = label_index;
            label_index++;
        }
    }

    arma::Row<size_t> labels(vectorOfNames.size());
    for (unsigned long i = 0; i < vectorOfNames.size(); i++){
        labels(i) =  static_cast<size_t>(mapOfNames[vectorOfNames[i]]);
    }

    return labels;

}
