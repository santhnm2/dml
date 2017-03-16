#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <string>
#include <vector>

#include <Eigen/Dense>

#include "../ops/operation.h"
#include "../runtime/device.h"
#include "../runtime/rpc/protos/node_def.pb.h"

using dml::NodeDef;
using Eigen::MatrixXd;

class Node {
 public:
  Node(NodeDef def);
  std::string name() const;
  Operation op() const;
  std::vector<std::string> inputs() const;
  std::vector<std::string> outputs() const;
  Device device() const;
  void setDevice(Device d);
  NodeDef def();
  NodeDef* allocated_def();
  void compute();
  int getForwardDependencies();
  void setForwardDependencies(int deps);
  int getBackwardDependencies();
  void setBackwardDependencies(int deps);
  MatrixXd getInput();
  MatrixXd getWeight();
  MatrixXd getOutput();
  void setInput(MatrixXd input);
  void setWeight(MatrixXd weight);
  void setOutput(MatrixXd output);
 private:
  int fwd_deps_;
  int bwd_deps_;
  std::string name_;
  std::string op_;
  std::string inputs_str_;
  std::string outputs_str_;
  std::vector<std::string> inputs_;
  std::vector<std::string> outputs_;
  Device device_;
  MatrixXd input_;
  MatrixXd weight_;
  MatrixXd output_;
  // Operation op_;
};

#endif // GRAPH_NODE_H