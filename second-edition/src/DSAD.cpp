#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <numeric>
#include <random>
#include <algorithm>
#include "timer.h"
#include "sorted_vector_with_large_capacity.h"
#include "unsorted_vector_with_large_capacity.h"
#include "LEGO.h"
#include "buffer.h"
#include "disjoint_sets.h"
#include "Huffman.h"
#include "digraph.h"
#include "dynamic_array.h"
#include "doubly_linked_list.h"
#include <chrono>

// 函数声明.

void identity_matrix(size_t n);

uint64_t Fibonacci(unsigned int n);

void Fibonacci_sequence(unsigned int m);

void ChiaHsien_triangle(unsigned int n, int width);

void input_preprocess(std::list<int>& L, int& m);

void print(const std::list<int>& L);

void mean_of_larger(std::list<int>& L, int d, int m);

void treasure_hunting(const std::vector<std::vector<std::string>>& H,
                      const std::vector<std::string>& F);

// 打印容器S中的所有元素.
template <typename C>
void print_all(const C& S)
{
  for (const auto& x : S)
    std::cout << x << ' ';
  std::cout << std::endl;
}

// 以迭代器区间[left, right)作为参数打印所有元素.
template <typename IR>
void print_all(IR left, IR right)
{
  while (left != right)
    std::cout << *++left << ' ';
  std::cout << std::endl;
}

// 演示程序直接在main函数里调用即可.

// 单位矩阵演示.
void demo_identity_matrix()
{
  // 设置5 x 5单位矩阵并打印.
  identity_matrix(5);
}

// Fibonacci序列计算(非常慢).
void demo_Fibonacci()
{
  timer t;
  t.start();
  Fibonacci_sequence(50);
  t.stop();
  std::cout << t.time() << std::endl;
}

// LEGO问题求解.
void demo_LEGO()
{
  // 底板尺寸8 x 8, (5, 2)位置已覆盖.
  LEGO L(8);
  L.solve({5, 2});
  // 80字符终端打印可设width为5.
  L.print(5);
}

// 缓冲区演示.
void demo_buffer()
{
  size_t n = 10;
  buffer<int> B(n);
  int i = 0;
  while (!B.full())
  {
    B.push(i++);
    std::cout << B.front() << ' ';
  }
  std::cout << std::endl;
  while (!B.empty())
  {
    std::cout << B.front() << ' ';
    B.pop();
  }
  std::cout << std::endl;
}

// 贾宪三角演示.
void demo_ChiaHsien_triangle()
{
  // 由于终端显示限制n最大取13.
  // 二项式系数的宽度width, 随n的值增大而增大, 此处取3足矣.
  ChiaHsien_triangle(13, 3);
}

// 统计量.
void demo_special_statistic()
{
  std::list<int> L;
  int d = 2;
  int m;
  input_preprocess(L, m);
  mean_of_larger(L, d, m);
}

// 寻找宝藏问题演示.
void demo_multi_treasure_hunting()
{
  std::vector<std::vector<std::string>> H {
    {"A", "B"}, {"C", "D"}, {"D", "S", "A", "D"}
  };
  std::vector<std::string> F {"A", "A", "C"};
  treasure_hunting(H, F);
}

// 不相交集演示.
void demo_disjoint_sets()
{
  // 共7个元素.
  disjoint_sets S(7);
  S.merge(S.find(1), S.find(5));
  S.print();
  S.merge(S.find(2), S.find(4));
  S.print();
  S.merge(S.find(1), S.find(4));
  S.print();
  S.merge(S.find(6), S.find(5));
  S.print();
  S.merge(S.find(4), S.find(3));
  S.print();
}

// Huffman编码演示, 英文字母词频.
void demo_Huffman()
{
  std::vector<double> P {
    0.0721, 0.0240, 0.0394, 0.0372, 0.1224, 0.0272,
    0.0178, 0.0449, 0.0779, 0.0013, 0.0054, 0.0426,
    0.0282, 0.0638, 0.0681, 0.0290, 0.0023, 0.0638,
    0.0728, 0.0908, 0.0235, 0.0094, 0.0130, 0.0077,
    0.0126, 0.0026
  };
  Huffman H;
  H.coding(P);
  // 码字与对应符号(也即英文字母).
  for (size_t i = 0; i < H.size(); ++i)
    std::cout << H.codeword(i) << " <-> "
              << (char)('A' + H.symbol(H.codeword(i))) << std::endl;
  if (H.symbol("012") == H.size())
    std::cout << "Error!" << std::endl;
}

// 有向图演示.
void demo_digraph()
{
  // 实际上G是一棵树, 注意观察遍历次序.
  digraph G(7);
  G.add_edge(0, 1);
  G.add_edge(0, 2);
  G.add_edge(0, 3);
  G.add_edge(1, 4);
  G.add_edge(2, 5);
  G.add_edge(2, 6);
  G.DFS(0);
  std::cout << std::endl;
  G.BFS(0);
  std::cout << std::endl;
  G.add_vertices(2);
  G.add_edge(2, 7);
  G.add_edge(5, 8);
  G.DFS(0);
  std::cout << std::endl;
  G.BFS(0);
  std::cout << std::endl;
  if (G.is_edge(0, 3))
    G.remove_edge(0, 3);
  G.DFS(0);
  std::cout << std::endl;
  G.BFS(0);
  std::cout << std::endl;
}

// 前缀和问题演示(使用STL).
void demo_prefixsum()
{
  std::vector<double> A {3.1, 3.14, 3.141, 3.1415};
  std::vector<double> S(A.size());
  std::partial_sum(A.begin(), A.end(), S.begin());
  print_all(S);
}

// 洗牌算法展示(使用STL).
void demo_shuffle()
{
  std::vector<int> V {4, 2, 1, 3, 5};
  // 随机数来源于rd.
  std::random_device rd;
  // 基于knuth_b(以Knuth命名的shuffle_order_engine)的随机数生成器g.
  std::knuth_b g(rd());
  // n为洗牌次数.
  size_t n = 3;
  for (size_t i = 0; i < n; ++i)
  {
    std::shuffle(V.begin(), V.end(), g);
    print_all(V.begin(), V.end());
  }
}

// 动态数组演示.
void demo_dynamic_array()
{
  dynamic_array<int> A(4, 2);
  for (auto iter = A.begin(); iter != A.end(); ++iter)
    std::cout << *iter << ' ';
  std::cout << std::endl;
  // 注意单独留作哨兵位置.
  A[A.size()] = 3;
  std::cout << A[A.size()];
}

// 双链演示.
void demo_doubly_linked_list()
{
  doubly_linked_list<int> L;
  L.push_back(3);
  L.push_back(2);
  L.push_front(4);
  L.push_front(1);
  for (auto iter = L.begin(); iter != L.end(); ++iter)
    std::cout << *iter << ' ';
  std::cout << std::endl;
  L.reverse();
  for (auto riter = L.rbegin(); riter != L.rend(); ++riter)
    std::cout << *riter << ' ';
  std::cout << std::endl;
  auto iter = L.find(2);
  std::cout << *iter;
}

int main()
{
  return 0;
}
