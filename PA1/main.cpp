#include "boost/graph/adjacency_list.hpp"
#include <boost/graph/graph_selectors.hpp>
#include <iostream>

int main() {
  using Graph =
      boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS>;
  Graph g{};
  auto v1 = add_vertex(g);
  auto v2 = add_vertex(g);
  add_edge(v1, v2, g);
  std::cout << "Number of vertices: " << num_vertices(g) << std::endl;
  std::cout << "Number of edges: " << num_edges(g) << std::endl;
  return 0;
}