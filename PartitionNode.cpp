#include "PartitionNode.hpp"

#include <algorithm>

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
    std::random_shuffle(partition.begin(), partition.end());

    OutputDataTable() = *InputDataTable();
    OutputDataTable().SetIsPartitioned(true);
    OutputDataTable().SetPartition(partition);
}