#include "digraph.h"

void digraph::depth_first_search(size_t v)
{
  visit(v);         // 访问顶点v.
  marked[v] = true; // 置该顶点为已访问.
  for (auto citer = AL[v].cbegin(); citer != AL[v].cend(); ++citer)
    if (!marked[*citer])
      depth_first_search(*citer);
}

void digraph::DFS(size_t v)
{
  // 所有顶点标记为未访问.
  for (size_t i = 0; i < marked.size(); ++i)
    marked[i] = false;
  depth_first_search(v);
}
