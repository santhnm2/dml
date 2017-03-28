#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <string>
#include <vector>

#include <Eigen/Dense>

// #include "../ops/operation.h"
#include "../runtime/device.h"
#include "../runtime/rpc/protos/node_def.pb.h"

using dml::NodeDef;
using Eigen::MatrixXd;

class Node {
 public:
  Node(NodeDef def);
  std::string name() const;
  std::string op() const;
  std::vector<std::string> input_names() const;
  std::vector<std::string> output_names() const;
  std::vector<Node*> inputs();
  std::vector<Node*> outputs();
  Device device() const;
  void setDevice(Device d);
  NodeDef def();
  NodeDef* allocated_def();
  //void compute();
  int getForwardDependencies();
  void setForwardDependencies(int deps);
  int getBackwardDependencies();
  void setBackwardDependencies(int deps);
  MatrixXd getInput();
  void setInput(MatrixXd input);
  MatrixXd getWeight();
  void setWeight(MatrixXd weight);
  MatrixXd getOutput();
  void setOutput(MatrixXd output);
  void addInEdge(Node* n);
  void addOutEdge(Node* n);
  MatrixXd data1;
  MatrixXd data2;
  MatrixXd data3;
 private:
  int fwd_deps_;
  int bwd_deps_;
  std::string name_;
  std::string op_;
  std::string inputs_str_;
  std::string outputs_str_;
  std::vector<std::string> input_names_;
  std::vector<std::string> output_names_;
  std::vector<Node*> inputs_;
  std::vector<Node*> outputs_;
  Device device_;
  MatrixXd input_;
  MatrixXd weight_;
  MatrixXd output_;
  // Operation op_;
};

#endif // GRAPH_NODE_H