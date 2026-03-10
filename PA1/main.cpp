#include <iostream>
#include <filesystem>

#include "circuit_manager.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <relative_path_to_your_input_file_from_root>" << std::endl;
    return 1;
  }
  std::string relative_path = argv[1];
  std::filesystem::path project_root = std::filesystem::current_path().parent_path().parent_path();
  std::filesystem::path input_path = project_root / relative_path;
  std::cout << "Input file path: " << input_path << std::endl;
  CircuitManager circuit_manager(input_path.string());
  circuit_manager.get_circuit().print_info();
  return 0;
}