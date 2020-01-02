#include <ClassificationNode.hpp>

ClassificationNode::ClassificationNode(std::string name) : Node::Node(name){
    targetColumnName = "";
}

bool ClassificationNode::IsVariableSelected(){
    return !(targetColumnName.compare("") == 0);
}

arma::Row<size_t> ClassificationNode::TargetColumn() const {
    return targetColumn;
}

std::string ClassificationNode::TargetColumnName() const {
    return targetColumnName;
}

arma::Row<size_t> ClassificationNode::TransformToArma(){

    std::vector<std::string> vectorOfNames = Node::unbinarize(targetColumnName);

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

void ClassificationNode::setTarget(std::string targetName) {
    //TODO: check if targetName is in columnNames
    targetColumnName = targetName;

    targetColumn = TransformToArma();
}
