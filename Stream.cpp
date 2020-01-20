#include "Stream.hpp"

#include <iostream>

Stream::Stream(){}

// TODO: fix destructor
Stream::~Stream(){

    for (auto pair : mapOfNodes){
        disconnect(pair.first);
    }
    for (auto iter = mapOfNodes.begin(); iter != mapOfNodes.end(); iter++){
          mapOfNodes.erase(iter);
      }
}

//TODO: Kopiranje Stream-a ne radi, zbog pokazivaca u mapi. Naci novi nacin za cuvanje strima ili drugacije implementirati kopiranje.
Stream::Stream(const Stream& s) : mapOfNodes(s.MapOfNodes()) {}

Stream& Stream::operator= (const Stream& s){
    this->mapOfNodes = s.MapOfNodes();
    return *this;
}

void Stream::add(Node *node){
    mapOfNodes[node] = nullptr;
}

void Stream::connect_to(Node *node1, Node *node2){
    mapOfNodes[node2] = node1;
    node2->setInputDataTable((node1->RefOutputDataTable()));
}

// TODO: change disconnect function so it disconnects node 2 from all nodes it has connections to
void Stream::disconnect(Node *node2){
    mapOfNodes[node2] = nullptr;
    node2->setInputDataTable(nullptr);
}

void Stream::RunStream(Node *targetNode){
    if(dynamic_cast<SourceNode*>(targetNode)) {
    } else {
        RunStream(mapOfNodes[targetNode]);
    }
    targetNode->run();
}

std::map<Node*, Node*> Stream::MapOfNodes() const{
    return mapOfNodes;
}
