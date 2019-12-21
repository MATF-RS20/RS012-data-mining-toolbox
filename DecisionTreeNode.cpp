#include "DecisionTreeNode.hpp"

DecisionTree::DecisionTree(std::string name):ClassificationNode(name){
    maximumDepth = 0;
    minimumLeafSize = 10;
}

int DecisionTree::MaximumDepth() const{
    return maximumDepth;
}
int DecisionTree::MinimumLeafSize() const{
    return minimumLeafSize;
}

void DecisionTree::SetMaximumDepth(int depth){
    maximumDepth = depth;
}
void DecisionTree::SetMinimumLeafSize(int size){
    minimumLeafSize = size;
}
