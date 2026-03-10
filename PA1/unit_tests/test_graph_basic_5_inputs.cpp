//
// Created by letianli on 3/8/26.
//

#include <gtest/gtest.h>

#include "parser.hpp"
TEST(graph_basic, five_inputs) {
    Parser parser{};
    try {
      Circuit circuit = parser.parse("test/test1/b01_C.in");
      EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::INPUT), 7);
      EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::OUTPUT), 7);
      EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NOT), 10);
      EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::AND), 1);
      EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::OR), 1);
      EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NAND), 28);
      EXPECT_EQ(circuit.get_gate_count(), 40);
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      FAIL();
    }
}