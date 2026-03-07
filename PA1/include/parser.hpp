#ifndef __PARSER_H__
#define __PARSER_H__

#include "circuit.hpp"
#include <gtest/gtest.h>
#include <string>
class Parser {
public:
  Circuit parse(const std::string &filepath);
};

#endif // __PARSER_H__