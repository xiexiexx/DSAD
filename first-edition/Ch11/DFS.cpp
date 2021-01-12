#include "xDigraph.h"

void xDigraph::DepthFirstSearch(size_t v)
{
	visit(v);			// 访问顶点v
	marked[v] = true;	// 置该顶点为已访问
	for (auto c_iter = AL[v].cbegin(); c_iter != AL[v].cend(); ++c_iter)
		if (!marked[*c_iter])
			DepthFirstSearch(*c_iter);
}

void xDigraph::DFS(size_t v)
{
	// 所有顶点标记为未访问
	for (size_t i = 0; i < marked.size(); i++)
		marked[i] = false;
	DepthFirstSearch(v);
}
