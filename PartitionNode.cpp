#include "PartitionNode.hpp"

//Constructor
PartitionNode::PartitionNode(std::string name):Node(name){
    testSizeRatio = 0.3;
}

//Getter
double PartitionNode::TestSizeRatio() const{
    return testSizeRatio;
}

//Setter
void PartitionNode::SetTestSizeRatio(const double &size){
    testSizeRatio = size;
}

void PartitionNode::run(){

    //Making a vector that contains field for every tuple, indicating whether the tuple belongs to the train or to the test set
    unsigned long rowSize = InputDataTable()->DataMatrix().n_rows;
    std::vector<bool> partition(rowSize);

    //Finding size of test set
    unsigned long testSize = static_cast<unsigned long>(static_cast<double>(rowSize)*testSizeRatio);
    //int trainingSize = rowSize - testSize;
    //Inserting adequate number of true/false values (true is for test)
    for(unsigned long i = 0; i < testSize; i++){
        partition[i] = true;
    }
    for(unsigned long long i = testSize; i < rowSize; i++){
        partition[i] = false;
    }
    
    //Shuffling the vector in order to get random sets
    srand(time(0));
    std::random_shuffle(partition.begin(), partition.end());

    DataTable dt = *InputDataTable();
    
    //Seting outputDataTable with new data for partition
    this->setOutDataTable(dt);
    outputDataTable.SetIsPartitioned(true);
    outputDataTable.SetPartition(partition);
    outputDataTable.SetTestSize(testSize);
}
