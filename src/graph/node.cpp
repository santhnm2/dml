#include "node.h"
#include "../util/util.h"

#include <iostream>
#include <string>
#include <vector>

#include <Eigen/Dense>

using Eigen::MatrixXd;
using dml::NodeDef;

Node::Node(NodeDef def) {
  name_ = def.name();

  op_ = def.op();

  for (auto input : def.input()) {
    input_names_.push_back(input);
  }

  for (auto output: def.output()) {
    output_names_.push_back(output);
  }

  fwd_deps_ = input_names_.size();
  bwd_deps_ = 0;
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

void Node::addOutEdge(Node* n) {
  outputs_.push_back(n);
}

void Node::setDevice(Device d) {
  device_ = d;
}

NodeDef Node::def() {
  NodeDef def;
  def.set_name(name_);
  def.set_op(op_);

  for (auto input : input_names_) {
    def.add_input(input);
  }

  for (auto output : output_names_) {
    def.add_output(output);
  }

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