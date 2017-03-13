#include "node.h"
#include "../ops/operation.h"
#include "../ops/ops_store.h"
#include "../util/util.h"

#include <iostream>
#include <string>
#include <vector>

#include <Eigen/Dense>

using Eigen::MatrixXd;
using dml::NodeDef;

Node::Node(NodeDef def) {
  // TODO(santhnm2): assign Op to Node based on op string
  // TODO(santhnm2): parse input string
  // TODO(santhnm2): parse output string

  def.name() == "-" ? name_ = "" : name_ = def.name();

  def.op() == "-" ? op_str_ = "" : op_str_ = def.op();

  def.inputs() == "-" ? inputs_ = "" : inputs_ = def.inputs();

  def.outputs() == "-" ? outputs_ = "" : outputs_ = def.outputs();

  op_ = OpsStore::requestOp(op_str_);

  std::vector<std::string> input_list = parse(inputs_, ":");
  fwd_deps_ = input_list.size();
}

std::string Node::name() const {
  return name_;
}

Operation Node::op() const {
  return op_;
}

std::string Node::inputs() const {
  return inputs_;
}

std::string Node::outputs() const {
  return outputs_;
}

Device Node::device() const {
  return device_;
}

MatrixXd Node::input() {
  return input_;
}

MatrixXd Node::weight() {
  return weight_;
}

MatrixXd Node::output() {
  return output_;
}

void Node::compute() {
  op_.compute(input_, weight_, output_);
}

void Node::setDevice(Device d) {
  device_ = d;
}

NodeDef Node::def() {
  NodeDef def;
  def.set_name(name_);
  def.set_op(op_str_);
  def.set_inputs(inputs_);
  def.set_outputs(outputs_);
  return def;
}

NodeDef* Node::allocated_def() {
  NodeDef *def = new NodeDef();
  def->set_name(name_);
  def->set_op(op_str_);
  def->set_inputs(inputs_);
  def->set_outputs(outputs_);
  return def;
}

int Node::forwardDependencies() {
  return fwd_deps_;
}

void Node::decrementForwardDependencies() {
  fwd_deps_--;
}