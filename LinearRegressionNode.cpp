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
    std::map<std::string, std::set<std::string>> map = inputDataTable->CategoricalValues();
    size_t index = 0;
    for(unsigned i = 0; i < columns.size(); i++) {
        if(0 == columns[i].compare(targetColumnName)) {
            if(map.find(targetColumnName) != map.end()) {
                std::cout << "Greska! Izabrana kolona sa kategorickom vrednoscu!" << std::endl;
                return;
            }
            else {
                auto matrix = inputDataTable->DataMatrix();
                targetColumn.set_size(matrix.n_rows);
                std::copy(matrix.begin_col(index), matrix.end_col(index), targetColumn.begin());
            }
            break;
        }

        if(map.find(columns[i]) != map.end()) {

            index += map.at(columns[i]).size();
        } else {

             index++;
        }
    }
}

void LinearRegressionNode::RSS(arma::Col<double> values, arma::Col<double> predictions){
    
    size_t nRows = values.size();
    double sum = 0;
    
    for(unsigned long i = 0; i < nRows; i++){
    
        sum += (values[i] - predictions[i])*(values[i] - predictions[i]);
        
    }

    SetRssScore(sum);
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
    
    if (!dt.IsPartitioned()){

        data = trans(data);
        mlpack::regression::LinearRegression lr(data, targetColumn);

        SetParams(lr.Parameters());
        std::cout << "Parameters: " << std::endl;
        std::cout << Params() << std::endl;

        arma::Row<double> predictions;
        lr.Predict(data, predictions);
        std::cout << "Predictions: " << std::endl;
        std::cout << predictions << std::endl;
        
        RSS(targetColumn, predictions);
        std::cout << RssScore() << std::endl;
        
        SetTargetPredictions(predictions);
        
    } else {

        arma::mat testData(dt.TestSize(), data.n_cols);
        arma::mat trainData(data.n_rows - dt.TestSize(), data.n_cols);
        
        arma::Col<double> testTarget(dt.TestSize());
        arma::Col<double> trainTarget(data.n_rows - dt.TestSize());
        
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
        
        mlpack::regression::LinearRegression lr(trainData, trainTarget);

        SetParams(lr.Parameters());
        std::cout << "Parameters: " << std::endl;
        std::cout << Params() << std::endl;
        
        arma::Row<double> predictions;
        lr.Predict(testData, predictions);
        std::cout << "Predictions: " << std::endl;
        std::cout << predictions << std::endl;
        
        RSS(testTarget, predictions);
        std::cout << RssScore() << std::endl;
        
        arma::Row<double> allPredictions;
        data = trans(data);
        lr.Predict(data, allPredictions);
        SetTargetPredictions(allPredictions);
        std::cout << TargetPredictions() << std::endl;
    }

    DataTable dataTable = *InputDataTable();
    this->setOutDataTable(dataTable);
}

arma::Col<double> LinearRegressionNode::TargetPredictions() const{
    return targetPredictions;
}
    
void LinearRegressionNode::SetTargetPredictions(const arma::Col<double> predictions){
    targetPredictions = predictions;
}

double LinearRegressionNode::RssScore() const{
    return rssScore;
}

void LinearRegressionNode::SetRssScore(const double& score){
    rssScore = score;
}
    
arma::vec LinearRegressionNode::Params() const{
    return params;
}

void LinearRegressionNode::SetParams(const arma::vec& parameters){
    params = parameters;
}



