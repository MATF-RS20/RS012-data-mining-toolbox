#ifndef SOURCENODE_HPP
#define SOURCENODE_HPP

#include "Node.hpp"
#include <list>
#include <armadillo>

// Node that reads data from file
class SourceNode : public Node{

public:

    SourceNode(std::string name);
    SourceNode(const SourceNode& sn);
    void setFilename(std::string fName);
    void read();

    void run() override;

private:
    std::string filename;
    bool isRead;
};

#endif // SOURCENODE_HPP
