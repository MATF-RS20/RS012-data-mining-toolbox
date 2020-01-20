#ifndef STREAM_H
#define STREAM_H

#include <map>
#include <list>
#include <SourceNode.hpp>
#include "Node.hpp"

// Class that contains nodes and their connections.
class Stream {

public:

    Stream();

    ~Stream();

    Stream(const Stream& s);
    Stream& operator = (const Stream& s);

    // adds an unconnected node to the stream
    void add (Node* node);

    // connects node1 to node2
    void connect_to(Node* node1, Node* node2);

    // disconnects nodes
    void disconnect(Node* node2);

    // performs a recursive call of run method from "targetNode" to a source node
    void RunStream(Node* targetNode);

    std::map<Node*, Node*> MapOfNodes() const;

private:

    // map that contains pairs of nodes (A, B) where B -> A
    std::map<Node*, Node*> mapOfNodes;

};

#endif // STREAM_H
