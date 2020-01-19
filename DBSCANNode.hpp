#ifndef DBSCANNODE_HPP
#define DBSCANNODE_HPP

#include "ClusteringNode.hpp"

class DBSCANNode : public ClusteringNode {
public:
    DBSCANNode(std::string name, double e, size_t mp);

    double Eps();
    size_t MinPoints();
    void SetEps(double e);
    void SetMinPoints(size_t mp);
    void run() override;

private:
    double eps;
    size_t minPoints;
};

#endif // DBSCANNODE_HPP
