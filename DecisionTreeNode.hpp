#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

#include "ClassificationNode.hpp"

class DecisionTree : public ClassificationNode{

public:

    DecisionTree(std::string name);

    int MaximumDepth() const;
    int MinimumLeafSize() const;

    void SetMaximumDepth(int depth);
    void SetMinimumLeafSize(int size);

private:

    int maximumDepth;
    int minimumLeafSize;


};

#endif // DECISIONTREENODE_H
