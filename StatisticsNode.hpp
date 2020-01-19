#ifndef STATISTICSNODE_HPP
#define STATISTICSNODE_HPP

#include "Node.hpp"

class StatisticsNode : public Node {

public:

    StatisticsNode(std::string name);

    void run() override;
    
    std::string GetStatistics() const;
    
private:
    
    std::string statistics;

};

#endif // STATISTICSNODE_HPP
