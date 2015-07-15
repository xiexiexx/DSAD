#include "xWGraph.h"
#include "xUF.h"

#include <queue>
using std::priority_queue;

using std::vector;

double xWGraph::Kruskal()
{
	size_t V = xWDigraph::num_vertices();
	// 将所有边存于向量EdgeVector中, 由于使用了默认构造函数, 效率不高.
	// 可以改写为自行申请空闲存储区的空间, 使用指针来实现. 
	vector<xWEdge> EdgeVector(2 * E);
	// 生成树的总花费
	double cost =  0;
	// 存储边指针的最小优先级队列PQ
	priority_queue<xWEdge*, vector<xWEdge*>, greater_xWEdgePointer> PQ;
	// 判断顶点是否在不同树中的不相交集
	xUF F(V);
	// 从邻接表中将所有边放入EdgeVector
	for (size_t pos = 0, u = 0; u < V; u++)
		for (auto c_iter = WL[u].begin(); c_iter != WL[u].end(); ++c_iter)
		{
			EdgeVector[pos] = xWEdge(u, c_iter->v, c_iter->weight);
			pos++;
		}
	// 将所有边的指针放入PQ
	for (size_t pos = 0; pos < EdgeVector.size(); pos++)
		PQ.push(&EdgeVector[pos]);
	size_t e_count = 0;		// 边计数器
	// 寻找V - 1条边组成最小生成树
	while (e_count < V - 1)
	{
		xWEdge* ePointer = PQ.top();	// 取权最小的边的指针ePointer
		// 若ePointer->u和ePointer->v不在一棵树中则对其所在的树进行合并
		if (F.Find(ePointer->u) != F.Find(ePointer->v))
		{
			F.Union(ePointer->u, ePointer->v);
			cost += ePointer->weight;	// 计入总花费
			e_count++;					// 找到一条边
		}
		PQ.pop();						// 删除最小元
    }
	return cost;
}