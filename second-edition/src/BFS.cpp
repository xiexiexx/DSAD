#include "digraph.h"

#include <queue>

void digraph::BFS(size_t s)
{
  std::queue<size_t> Q;
  // 从起点s开始搜索.
  Q.push(s);
  marked[s] = true;
  while (!Q.empty())
  {
    // 访问队首元素f并将其出队.
    size_t f = Q.front();
    visit(f);
    Q.pop();
    // 将f所在链中所有未发现的邻接顶点入队.
    // 基于范围的for循环形式遍历邻接表更为简洁.
    for (const auto& v : AL[f])
      if (!marked[v])
      {
        // 将v入队并标记为已发现.
        Q.push(v);
        // 尽管此时未访问顶点v, 但它已进入队列, 将来一定会被访问.
        marked[v] = true;
      }
  }
}
