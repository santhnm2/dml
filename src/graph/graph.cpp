#include "graph.h"

#include <set>
#include <vector>

Node::Node(int id, int op_type) {
  id_ = id;
  op_type_ = op_type;
}

Node::~Node() {

}

Edge *Node::AddEdge(bool input, Edge* edge) {
  if (input) {
    in_edges_.push_back(edge);
  } else {
    out_edges_.push_back(edge);
  }

  return edge;
}

Edge::Edge(Node* src, Node* dst) {
  src_ = src;
  dst_ = dst;
}

Edge::~Edge() {

}

Node* Graph::AddNode(std::vector<Node*> inputs, int op_type) {
  Node* node = new Node(id_counter++, op_type);
  nodes_.push_back(node);

  for (int i = 0; i < inputs.size(); i++) {
    Edge* edge = new Edge(inputs[i], node);
    edges_.push_back(edge);
    node->AddEdge(true, edge);
  }

  return node;
}

Graph::~Graph() {
  for (int i = 0; i < nodes_.size(); i++) {
    delete nodes_[i];
  }

  for (int i = 0; i < edges_.size(); i++) {
    delete edges_[i];
  }
}

void Graph::RemoveNode(Node* node) {
  delete nodes_[node->id_];
  nodes_.erase(nodes_.begin()+node->id_);
}
