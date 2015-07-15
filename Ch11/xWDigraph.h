#include <vector>
#include <list>
#include "vMatrix.h"

#ifndef X_WEIGHTED_DIGRAPH
#define X_WEIGHTED_DIGRAPH

// 加权出边类, 存放邻接顶点与边权
struct xWOutEdge {
	xWOutEdge(size_t init_v, double w = 0)
		: v(init_v), weight(w)
	{
		// 构造函数
	}
	bool operator==(const xWOutEdge& rhs) const
	{
		// 仅考虑邻接顶点的相等情况
		return (v == rhs.v);
	}
	// 从顶点u到v的边, 邻接顶点为v, 权为weight.
	size_t v;			// 邻接顶点
	double weight;		// 边权
};

// 加权有向边类
struct xWEdge {
	xWEdge(size_t init_u = 0, size_t init_v = 0, double w = 0)
		: u(init_u), v(init_v), weight(w)
	{
		// 构造函数
	}
	// 从顶点u到v的边, 权为weight.
	size_t u;
	size_t v;
	double weight;
};

// 为xWEdge型指针定义的函数对象, 用于比较该型指针所指向对象边权之间的大于关系
class greater_xWEdgePointer {
public:
	bool operator()(const xWEdge* a, const xWEdge* b) const
	{
		return (a->weight > b->weight);
	}
};

class xWDigraph {
public:
	// 构造函数, V为预设顶点数
	xWDigraph(size_t V = 0);
	// 顶点数
	size_t num_vertices() const;
	// 边数
	size_t num_edges() const;
	// 测试边(u, v)是否在图中
	bool edge(size_t u, size_t v) const;
	// 增添边(u, v), 权值为weight(默认值为0)
	void add_edge(size_t u, size_t v, double weight = 0);
	// 删除边(u, v)
	void remove_edge(size_t u, size_t v);
	// 增添一个顶点, 编号为当前最大编号加1
	void add_vertex();
	// 正无穷大权值
	static double POSITIVE_INFINITY;
	// Dijkstra算法
	void Dijkstra(size_t s, std::vector<size_t>& path, 
		std::vector<double>& length);
	// Bellman-Ford-Moore算法
	bool BFM(size_t s, std::vector<size_t>& path, 
		std::vector<double>& length);
	// Floyd-Warshall算法
	void FW(matrix<size_t>& path, matrix<double>& length);
protected:
	std::vector<std::list<xWOutEdge>> WL;	// 邻接表, 存储出边的邻接顶点与边权
	std::vector<bool> marked;				// 顶点标记向量
	size_t E;								// 边数
};

# endif	// X_WEIGHTED_DIGRAPH

