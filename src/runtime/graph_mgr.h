#ifndef RUNTIME_GRAPH_MANAGER_H
#define RUNTIME_GRAPH_MANAGER_H

#include <map>
#include <string>
#include <vector>

#include "../graph/node.h"
#include "rpc/protos/node_def.pb.h"

using dml::NodeDef;

class GraphManager {
 public:
  GraphManager();
  GraphManager(const std::string filename);
  void eraseGraph();
  void addNode(Node *n);
  std::map<std::string, Node*> graph();
  std::vector<NodeDef> graphDef();
  void connectNodes();
  Node* getNode(std::string name);
  int size();
  int iterations();
  double stepSize();

 private:
  std::map<std::string, Node*> graph_;
  int iterations_;
  double step_size_;
};

#endif // RUNTIME_DEVICE_MANAGER_H