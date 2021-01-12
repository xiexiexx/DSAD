#include "xDigraph.h"

#include <queue>
using std::queue;

void xDigraph::BFS(size_t v)
{
	// 所有顶点标记置为未发现
	for (size_t i = 0; i < marked.size(); i++)
		marked[i] = false;
	queue<size_t> Q;
	Q.push(v);
	marked[v] = true;
	while (!Q.empty())
	{
		size_t QF = Q.front();
		Q.pop();
		visit(QF);		// 访问队首元素QF
		// 随后将QF所在链中所有未发现的邻接顶点入队
		for (auto c_iter = AL[QF].cbegin(); c_iter != AL[QF].cend(); ++c_iter)
			if (!marked[*c_iter])
			{
				Q.push(*c_iter);
				marked[*c_iter] = true;	// 标记为已发现
				// 尽管该顶点还未被访问, 但它已进入队列, 将来一定会被访问.
			}
	}
}