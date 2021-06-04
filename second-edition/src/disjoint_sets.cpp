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
  // 编号超出范围则不处理.
  if (x >= D.size() || y >= D.size())
    return;
  // x和y必须都为集合的代表元/树根结点, 并且互不相等才能合并.
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

size_t disjoint_sets::find(size_t z)
{
  // 超出范围的编号则返回D.size()以示不存在.
  if (z >= D.size())
    return D.size();
  // 使用两次迭代完成.
  size_t root = z;
  // 先查找代表元.
  while (D[root].parent != root)
    root = D[root].parent;
  // 再进行路径压缩.
  while (D[z].parent != root)
  {
    // 使用parent暂存父亲结点.
    size_t parent = D[z].parent;
    D[z].parent = root;
    z = parent;
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

void disjoint_sets::reset()
{
  for (size_t i = 0; i < D.size(); ++i)
    D[i] = {i, 0};
}
