#include "node.h"

#include <string>

using dml::NodeDef;

Node::Node(NodeDef def) {
  def.name() == "-" ? name_ = "" : name_ = def.name();

  def.op() == "-" ? op_ = "" : op_ = def.op();

  def.inputs() == "-" ? inputs_ = "" : inputs_ = def.inputs();

  def.outputs() == "-" ? outputs_ = "" : outputs_ = def.outputs();
}

std::string Node::name() {
  return name_;
}

std::string Node::op() {
  return op_;
}

std::string Node::inputs() {
  return inputs_;
}

std::string Node::outputs() {
  return outputs_;
}

Device Node::device() {
  return device_;
}

void Node::setDevice(Device d) {
  device_ = d;
}

NodeDef Node::def() {
  NodeDef def;
  def.set_name(name_);
  def.set_op(op_);
  def.set_inputs(inputs_);
  def.set_outputs(outputs_);
  return def;
}

NodeDef* Node::allocated_def() {
  NodeDef *def = new NodeDef();
  def->set_name(name_);
  def->set_op(op_);
  def->set_inputs(inputs_);
  def->set_outputs(outputs_);
  return def;
}