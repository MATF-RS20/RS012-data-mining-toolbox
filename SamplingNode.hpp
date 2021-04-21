#ifndef SAMPLINGNODE_H
#define SAMPLINGNODE_H

#include "Node.hpp"
#include <algorithm>
#include <stdlib.h>
#include <time.h>

// Taking a sample of existing data
class SamplingNode : public Node {

public:
  // Constructor
  SamplingNode(std::string name);

  // Getter
  double SampleSizeRatio() const;

  // Setter
  void SetSampleSizeRatio(const double &size);

  void run() override;

private:
  // Size ration of the sample
  double sampleSizeRatio;
};

#endif // SAMPLINGNODE_H
