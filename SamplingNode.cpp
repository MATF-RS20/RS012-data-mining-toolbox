#include "SamplingNode.hpp"  

//Constructor
SamplingNode::SamplingNode(std::string name):Node(name){
    sampleSizeRatio = 0.3;
}

//Getter
double SamplingNode::SampleSizeRatio() const{
    return sampleSizeRatio;
}

//Setter
void SamplingNode::SetSampleSizeRatio(const double &size){
    sampleSizeRatio = size;
}

void SamplingNode::run(){
    
    //Making a vector with a field for every tuple that indicates whether the tuple goes into the sample
    unsigned long rowSize = InputDataTable()->DataMatrix().n_rows;
    std::vector<bool> sample(rowSize);

    //Setting n (sample size) elements of vector to true indicating that sample size elements will be taken
    // for sample. Setting the rest of elements to false.
    unsigned long sampleSize = static_cast<unsigned long>(static_cast<double>(rowSize)*SampleSizeRatio());
    for(unsigned long i = 0; i < sampleSize; i++){
        sample[i] = true;
    }
    for(unsigned long long i = sampleSize; i < rowSize; i++){
        sample[i] = false;
    }
    
    //Shuffling the vector to obtain a random sample
    srand(time(0));
    std::random_shuffle(sample.begin(), sample.end());

    //Making new data matrix by sampling from the current one using the vector for sampling
    unsigned long colSize = InputDataTable()->DataMatrix().n_cols;
    arma::mat newData(sampleSize, colSize);
    arma::mat oldData = InputDataTable()->DataMatrix();
    unsigned long k = 0;
    for (unsigned long i = 0; i < rowSize; i++){
        if (sample[i] == true){
            
            for (unsigned long j = 0; j < colSize; j++) {
                newData(k, j) = oldData(i, j);
            }
            k++;
        }
    }

    //Setting output data table data matrix to the new data matrix
    DataTable dt = *(this->InputDataTable());
    dt.SetDataMatrix(newData);
    this->setOutDataTable(dt);

}
