#include "SamplingNode.hpp"

#include <algorithm>

SamplingNode::SamplingNode(std::string name):Node(name){
    sampleSizeRatio = 0.3;
}

double SamplingNode::SampleSizeRatio() const{
    return sampleSizeRatio;
}

void SamplingNode::SetSampleSizeRatio(const double &size){
    sampleSizeRatio = size;
}

void SamplingNode::run(){
    unsigned long rowSize = InputDataTable()->DataMatrix().n_rows;
    std::vector<bool> sample(rowSize);

    unsigned long sampleSize = static_cast<unsigned long>(static_cast<double>(rowSize)*SampleSizeRatio());
    for(unsigned long i = 0; i < sampleSize; i++){
        sample[i] = true;
    }
    for(unsigned long long i = sampleSize; i < rowSize; i++){
        sample[i] = false;
    }
    std::random_shuffle(sample.begin(), sample.end());

    unsigned long colSize = InputDataTable()->DataMatrix().n_cols;
    arma::mat newData(sampleSize, colSize);
    arma::mat oldData = InputDataTable()->DataMatrix();
    
    unsigned long k = 0;
    for (unsigned long i = 0; i < rowSize; i++){
        if (sample[i] == true){
            
            for (unsigned long j = 0; j < colSize; j++) {
                newData(k, j) = oldData(i, j);
                k++;
            }
        }
    }

    DataTable dt = *(this->InputDataTable());
    dt.SetDataMatrix(newData);

    this->setOutDataTable(dt);

}
