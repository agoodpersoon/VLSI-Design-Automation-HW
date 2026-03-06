#ifndef PARSER
#define PARSER

#include "circuit.hpp"
#include <fstream>
#include <string>
class Parser {
public:
  CircuitGraph parse(const std::string &filepath);
};
#endif /* PARSER */
