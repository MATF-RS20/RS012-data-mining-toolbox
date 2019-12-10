#ifndef STREAM_H
#define STREAM_H

#include <map>
#include <list>
#include "Node.hpp"

// TODO: implement class Stream
class Stream{

public:

    Stream();

    ~Stream();

    // adds an unconnected node to the stream
    void add (Node& node);

    // connects node1 to node2
    void connect_to(Node& node1, Node& node2);

    // disconnects nodes
    void disconnect(Node& node1, Node& node2);

    // performs a recursive call of run method from "targetNode" to a source node
    DataTable RunStream(Node& targetNode);

    std::map<const Node*, Node&> MapOfNodes() const;

private:

    // map that contains pairs of nodes (A, B) where B -> A
    std::map<const Node*, Node&> mapOfNodes;

};

#endif // STREAM_H
