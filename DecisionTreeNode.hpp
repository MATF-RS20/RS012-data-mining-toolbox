#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

#include "ClassificationNode.hpp"

class DecisionTreeNode : public ClassificationNode{

public:

    DecisionTreeNode(std::string name);

    int MaximumDepth() const;
    int MinimumLeafSize() const;

    void SetMaximumDepth(int depth);
    void SetMinimumLeafSize(int size);

    void run() override;

private:

    int maximumDepth;
    int minimumLeafSize;


};

#endif // DECISIONTREENODE_H
