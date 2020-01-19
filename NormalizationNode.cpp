#include "NormalizationNode.hpp"

NormalizationNode::NormalizationNode(std::string name) : Node(name) {}

void NormalizationNode::run() {

    arma::mat data = this->InputDataTable()->DataMatrix();

    //Find max and min value for every column, and then transform every value with this expression:
        //(value - min)/(max - min)
    for(unsigned long j = 0; j < data.n_cols; j++){
        double min_value = data(0, j);
        double max_value = data(0, j);
        for(unsigned long i = 1; i < data.n_rows; i++){
            if (data(i, j) > max_value){
                max_value = data(i, j);
            } else if (data(i, j) < min_value){
                min_value = data(i, j);
            }
        }

        for(unsigned long i = 0; i < data.n_rows; i++){
            data(i, j) = (data(i, j) - min_value)/(max_value - min_value);
        }
    }

    DataTable dt = *(this->InputDataTable());
    dt.SetDataMatrix(data);

    this->setOutDataTable(dt);
}
