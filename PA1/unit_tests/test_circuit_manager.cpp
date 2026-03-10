//
// Created by letianli on 3/9/26.
//

#include <gtest/gtest.h>

#include "circuit_manager.hpp"

TEST(CircuitManager, load) {
  CircuitManager circuit_manager{};
  ASSERT_TRUE(circuit_manager.load_circuit("test/test1/b01_C.in"));

  const Circuit &circuit = circuit_manager.get_circuit();
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::INPUT), 7);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::OUTPUT), 7);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NOT), 10);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::AND), 1);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::OR), 1);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NAND), 28);
  EXPECT_EQ(circuit.get_gate_count(), 40);
}

TEST(CircuitManager, loads_c432) {
  CircuitManager circuit_manager{};
  ASSERT_TRUE(circuit_manager.load_circuit("test/test1/c432.in"));

  const Circuit &circuit = circuit_manager.get_circuit();
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::INPUT), 36);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::OUTPUT), 7);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NOT), 40);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::AND), 4);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::XOR), 18);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NAND), 79);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NOR), 19);
  EXPECT_EQ(circuit.get_gate_count(), 160);
}

TEST(CircuitManager, loads_c7552_nobuf) {
  CircuitManager circuit_manager{};
  ASSERT_TRUE(circuit_manager.load_circuit("test/test1/c7552_nobuf.in"));

  const Circuit &circuit = circuit_manager.get_circuit();
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::INPUT), 207);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::OUTPUT), 108);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NOT), 876);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::AND), 776);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::OR), 778);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::XOR), 0);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NAND), 1028);
  EXPECT_EQ(circuit.get_node_count(Circuit::NodeType::NOR), 54);
  EXPECT_EQ(circuit.get_gate_count(), 3512);
}