#include "node.h"
// #include "../ops/operation.h"
// #include "../ops/ops_store.h"
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

  // def.op() == "-" ? op_str_ = "" : op_str_ = def.op();

  def.op() == "-" ? op_ = "" : op_ = def.op();

  def.inputs() == "-" ? inputs_str_ = "" : inputs_str_ = def.inputs();

  def.outputs() == "-" ? outputs_str_ = "" : outputs_str_ = def.outputs();

  // op_ = OpsStore::requestOp(op_str_);

  input_names_ = parse(inputs_str_, ":");
  output_names_ = parse(outputs_str_, ":");
  
  fwd_deps_ = input_names_.size();
  bwd_deps_ = 0;

  // std::cout << "Node \"" << name_ << "\" initialized with " << fwd_deps_ << " forward dependencies." << std::endl;
}

std::string Node::name() const {
  return name_;
}

std::string Node::op() const {
  return op_;
}

std::vector<Node*> Node::inputs() {
  return inputs_;
}

std::vector<Node*> Node::outputs() {
  return outputs_;
}

std::vector<std::string> Node::input_names() const {
  return input_names_;
}

std::vector<std::string> Node::output_names() const {
  return output_names_;
}

Device Node::device() const {
  return device_;
}

MatrixXd Node::getInput() {
  return input_;
}

void Node::setInput(MatrixXd input) {
  input_ = input;
}

MatrixXd Node::getWeight() {
  return weight_;
}

void Node::setWeight(MatrixXd weight) {
  weight_ = weight;
} 

MatrixXd Node::getOutput() {
  return output_;
}

void Node::setOutput(MatrixXd output) {
  output_ = output;
}

void Node::addInEdge(Node* n) {
  inputs_.push_back(n);
}

void Node::addOutEdge(Node *n) {
  outputs_.push_back(n);
}

/*void Node::compute() {
  // op_.compute(input_, weight_, output_);
  std::cout << "Running operation " << op_ << std::endl;
  Operation::compute(op_, input_, weight_, output_);
}*/

void Node::setDevice(Device d) {
  device_ = d;
}

NodeDef Node::def() {
  NodeDef def;
  def.set_name(name_);
  def.set_op(op_);
  def.set_inputs(inputs_str_);
  def.set_outputs(outputs_str_);
  return def;
}

NodeDef* Node::allocated_def() {
  NodeDef *def = new NodeDef();
  def->set_name(name_);
  // def->set_op(op_str_);
  def->set_op(op_);
  def->set_inputs(inputs_str_);
  def->set_outputs(outputs_str_);
  return def;
}

int Node::getForwardDependencies() {
  return fwd_deps_;
}

void Node::setForwardDependencies(int deps) {
  fwd_deps_ = deps;
}

int Node::getBackwardDependencies() {
  return bwd_deps_;
}

void Node::setBackwardDependencies(int deps) {
  bwd_deps_ = deps;
}