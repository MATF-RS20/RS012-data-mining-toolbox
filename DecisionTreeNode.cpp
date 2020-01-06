#include <mlpack/methods/decision_tree/decision_tree.hpp>
#include "DecisionTreeNode.hpp"

#include <string>

DecisionTreeNode::DecisionTreeNode(std::string name):ClassificationNode(name){
    maximumDepth = 0;
    minimumLeafSize = 10;
}

void DecisionTreeNode::run() {

    if (!this->IsVariableSelected()){
        std::cout << "Target variable not selected" << std::endl;
        DataTable dt = *InputDataTable();
        this->setOutDataTable(dt);
        return;
    }    
    targetColumn = TransformToArma();
    
    DataTable dt = filter(targetColumnName);
    arma::mat data = dt.DataMatrix();

    data = trans(data);
    mlpack::tree::DecisionTree<> treeClassifier;
    treeClassifier.Train(data, this->targetColumn, 3);

    arma::Row<size_t> predictions;
    treeClassifier.Classify(data, predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;
    
    double precision = ClassificationNode::Precision(predictions);
    std::cout << precision << std::endl;
    
    DataTable dataTable = *InputDataTable();
    this->setOutDataTable(dataTable);
}

int DecisionTreeNode::MaximumDepth() const{
    return maximumDepth;
}
int DecisionTreeNode::MinimumLeafSize() const{
    return minimumLeafSize;
}

void DecisionTreeNode::SetMaximumDepth(int depth){
    maximumDepth = depth;
}
void DecisionTreeNode::SetMinimumLeafSize(int size){
    minimumLeafSize = size;
}
