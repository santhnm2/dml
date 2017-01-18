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