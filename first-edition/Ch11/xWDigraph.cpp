#include "xWDigraph.h"
#include <algorithm>

// 定义并初始化正无穷大权值
double xWDigraph::POSITIVE_INFINITY = std::numeric_limits<double>::max();

xWDigraph::xWDigraph(size_t V)
	: WL(V), marked(V), E(0)
{
	// 邻接表初始长度为V, 它也是顶点数.
	// 顶点标记向量初始长度为V.
	// 边数初始为0.
}

size_t xWDigraph::num_vertices() const
{
	return WL.size();
}

size_t xWDigraph::num_edges() const
{
	return E;
}

bool xWDigraph::edge(size_t u, size_t v) const
{
	// 定义一条出边oe, 邻接顶点为v, 边权任取(此处取0).
	xWOutEdge oe(v, 0);
	// 在AL[u]中查找v, 返回迭代器若为AL[u].end()则表明未找到.
	return ( std::find(WL[u].begin(), WL[u].end(), oe) != WL[u].end() );
}

void xWDigraph::add_edge(size_t u, size_t v, double weight)
{
	// 增添边是在对应的链WL[u]中增加顶点v和权weight. 
	WL[u].push_back(xWOutEdge(v, weight));
	E++;
}

void xWDigraph::remove_edge(size_t u, size_t v)
{
	// 删除边(u, v), 前提是该边在图中.
	// 定义一条出边oe, 邻接顶点为v, 边权任取(此处取0).
	xWOutEdge oe(v, 0);
	WL[u].remove(oe);	// 删除(u, v)
	E--;				// 边数减1
}

void xWDigraph::add_vertex()
{
	// 当前顶点编号为0, 1, ... , V - 1.
	// 增加一个新顶点, 编号设为V, 邻接表和其它信息相应更新.
	WL.push_back(std::list<xWOutEdge>());
	marked.push_back(false);
}
