#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "rpc/node_def.pb.h"
#include "graph_mgr.h"

using dml::NodeDef;

GraphManager::GraphManager(const std::string filename) {
  std::ifstream graph_spec(filename.c_str(), std::ifstream::in);
  std::string name;
  std::string op;
  std::string inputs;
  std::string outputs;
  std::string newline;

  if (graph_spec.is_open()) {
    while (getline(graph_spec, name) && getline(graph_spec, op) &&
           getline(graph_spec, inputs) && getline(graph_spec, outputs)) {
      NodeDef def;
      def.set_name(name);
      def.set_op(op);
      def.set_inputs(inputs);
      def.set_outputs(outputs);
      Node node(def);
      graph_.push_back(node);
      getline(graph_spec, newline);
    }
    graph_spec.close();
  }
}

int GraphManager::size() {
  return graph_.size();
}

Node* GraphManager::getNodeAtIndex(int idx) {
  if (idx >= graph_.size() || idx < 0) {
    return NULL;
  } 
  return &graph_[idx];
}

std::vector<Node> GraphManager::graph() {
  return graph_;
}