#include <ClassificationNode.hpp>
#include <algorithm>
#include <string.h>

//Constructor
ClassificationNode::ClassificationNode(std::string name) : Node::Node(name){
    targetColumnName = "";
}

bool ClassificationNode::IsVariableSelected(){
    return !(targetColumnName.compare("") == 0);
}


//Getters
arma::Row<size_t> ClassificationNode::TargetColumn() const {
    return targetColumn;
}

std::string ClassificationNode::TargetColumnName() const {
    return targetColumnName;
}

size_t ClassificationNode::NumClasses() const{
    return numClasses;
}

std::string ClassificationNode::GetPrecision() const{
    return precision;
}

std::string ClassificationNode::GetConfusionMatrix() const {
    return confusionMatrix;
}

arma::Row<size_t> ClassificationNode::ClassPredictions() const{
    return classPredictions;
}

//Setters
void ClassificationNode::setTarget(std::string targetName) {
    //TODO: check if targetName is in columnNames
    targetColumnName = targetName;
}

void ClassificationNode::SetNumClasses(const size_t& size){
    numClasses = size;
}

void ClassificationNode::SetClassPredictions(const arma::Row<size_t> predictions){
    classPredictions = predictions;
}

//Transforming column, a vector of strings, into an arma::Row of ints
arma::Row<size_t> ClassificationNode::TransformToArma(){
    
    //Getting original column from its binarized columns
    std::vector<std::string> vectorOfNames = Node::unbinarize(targetColumnName);

    //Making a map of labels of type int, where key is a class value
    int label_index = 0;
    std::map<std::string, int> mapOfNames;

    mapOfNames[vectorOfNames[0]] = label_index;
    label_index++;

    //Putting adequate ints in the map
    for(unsigned long i = 1; i < vectorOfNames.size(); i++){
        if (mapOfNames.find(vectorOfNames[i]) == mapOfNames.end()){
            mapOfNames[vectorOfNames[i]] = label_index;
            label_index++;
        }
    }

    //Forming a row from the map and vector
    arma::Row<size_t> labels(vectorOfNames.size());
    for (unsigned long i = 0; i < vectorOfNames.size(); i++){
        labels(i) =  static_cast<size_t>(mapOfNames[vectorOfNames[i]]);
    }

    return labels;

}

//Calculating precision of predictions
void ClassificationNode::Precision(arma::Row<size_t> values, arma::Row<size_t> predictions) {
    
    //Getting the number of true predictions
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

//Calculating precision matrix and putting it into a string
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
