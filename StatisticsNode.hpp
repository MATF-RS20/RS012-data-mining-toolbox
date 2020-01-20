#ifndef STATISTICSNODE_HPP
#define STATISTICSNODE_HPP

#include "Node.hpp"
#include <string.h>

//Statistics of data
class StatisticsNode : public Node {

public:

    //Constructor
    StatisticsNode(std::string name);

    //Getter
    std::string GetStatistics() const;

    void run() override;
    
private:
    
    //Atribute which will contain a string representation of the statistic
    std::string statistics;

};

#endif // STATISTICSNODE_HPP
