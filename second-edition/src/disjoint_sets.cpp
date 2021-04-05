#include "disjoint_sets.h"
#include <iostream>

disjoint_sets::disjoint_sets(size_t n)
  : disjoint_count(n)
{
  // 构造函数进行初始化.
  D.reserve(n);
  for (size_t i = 0; i < n; ++i)
    D.push_back({i, 0});
}

void disjoint_sets::merge(size_t x, size_t y)
{
  // x和y都为集合的代表元, 不相等才能合并.
  if (x == y)
    return;
  --disjoint_count;
  // 挑选秩较大的树根结点作为新的代表元.
  if (D[x].rank < D[y].rank)
    D[x].parent = y;
  else if (D[y].rank < D[x].rank)
    D[y].parent = x;
  else
  {
    // 秩相等则任选一个根结点, 此处选x.
    D[y].parent = x;
    // 注意增加秩.
    ++D[x].rank;
  }
}

size_t disjoint_sets::find(size_t x)
{
  // 使用两次迭代完成.
  size_t root = x;
  // 先查找代表元.
  while (D[root].parent != root)
    root = D[root].parent;
  // 再进行路径压缩.
  while (x != root)
  {
    size_t parent = D[x].parent;
    D[x].parent = root;
    x = parent;
  }
  return root;
}

size_t disjoint_sets::size() const
{
  return D.size();
}

size_t disjoint_sets::count() const
{
  return disjoint_count;
}

void disjoint_sets::print() const
{
  std::cout << "element: ";
  for (size_t i = 0; i < D.size(); ++i)
    std::cout << i << ", ";
  std::cout << std::endl << " parent: ";
  for (auto const& e : D)
    std::cout << e.parent << ", ";
  std::cout << std::endl << "   rank: ";
  for (auto const& e : D)
    std::cout << e.rank << ", ";
  std::cout << std::endl << std::endl;
}

void disjoint_sets::clear()
{
  for (size_t i = 0; i < D.size(); ++i)
    D[i] = {i, 0};
}
