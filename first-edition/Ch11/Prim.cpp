#include "xWGraph.h"

#include <queue>
using std::priority_queue;

using std::vector;

double xWGraph::Prim()
{
	size_t V = xWDigraph::num_vertices();
	// 将所有边存于向量EdgeVector中.
	vector<xWEdge> EdgeVector(2 * E);
	// 生成树的总花费
	double cost =  0;
	// 存储边指针的最小优先级队列PQ
	priority_queue<xWEdge*, vector<xWEdge*>, greater_xWEdgePointer> PQ;
	// 初始将顶点0加入顶点集P, 其它顶点不在P中.
	for (size_t u = 1; u < V; u++)
		marked[u] = false;
	marked[0] = true;
	// 将所有以顶点0为端点的边的指针放入PQ.
	size_t pos = 0;		// 记录向量EdgeVector的空闲位置
	for (auto c_iter = WL[0].begin(); c_iter != WL[0].end(); ++c_iter)
	{
		EdgeVector[pos] = xWEdge(0, c_iter->v, c_iter->weight);
		PQ.push(&EdgeVector[pos]);
		pos++;
	}
	size_t e_count = 0;	// 边计数器
	// 寻找V - 1条边组成最小生成树
	while (e_count < V - 1)
	{
		xWEdge* ePointer = PQ.top();	// 取权最小的边e的指针ePointer
		PQ.pop();						// 删除最小元
		// 若ePointer->u和ePointer->v仅有一个在P中则将新顶点加入P, 
		// 注意我们的算法保证了不可能两个顶点都不在P中.
		if ( !(marked[ePointer->u] && marked[ePointer->v]) )
		{
			cost += ePointer->weight;	// 计入总花费
			e_count++;					// 找到一条边
			// 当前不在P中的顶点为x.
			size_t x;
			if (!marked[ePointer->u])
				x = ePointer->u;
			else
				x = ePointer->v;
			marked[x] = true;			// 将顶点x加入P
			// 将一个端点为顶点x且另一端点不在P中的边的指针加入优先级队列PQ中.
			for (auto c_iter = WL[x].begin(); c_iter != WL[x].end(); ++c_iter)
				if (!marked[c_iter->v])
				{
					EdgeVector[pos] = xWEdge(x, c_iter->v, c_iter->weight);
					PQ.push(&EdgeVector[pos]);
					pos++;
				}
		}
    }
	return cost;
}