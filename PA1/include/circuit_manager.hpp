#ifndef CIRCUIT_MANAGER_HPP
#define CIRCUIT_MANAGER_HPP

#include "circuit.hpp"
#include "parser.hpp"
#include <memory>
#include <string>

class CircuitManager {
public:
  CircuitManager() = default;
  explicit CircuitManager(const std::string &filepath) { load_circuit(filepath); }

  // Load circuit from file using Parser. Returns true on success.
  bool load_circuit(const std::string &filepath) noexcept;

  // Check if a circuit is currently loaded
  bool is_loaded() const noexcept { return circuit_ != nullptr; }

  // Accessors
  const Circuit &get_circuit() const;

  // Reset manager and drop the current circuit
  void reset() noexcept { circuit_.reset(); }

private:
  Parser parser_;
  std::unique_ptr<Circuit> circuit_;
};

#endif // CIRCUIT_MANAGER_HPP


