#include "circuit.hpp"
#include "parser.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <filesystem>
#include <gtest/gtest.h>

TEST(Parse, Basic) {
  // This test tests a simple input file with 2 inputs 1 output and 1 and gate.
  Parser parser{};
  std::cout << "current path: " << std::filesystem::current_path() << std::endl;
  Circuit circuit = parser.parse("unit_tests/inputs/1and.in");
  // Check the number of nodes and edges.
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::AND), 1);
}
