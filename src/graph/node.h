#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <string>

#include "../runtime/rpc/node_def.pb.h"

using dml::NodeDef;

class Node {
 public:
  Node(NodeDef def);
  std::string name();
  std::string op();
  std::string inputs();
  std::string outputs();
 private:
  std::string name_;
  std::string op_;
  std::string inputs_;
  std::string outputs_;
  //int op_type_;
  // MatrixXd input_;
  // MatrixXd computation_data_;
  // MatrixXd output_;
  //Operation op_;

  //std::vector<Node> inputs_;
  //std::vector<Node> outputs_;

  //Device device_;
};

#endif // GRAPH_NODE_H