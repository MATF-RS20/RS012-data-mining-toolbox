#include <ClassificationNode.hpp>
#include <algorithm>
#include <string.h>

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

size_t ClassificationNode::NumClasses() const{
    return numClasses;
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

void ClassificationNode::SetNumClasses(const size_t& size){
    numClasses = size;
}

void ClassificationNode::Precision(arma::Row<size_t> values, arma::Row<size_t> predictions) {
    
    size_t nRows = values.size();
    int nTrue = 0;
    for(unsigned long i = 0; i < nRows; i++){
        if (values[i] == predictions[i]){
            nTrue++;
        }
    }
    
    if (nRows == 0){
        precision = "Precision: 0.0\n";
        return;
    }
    
    double prec = static_cast<double>(nTrue)/nRows;
    
    precision = "Precision: " + std::to_string(prec) + "\n";  
    
}

void ClassificationNode::ConfusionMatrix(arma::Row<size_t> values, arma::Row<size_t> predictions) {
    
    auto it = std::max_element(std::begin(predictions), std::end(predictions));
    size_t maximum = *it;
    unsigned long nRows = values.size();
    
    int nMatch;
    std::string result = "T-P ";
    for(size_t pLabel = 0; pLabel <= maximum; pLabel++){
        result += std::to_string(pLabel);
        result += " ";
    }
    result += "\n";
    for(size_t tLabel = 0; tLabel <= maximum; tLabel++){
        result += std::to_string(tLabel);
        result += " ";
        for (size_t pLabel = 0; pLabel <= maximum; pLabel++){
            nMatch = 0;
            for (unsigned long i = 0; i < nRows; i++){
                if(values[i] == tLabel && predictions[i] == pLabel){
                    nMatch++;
                }
            }
            result += std::to_string(nMatch);
            result += " ";
        }
        result += "\n";
    }
    
    confusionMatrix = result;
    
}

std::string ClassificationNode::GetPrecision() const{
    return precision;
}
    
std::string ClassificationNode::GetConfusionMatrix() const {
    return confusionMatrix;
}

void ClassificationNode::SetClassPredictions(const arma::Row<size_t> predictions){
    classPredictions = predictions;
}

arma::Row<size_t> ClassificationNode::ClassPredictions() const{
    return classPredictions;
}
    





