#include "LinearRegressionNode.hpp"

#include <mlpack/methods/linear_regression/linear_regression.hpp>

LinearRegressionNode::LinearRegressionNode(std::string name)
    :Node(name){}

LinearRegressionNode::~LinearRegressionNode(){}

bool LinearRegressionNode::IsTargetSelected() const{
    return !(targetColumnName.compare("") == 0);
}

void LinearRegressionNode::setTarget(std::string targetName) {
    targetColumnName = targetName;

}

void LinearRegressionNode::SetTargetColumn() {
    
    std::vector<std::string> columns = inputDataTable->ColumnNames();
    for(unsigned i = 0; i < columns.size(); i++) {
        if(0 == columns[i].compare(targetColumnName)) {
            std::map<std::string, std::set<std::string>> map = inputDataTable->CategoricalValues();
            if(map.find(targetColumnName) != map.end()) {
                std::cout << "Greska! Izabrana kolona sa kategorickom vrednoscu!" << std::endl;
                return;
            }
            else {
                targetColumn = *(inputDataTable->DataMatrix().begin_col(i));
            }
        }
    }
}

void LinearRegressionNode::run(){
    
    if (!this->IsTargetSelected()){
        std::cout << "Target variable not selected" << std::endl;
        DataTable dt = *InputDataTable();
        this->setOutDataTable(dt);
        return;
    }
    
    this->SetTargetColumn();
    
    DataTable dt = filter(targetColumnName);
    arma::mat data = dt.DataMatrix();
    mlpack::regression::LinearRegression lr(trans(data), targetColumn);

    arma::vec parameters = lr.Parameters();
    std::cout << "Paramtetes: " << std::endl;
    std::cout << parameters << std::endl;

    arma::Col<double> predictions;
    lr.Predict(trans(data), predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;
}
