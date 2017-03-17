#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "rpc/protos/node_def.pb.h"
#include "graph_mgr.h"

using dml::NodeDef;

GraphManager::GraphManager() {

}


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
      Node* n = new Node(def);
      addNode(n);
      getline(graph_spec, newline);
    }
    graph_spec.close();
  }
}

void GraphManager::eraseGraph() {
  for (auto it = graph_.begin(); it != graph_.end(); it++) {
    Node *n = it->second;
    delete n;
  }
}

int GraphManager::size() {
  return graph_.size();
}

void GraphManager::addNode(Node* n) {
  graph_.insert({n->name(), n});
} 

void GraphManager::connectNodes() {
  for (auto it = graph_.begin(); it != graph_.end(); it++) {
    Node *n = it->second;
    for (auto input : n->input_names()) {
      n->addInEdge(getNode(input));
    }
    for (auto output : n->output_names()) {
      n->addOutEdge(getNode(output));
    }
  }
}

Node* GraphManager::getNode(std::string name) {
  return graph_[name];
}

std::map<std::string, Node*> GraphManager::graph() {
  return graph_;
}

std::vector<NodeDef> GraphManager::graphDef() {
  std::vector<NodeDef> graphDef;

  for (auto it = graph_.begin(); it != graph_.end(); it++) {
    graphDef.push_back(it->second->def());
  }

  return graphDef;
}