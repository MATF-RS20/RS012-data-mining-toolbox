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
    
    if (!dt.IsPartitioned()){

        data = trans(data);
        mlpack::tree::DecisionTree<> treeClassifier;
        treeClassifier.Train(data, this->targetColumn, 3);

        arma::Row<size_t> predictions;
        treeClassifier.Classify(data, predictions);
        std::cout << "Predictions: " << std::endl;
        std::cout << predictions << std::endl;
        
        double precision = ClassificationNode::Precision(targetColumn, predictions);
        std::cout << precision << std::endl;
        
        ClassificationNode::ConfussionMatrix(targetColumn, predictions);
    } else {
        
        arma::mat testData(dt.TestSize(), data.n_cols);
        arma::mat trainData(data.n_rows - dt.TestSize(), data.n_cols);
        
        arma::Row<size_t> testTarget(dt.TestSize());
        arma::Row<size_t> trainTarget(data.n_rows - dt.TestSize());
        
        std::vector<bool> partition = dt.Partition();
        
        unsigned long train_index = 0;
        unsigned long test_index = 0;
        for(unsigned long i = 0; i < data.n_rows; i++){
            if (partition[i]){
                testTarget[test_index] = targetColumn[i];
                for(unsigned long j = 0; j < data.n_cols; j++){
                    testData(test_index, j) = data(i, j);
                }
                test_index++;
            } else {
                trainTarget[train_index] = targetColumn[i];
                for(unsigned long j = 0; j < data.n_cols; j++){
                    trainData(train_index, j) = data(i, j);
                }
                train_index++;
            }
        }
        
        trainData = trans(trainData);
        testData = trans(testData);
        mlpack::tree::DecisionTree<> treeClassifier;
        treeClassifier.Train(trainData, trainTarget, 3);

        arma::Row<size_t> predictions;
        treeClassifier.Classify(testData, predictions);
        std::cout << "Predictions: " << std::endl;
        std::cout << predictions << std::endl;
        
        double precision = ClassificationNode::Precision(testTarget, predictions);
        std::cout << precision << std::endl;
        
        ClassificationNode::ConfussionMatrix(testTarget, predictions);
        
    }
    
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
