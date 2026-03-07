#ifndef CIRCUIT
#define CIRCUIT

#include "boost/graph/adjacency_list.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>

class Circuit {
public:
  enum class NodeType { DEFAULT, INPUT, OUTPUT, AND, OR, NOT, XOR, NAND, NOR };
  struct Node {
    std::size_t id;
    std::string name;
    NodeType type;
    bool operator==(const Node &other) const = default;
  };

  using Graph =
      boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, Node>;
  using Vertex = boost::graph_traits<Graph>::vertex_descriptor;

public:
  void add_node(const std::string &name, const std::size_t id, NodeType type);
  void add_edge(const std::string &from, const std::string &to);
  Vertex find_vertex(const std::string &name) const;
  void increment_gate_count(NodeType type);
  std::size_t get_gate_count(NodeType type) const;

private:
  Graph graph_;
  std::unordered_map<std::string, Vertex> name_to_vertex_;
  std::unordered_map<NodeType, std::size_t> gate_counts_;
};

#endif /* CIRCUIT */
