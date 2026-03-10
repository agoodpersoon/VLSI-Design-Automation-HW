#include "parser.hpp"
#include "circuit.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cctype>

Circuit Parser::parse(const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filepath);
  }
  Circuit circuit{};
  std::string line;
  std::size_t line_idx = 0;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') {
      line_idx++;
      continue; // Skip empty lines and comments
    }
    if (line.substr(0, 5) == "INPUT") {
      // Parse input node
      // Input format: INPUT(<name>)
      std::string name = line.substr(6, line.size() - 7);
      std::size_t id = circuit.get_node_count(Circuit::NodeType::INPUT);
      circuit.increment_gate_count(Circuit::NodeType::INPUT);
      if (!circuit.has_vertex(name)) {
        circuit.add_node(name, id, Circuit::NodeType::INPUT);
      }
    } else if (line.substr(0, 6) == "OUTPUT") {
      // Parse output node
      // Output format: OUTPUT(<name>)
      std::string name = line.substr(7, line.size() - 8);
      std::size_t id = circuit.get_node_count(Circuit::NodeType::OUTPUT);
      circuit.increment_gate_count(Circuit::NodeType::OUTPUT);
      if (!circuit.has_vertex(name)) {
        circuit.add_node(name, id, Circuit::NodeType::OUTPUT);
      }
    } else {
      // Parse gate node and edges
      // Gate format: <name> = <GATE_TYPE>(<input1>, <input2>, ...)
      std::size_t eq_pos = line.find('=');
      if (eq_pos == std::string::npos) {
        throw std::runtime_error("Invalid line format at line index: " +
                                 std::to_string(line_idx) + ", missing '='");
      }

      // a. extract output node
      std::string out_node_name = line.substr(0, eq_pos - 1);
      std::size_t out_node_id =
          circuit.get_node_count(Circuit::NodeType::DEFAULT);

      // if the output node does not exist, create it as a default node.
      // otherwise it has been created as an output node, which is not a regular node
      if (!circuit.has_vertex(out_node_name)) {
        circuit.increment_gate_count(Circuit::NodeType::DEFAULT);
        circuit.add_node(out_node_name, out_node_id,
                         Circuit::NodeType::DEFAULT);
      }
      // Extract gate type and input nodes
      std::string rest = line.substr(eq_pos + 2);
      std::size_t left_paren_pos = rest.find('(');
      std::size_t right_paren_pos = rest.find(')');
      if (left_paren_pos == std::string::npos ||
          right_paren_pos == std::string::npos) {
        throw std::runtime_error(
            "Invalid gate format at line index: " + std::to_string(line_idx) +
            ", missing parentheses");
      }

      // b. extract gate node
      std::string gate_type_str = rest.substr(0, left_paren_pos);
      std::transform(gate_type_str.begin(), gate_type_str.end(),
             gate_type_str.begin(),
             [](unsigned char c) { return std::toupper(c); });
      Circuit::NodeType gate_type;
      if (gate_type_str == "AND") {
        gate_type = Circuit::NodeType::AND;
      } else if (gate_type_str == "OR") {
        gate_type = Circuit::NodeType::OR;
      } else if (gate_type_str == "NOT") {
        gate_type = Circuit::NodeType::NOT;
      } else if (gate_type_str == "XOR") {
        gate_type = Circuit::NodeType::XOR;
      } else if (gate_type_str == "XNOR") {
        gate_type = Circuit::NodeType::XNOR;
      } else if (gate_type_str == "NAND") {
        gate_type = Circuit::NodeType::NAND;
      } else if (gate_type_str == "NOR") {
        gate_type = Circuit::NodeType::NOR;
      } else {
        throw std::runtime_error(
            "Unknown gate type at line index: " + std::to_string(line_idx) +
            ", gate type: " + gate_type_str);
      }
      std::size_t id = circuit.get_node_count(gate_type);
      std::string gate_name = gate_type_str + "_" + std::to_string(id);
      circuit.increment_gate_count(gate_type);
      circuit.add_node(gate_name, id, gate_type);

      // c. extract input nodes
      std::string inputs_nodes_str =
          rest.substr(left_paren_pos + 1, right_paren_pos - left_paren_pos - 1);
      std::vector<std::string> input_names;
      std::replace(inputs_nodes_str.begin(), inputs_nodes_str.end(), ',', ' ');
      std::stringstream ss(inputs_nodes_str);
      std::string input_name;
      while (ss >> input_name) {
        input_names.push_back(input_name);
      }

      // d. connect edges
      // Connect input nodes to the gate node.
      for (const std::string &input_name : input_names) {
        if (!circuit.has_vertex(input_name)) {
          std::size_t input_node_id =
              circuit.get_node_count(Circuit::NodeType::DEFAULT);
          circuit.increment_gate_count(Circuit::NodeType::DEFAULT);
          circuit.add_node(input_name, input_node_id,
                           Circuit::NodeType::DEFAULT);
        }
        circuit.add_edge(input_name,
                         gate_name); // Connect input node to gate node
      }

      // Connect gate node to the output node.
      circuit.add_edge(gate_name,
                       out_node_name); // Connect gate node to output node
    }
    line_idx++;
  }
  return circuit;
}