#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <set>
#include <vector>

class Node;
class Edge;
class Graph;

class Node {
  public:
    const std::vector<Edge*>& in_edges() const { return in_edges_; }
    const std::vector<Edge*>& out_edges() const { return out_edges_; }
    Edge* AddEdge(bool input, Edge* edge);
  private:
    friend class Graph;
    Node(int id, int op_type);
    ~Node();
    int id_;
    int op_type_;

    std::vector<Edge*> in_edges_;
    std::vector<Edge*> out_edges_;
};

class Edge {
  public:
    Node* src() const { return src_; }
    Node* dst() const { return dst_; }
  private:
    friend class Graph;
    Edge(Node* src, Node* dst);
    ~Edge();
    Node* src_;
    Node* dst_;
};

class Graph {
  public:
    ~Graph();
    Node* AddNode(std::vector<Node*> inputs, int op_type);
    void RemoveNode(Node* node);
  private:
    int id_counter = 0;
    std::vector<Node*> nodes_;
    std::vector<Edge*> edges_;
};

#endif // GRAPH_GRAPH_H
