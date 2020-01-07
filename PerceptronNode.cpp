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

    data = trans(data);
    mlpack::perceptron::Perceptron<> perceptronClassifier(data, this->targetColumn, 3);
    perceptronClassifier.Train(data, this->targetColumn);

    arma::Row<size_t> predictions(this->targetColumn.size());
    perceptronClassifier.Classify(data, predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;
    
    double precision = ClassificationNode::Precision(predictions);
    std::cout << precision << std::endl;
    
    DataTable dataTable = *InputDataTable();
    this->setOutDataTable(dataTable);
}
