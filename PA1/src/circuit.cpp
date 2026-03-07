#include "circuit.hpp"
#include <cstddef>
void Circuit::add_node(const std::string &name, std::size_t id, NodeType type) {
  if (name_to_vertex_.find(name) != name_to_vertex_.end()) {
    throw std::runtime_error("Node with name '" + name + "' already exists.");
  }
  Vertex v = boost::add_vertex(Circuit::Node{id, name, type}, graph_);
  name_to_vertex_[name] = v;
}

void Circuit::add_edge(const std::string &from, const std::string &to) {
  auto from_it = name_to_vertex_.find(from);
  auto to_it = name_to_vertex_.find(to);
  if (from_it == name_to_vertex_.end()) {
    throw std::runtime_error("Node with name '" + from + "' does not exist.");
  }
  if (to_it == name_to_vertex_.end()) {
    throw std::runtime_error("Node with name '" + to + "' does not exist.");
  }
  boost::add_edge(from_it->second, to_it->second, graph_);
}

Circuit::Vertex Circuit::find_vertex(const std::string &name) const {
  auto it = name_to_vertex_.find(name);
  if (it == name_to_vertex_.end()) {
    return Vertex(); // Return an invalid vertex if not found
  }
  return it->second;
}

void Circuit::increment_gate_count(Circuit::NodeType type) {
  gate_counts_[type]++;
}
std::size_t Circuit::get_gate_count(NodeType type) const {
  auto it = gate_counts_.find(type);
  return it != gate_counts_.end() ? it->second : 0;
}