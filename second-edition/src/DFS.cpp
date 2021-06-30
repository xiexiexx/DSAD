#include "digraph.h"

void digraph::DFS(size_t s)
{
  // 访问顶点s并置该顶点为已访问.
  visit(s);
  marked[s] = true;
  // 对s所在链中的未访问顶点逐个进行递归搜索.
  for (auto citer = AL[s].cbegin(); citer != AL[s].cend(); ++citer)
    if (!marked[*citer])
      DFS(*citer);
}
