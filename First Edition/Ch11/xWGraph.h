#include "xWDigraph.h"

#ifndef X_WEIGHTED_GRAPH
#define X_WEIGHTED_GRAPH

class xWGraph : public xWDigraph {
public:
	// 构造函数, V为预设顶点数
	xWGraph(size_t V = 0);
	// 增添边(u, v), 权值为weight(默认值为0).
	void add_edge(size_t u, size_t v, double weight = 0);
	// 删除边(u, v)
	void remove_edge(size_t u, size_t v);
	// Kruskal算法
	double Kruskal();
	// Prim算法
	double Prim();
};

# endif	// X_WEIGHTED_GRAPH

