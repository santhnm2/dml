#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "json.hpp"
#include "rpc/protos/node_def.pb.h"
#include "graph_mgr.h"

using dml::NodeDef;
using json = nlohmann::json;

GraphManager::GraphManager() {

}

GraphManager::GraphManager(const std::string filename) {
  std::ifstream f(filename.c_str(), std::ifstream::in);
  json graph_spec;
  f >> graph_spec;

  for (auto it = graph_spec["graph"].begin(); it != graph_spec["graph"].end();
       it++) {
    NodeDef def;
    def.set_name(it.key());
    def.set_op(it.value()["op"]);
    for (auto input : it.value()["inputs"]) {
      def.add_input(input);
    }
    for (auto output : it.value()["outputs"]) {
      def.add_output(output);
    }

    def.set_args(it.value()["args"].dump());
    Node *n = new Node(def);
    addNode(n);
  }
  
  iterations_ = graph_spec["iterations"];
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

int GraphManager::iterations() {
  return iterations_;
}