#ifndef CLASSIFICATIONNODE_H
#define CLASSIFICATIONNODE_H

#include "Node.hpp"

class ClassificationNode : public Node{

public:

    ClassificationNode(std::string name);

    bool IsVariableSelected();

    std::vector<std::string> TargetVariable() const;

    void SetTargetVariable(std::vector<std::string> Variable);

private:

    std::vector<std::string> targetVariable;

};

#endif // CLASSIFICATIONNODE_H
