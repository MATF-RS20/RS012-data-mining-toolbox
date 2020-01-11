#include "PartitionNode.hpp"

#include <algorithm>
#include <stdlib.h>    
#include <time.h>  

PartitionNode::PartitionNode(std::string name):Node(name){
    testSizeRatio = 0.3;
}

double PartitionNode::TestSizeRatio() const{
    return testSizeRatio;
}

void PartitionNode::SetTestSizeRatio(const double &size){
    testSizeRatio = size;
}

void PartitionNode::run(){

    unsigned long rowSize = InputDataTable()->DataMatrix().n_rows;
    std::vector<bool> partition(rowSize);

    unsigned long testSize = static_cast<unsigned long>(static_cast<double>(rowSize)*TestSizeRatio());
    //int trainingSize = rowSize - testSize;
    for(unsigned long i = 0; i < testSize; i++){
        partition[i] = true;
    }
    for(unsigned long long i = testSize; i < rowSize; i++){
        partition[i] = false;
    }
    
    srand(time(0));
    std::random_shuffle(partition.begin(), partition.end());

    DataTable dt = *InputDataTable();
    
    this->setOutDataTable(dt);
    outputDataTable.SetIsPartitioned(true);
    outputDataTable.SetPartition(partition);
    outputDataTable.SetTestSize(testSize);
}
