#ifndef SOURCENODE_HPP
#define SOURCENODE_HPP

#include "Node.hpp"

// Node that reads data from file
class SourceNode : public Node{

public:

    SourceNode(std::string name);
    SourceNode(const SourceNode& sn);
    void setFilename(std::string fName);

    void run() override;

private:
    std::string filename;
};

#endif // SOURCENODE_HPP
