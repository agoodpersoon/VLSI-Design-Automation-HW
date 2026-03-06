#include <boost/graph/adjacency_list.hpp>
#include <gtest/gtest.h>

// 定义测试套件名为 GraphTest，测试用例名为 BasicStructure
TEST(GraphTest, BasicStructure) {
  // 1. 定义图类型（和你 main 里的完全一致）
  using Graph =
      boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS>;
  Graph g{};

  // 2. 执行操作
  auto v1 = add_vertex(g);
  auto v2 = add_vertex(g);
  add_edge(v1, v2, g);

  // 3. 验证逻辑（核心：不再用 cout，用断言）
  // 验证顶点数是否为 2
  EXPECT_EQ(boost::num_vertices(g), 2);

  // 验证边数是否为 1
  EXPECT_EQ(boost::num_edges(g), 1);
}

// 注意：如果 CMake 链接了 GTest::gtest_main，你这里不需要写 main 函数