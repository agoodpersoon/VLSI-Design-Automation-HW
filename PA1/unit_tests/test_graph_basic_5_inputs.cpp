//
// Created by letianli on 3/8/26.
//

#include <gtest/gtest.h>

#include "parser.hpp"
TEST(graph_basic, 5_inputs) {
    Parser parser{};
    Circuit circuit = parser.parse("unit_tests/inputs/5inputs.in");
    EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::INPUT), 5);
    EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::OUTPUT), 3);
    EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::AND), 1);
    EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::DEFAULT), 1);
    EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::OR), 1);
    EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::XOR), 1);
    EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NAND), 0);
    EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NOR), 0);
}