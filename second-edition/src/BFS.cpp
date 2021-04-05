#include "digraph.h"

#include <queue>
using std::queue;

void digraph::BFS(size_t v)
{
  // 所有顶点标记置为未发现.
  for (size_t i = 0; i < marked.size(); ++i)
    marked[i] = false;
  queue<size_t> Q;
  Q.push(v);
  marked[v] = true;
  while (!Q.empty())
  {
    // 访问队首元素f并将其出队.
    size_t f = Q.front();
    visit(f);
    Q.pop();
    // 随后将f所在链中所有未发现的邻接顶点入队.
    for (auto citer = AL[f].cbegin(); citer != AL[f].cend(); 
      ++citer)
      if (!marked[*citer])
      {
        Q.push(*citer);
        marked[*citer] = true; // 标记为已发现.
        // 尽管该顶点还未被访问, 但它已进入队列, 将来一定会被访问.
      }
  }
}