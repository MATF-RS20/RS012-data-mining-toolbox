#ifndef KMEANS_HPP
#define KMEANS_HPP

#include "ClusteringNode.hpp"

class KMeansNode : public ClusteringNode {
public:
    enum class distances {
        ManhattanDistance,
        EuclideanDistance,
        SquaredEuclideanDistance,
        ChebyshevDistance

    };
    KMeansNode(std::string name);
    KMeansNode(std::string name, size_t numClus);
    KMeansNode(std::string name, distances d);
    KMeansNode(std::string name, size_t numClus, size_t maxNumIter);
    KMeansNode(std::string name, size_t numClus, distances d);
    KMeansNode(std::string name, distances d, size_t maxNumIter);
    KMeansNode(std::string name, size_t numClus, distances d, size_t maxNumIter);


    size_t NumberOfClusters();
    void SetNumberOfClusters(size_t number);

    distances Distance();
    void SetDistance(distances dist);

    size_t MaxNumberOfIterations();
    void SetMaxNumberOfIterations(size_t number);

    void run() override;

private:
    size_t numberOfClusters;
    distances distance;
    size_t maxNumberOfIterations;
};

#endif // KMEANS_HPP
