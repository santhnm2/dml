#ifndef RUNTIME_GRAPH_MANAGER_H
#define RUNTIME_GRAPH_MANAGER_H

#include <string>
#include <vector>

#include "../graph/node.h"

class GraphManager {
 public:
  void parseGraphSpec(const std::string filename);
  std::vector<Node> graph();

 private:
  std::vector<Node> graph_;
};

#endif // RUNTIME_DEVICE_MANAGER_H