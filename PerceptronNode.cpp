#include <mlpack/methods/perceptron/perceptron.hpp>
#include "PerceptronNode.hpp"

#include <string>

PerceptronNode::PerceptronNode(std::string name):ClassificationNode(name){}

void PerceptronNode::run() {
    
    if (!this->IsVariableSelected()){
        std::cout << "Target variable not selected" << std::endl;
        DataTable dt = *InputDataTable();
        this->setOutDataTable(dt);
        return;
    }    
    targetColumn = TransformToArma();
    
    DataTable dt = filter(targetColumnName);
    arma::mat data = dt.DataMatrix();
    
    if(!dt.IsPartitioned()){

        data = trans(data);
        mlpack::perceptron::Perceptron<> perceptronClassifier(data, this->targetColumn, 3);
        perceptronClassifier.Train(data, this->targetColumn);

        arma::Row<size_t> predictions(this->targetColumn.size());
        perceptronClassifier.Classify(data, predictions);
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
        mlpack::perceptron::Perceptron<> perceptronClassifier(trainData, trainTarget, 3);
        perceptronClassifier.Train(trainData, trainTarget);
        
        arma::Row<size_t> predictions(testTarget.size());
        perceptronClassifier.Classify(testData, predictions);
        std::cout << "Predictions: " << std::endl;
        std::cout << predictions << std::endl;
        
        double precision = ClassificationNode::Precision(testTarget, predictions);
        std::cout << precision << std::endl;
        
        ClassificationNode::ConfussionMatrix(testTarget, predictions);
    }
        
    DataTable dataTable = *InputDataTable();
        this->setOutDataTable(dataTable);
        
        
    }
