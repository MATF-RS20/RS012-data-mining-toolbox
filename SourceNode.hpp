#ifndef SOURCENODE_HPP
#define SOURCENODE_HPP

#include "Node.hpp"

// Node that reads data from file
// TODO: implement it
class SourceNode : public Node{

public:

    SourceNode(std::string name);
    void setFilename(std::string fName);

    void run() override;

private:
    std::string filename;
};

#endif // SOURCENODE_HPP
