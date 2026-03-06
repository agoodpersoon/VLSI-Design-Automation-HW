#ifndef CIRCUIT
#define CIRCUIT

#include "boost/graph/adjacency_list.hpp"
#include <cstdint>
enum class GateType { INPUT, OUTPUT, AND, OR, NOT, XOR, NAND, NOR };
struct Node {
  uint64_t id;
  GateType type;
};

using CircuitGraph =
    boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, Node>;

#endif /* CIRCUIT */
