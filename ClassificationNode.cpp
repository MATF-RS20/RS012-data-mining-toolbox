#include <ClassificationNode.hpp>
#include <algorithm>

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
}

double ClassificationNode::Precision(arma::Row<size_t> values, arma::Row<size_t> predictions) const {
    
    int nRows = values.size();
    int nTrue = 0;
    for(unsigned long i = 0; i < nRows; i++){
        if (values[i] == predictions[i]){
            nTrue++;
        }
    }
    
    if (nRows == 0){
        return 0.0;
    }
    
    double precision = static_cast<double>(nTrue)/nRows;
    return precision;
    
    
}

void ClassificationNode::ConfussionMatrix(arma::Row<size_t> values, arma::Row<size_t> predictions) const{
    
    auto it = std::max_element(std::begin(predictions), std::end(predictions));
    size_t maximum = *it;
    unsigned long nRows = values.size();
    
    int nMatch;
    std::cout << "T-P ";
    for(size_t pLabel = 0; pLabel <= maximum; pLabel++){
        std::cout << pLabel << " ";
    }
    std::cout << std::endl;
    for(size_t tLabel = 0; tLabel <= maximum; tLabel++){
        std::cout << tLabel << " ";
        for (size_t pLabel = 0; pLabel <= maximum; pLabel++){
            nMatch = 0;
            for (unsigned long i = 0; i < nRows; i++){
                if(values[i] == tLabel && predictions[i] == pLabel){
                    nMatch++;
                }
            }
            std::cout << nMatch << " ";
        }
        std::cout << std::endl;
    }
    
}
