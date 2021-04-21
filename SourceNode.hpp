#ifndef SOURCENODE_HPP
#define SOURCENODE_HPP

#include "Node.hpp"
#include "csvreader.hpp"
#include <armadillo>
#include <boost/algorithm/string.hpp>
#include <list>
#include <string>

// Node that reads data from file
class SourceNode : public Node {

public:
  // Constructor
  explicit SourceNode(std::string name);

  // Copy constructor
  SourceNode(const SourceNode &sn);

  // Setter for name of the file from which we read
  void setFilename(const std::string &fName);

  // Getter for name of the file from which we read
  std::string getFileName();

  void read();

  // Run function, specific for this node
  void run() override;

private:
  // Name of the file
  std::string filename;

  // Indicator of whether the file with the set file name is read or not
  bool isRead;
};

#endif // SOURCENODE_HPP
