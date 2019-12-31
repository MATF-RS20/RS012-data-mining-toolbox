#include <mlpack/methods/decision_tree/decision_tree.hpp>
#include "DecisionTreeNode.hpp"

#include <string>

DecisionTreeNode::DecisionTreeNode(std::string name):ClassificationNode(name){
    maximumDepth = 0;
    minimumLeafSize = 10;
}

void DecisionTreeNode::run() {

    arma::mat data1 = InputDataTable()->DataMatrix();
    arma::Row<size_t> train_labels = this->TransformToArma();

  /*  arma::mat data;
    mlpack::data::Load("../RS012-data-mining-toolbox/zoo.csv", data);*/

    // target column (used just for testing)
    //arma::vec responses = arma::vec(InputDataTable()->DataMatrix().n_rows, arma::fill::ones);

 /*   std::vector<std::string> columns = InputDataTable()->ClassTargetVariable();
    arma::Row<size_t> train_labels = arma::Row<size_t>(data1.n_rows);
    for(unsigned long i = 0; i < data1.n_rows; i++){
       // std::cout << columns[i] << std::endl;
        std::string tmp  = columns[i].substr(0, columns[i].length() -1);
        if(tmp == "setosa"){
            train_labels(i) = 0;
        } else if (tmp == "versicolor"){
            train_labels(i) = 1;
        } else if (tmp == "virginica"){
            train_labels(i) = 2;
        }
    }*/

   // std::cout << data1.n_cols << " " << data1.n_rows << " " << train_labels.n_cols << " " << train_labels.n_rows << std::endl;

 /*   std::cout << data1 << std::endl;
    std::cout << std::endl << std:: endl << std::endl;
    std::cout << train_labels << std::endl;*/

    data1 = trans(data1);
    mlpack::tree::DecisionTree<> treeClassifier;
    treeClassifier.Train(data1, train_labels, 3);

    arma::Row<size_t> predictions;
    treeClassifier.Classify(data1, predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;
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
