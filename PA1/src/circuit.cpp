#include "circuit.hpp"
#include <cstddef>
#include <iostream>
#include <fstream>

void Circuit::add_node(const std::string& name, std::size_t id, NodeType type) {
  if (name_to_vertex_.find(name) != name_to_vertex_.end()) {
    throw std::runtime_error("Node with name '" + name + "' already exists.");
  }
  Vertex v = boost::add_vertex(Circuit::Node{id, name, type}, graph_);
  name_to_vertex_[name] = v;
}

void Circuit::add_edge(const std::string& from, const std::string& to) {
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

bool Circuit::has_vertex(const std::string& name) const {
  return name_to_vertex_.find(name) != name_to_vertex_.end();
}

Circuit::Vertex Circuit::find_vertex(const std::string& name) const {
  auto it = name_to_vertex_.find(name);
  if (it == name_to_vertex_.end()) {
    return Trait::null_vertex(); // Return an invalid vertex if not found
  }
  return it->second;
}

void Circuit::increment_gate_count(Circuit::NodeType type) {
  node_counts_[type]++;
}

std::size_t Circuit::get_node_count(NodeType type) const {
  auto it = node_counts_.find(type);
  return it != node_counts_.end() ? it->second : 0;
}

std::size_t Circuit::get_gate_count() const {
  std::size_t total_gates = 0;
  total_gates += get_node_count(NodeType::AND);
  total_gates += get_node_count(NodeType::OR);
  total_gates += get_node_count(NodeType::XOR);
  total_gates += get_node_count(NodeType::NAND);
  total_gates += get_node_count(NodeType::NOR);
  total_gates += get_node_count(NodeType::XNOR);
  total_gates += get_node_count(NodeType::NOT);
  return total_gates;
}

void Circuit::print_info() const {
  print_info_helper(std::cout);
}

void Circuit::print_info(const std::string& filename) const {
  std::ofstream ofs(filename, std::ios::out | std::ios::trunc);
  if (!ofs) {
    throw std::runtime_error("Failed to open output file: " + filename);
  }
  print_info_helper(ofs);
  ofs.close();
}

void Circuit::print_info_helper(std::ostream& ofs) const {
  ofs << "Circuit info:" << std::endl;
  ofs << "Number of inputs: " << get_node_count(NodeType::INPUT) << std::endl;
  ofs << "Number of outputs: " << get_node_count(NodeType::OUTPUT) << std::endl;
  ofs << "Number of inverts: " << get_node_count(NodeType::NOT) << std::endl;
  ofs << "Number of all gates: " << get_gate_count() << std::endl;
}