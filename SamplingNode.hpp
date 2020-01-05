#ifndef SAMPLINGNODE_H
#define SAMPLINGNODE_H

#include "Node.hpp"

class SamplingNode : public Node {

public:

    SamplingNode(std::string name);

    void run() override;

    double SampleSizeRatio() const;

    void SetSampleSizeRatio(const double &size);

private:

    double sampleSizeRatio;
};

#endif // SAMPLINGNODE_H
