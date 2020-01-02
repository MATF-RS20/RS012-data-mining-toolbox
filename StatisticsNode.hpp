#ifndef STATISTICSNODE_HPP
#define STATISTICSNODE_HPP

#include "Node.hpp"

class StatisticsNode : public Node {

public:

    StatisticsNode(std::string name);

    void run() override;

};

#endif // STATISTICSNODE_HPP
