#include "circuit_manager.hpp"
#include <stdexcept>

bool CircuitManager::load_circuit(const std::string &filepath) noexcept {
  try {
    Circuit circuit = parser_.parse(filepath);
    circuit_ = std::make_unique<Circuit>(std::move(circuit));
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error parsing circuit: " << e.what() << std::endl;
    circuit_.reset();
    return false;
  }
}

const Circuit &CircuitManager::get_circuit() const {
  if (!circuit_) {
    throw std::runtime_error("No circuit loaded");
  }
  return *circuit_;
}


