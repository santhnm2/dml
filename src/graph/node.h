#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <string>

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
  std::string inputs() const;
  std::string outputs() const;
  Device device() const;
  void setDevice(Device d);
  NodeDef def();
  NodeDef* allocated_def();
  void compute();
  int forwardDependencies();
  void decrementForwardDependencies();
  MatrixXd input();
  MatrixXd weight();
  MatrixXd output();
 private:
  int fwd_deps_;
  std::string name_;
  std::string op_str_;
  std::string inputs_;
  std::string outputs_;
  Device device_;
  MatrixXd input_;
  MatrixXd weight_;
  MatrixXd output_;
  Operation op_;
};

#endif // GRAPH_NODE_H