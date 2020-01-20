#ifndef KMEANS_HPP
#define KMEANS_HPP

#include "ClusteringNode.hpp"
#include "mlpack/methods/kmeans/kmeans.hpp"

class KMeansNode : public ClusteringNode {
public:
    //Set of values for parameter distance
    enum class distances {
        ManhattanDistance,
        EuclideanDistance,
        SquaredEuclideanDistance,
        ChebyshevDistance

    };

    //Constructors
    KMeansNode(std::string name);
    KMeansNode(std::string name, size_t numClus);
    KMeansNode(std::string name, distances d);
    KMeansNode(std::string name, size_t numClus, size_t maxNumIter);
    KMeansNode(std::string name, size_t numClus, distances d);
    KMeansNode(std::string name, distances d, size_t maxNumIter);
    KMeansNode(std::string name, size_t numClus, distances d, size_t maxNumIter);

    //Getters
    size_t NumberOfClusters();
    distances Distance();
    size_t MaxNumberOfIterations();

    //Setters
    void SetNumberOfClusters(size_t number);
    void SetDistance(distances dist);
    void SetMaxNumberOfIterations(size_t number);

    void run() override;

private:
    //Parameters
    size_t numberOfClusters;
    distances distance;
    size_t maxNumberOfIterations;
};

#endif // KMEANS_HPP
