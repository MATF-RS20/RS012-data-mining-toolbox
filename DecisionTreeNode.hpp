#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

#include "ClassificationNode.hpp"
#include <mlpack/methods/decision_tree/decision_tree.hpp>
#include <string>


//Class representing Decision Tree
class DecisionTreeNode : public ClassificationNode{

public:

    //Constructor
    DecisionTreeNode(std::string name);

    //Getters
    int MaximumDepth() const;
    int MinimumLeafSize() const;

    //Setters
    void SetMaximumDepth(int depth);
    void SetMinimumLeafSize(int size);

    void run() override;

private:

    //Parameters
    int maximumDepth;
    int minimumLeafSize;
};

#endif // DECISIONTREENODE_H
