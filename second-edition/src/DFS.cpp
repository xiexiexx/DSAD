#include "digraph.h"

void digraph::depth_first_search(size_t v)
{
  // 访问顶点v并置该顶点为已访问.
  visit(v);
  marked[v] = true;
  // 对v所在链中的未访问顶点逐个进行递归搜索.
  for (auto citer = AL[v].cbegin(); citer != AL[v].cend(); ++citer)
    if (!marked[*citer])
      depth_first_search(*citer);
}

void digraph::DFS(size_t s)
{
  // 所有顶点标记为未访问.
  for (size_t i = 0; i < marked.size(); ++i)
    marked[i] = false;
  // 从起点s开始递归搜索.
  depth_first_search(s);
}
