#ifndef RUNTIME_GRAPH_MANAGER_H
#define RUNTIME_GRAPH_MANAGER_H

#include <string>
#include <vector>

#include "../graph/node.h"
#include "rpc/protos/node_def.pb.h"

using dml::NodeDef;

class GraphManager {
 public:
  GraphManager(const std::string filename);
  std::vector<Node> graph();
  std::vector<NodeDef> graphDef();
  Node* getNodeAtIndex(int idx);
  int size();

 private:
  std::vector<Node> graph_;
};

#endif // RUNTIME_DEVICE_MANAGER_H