#include "xWGraph.h"

xWGraph::xWGraph(size_t V)
	: xWDigraph(V)
{
	// 只需使用xWDigraph类的构造函数即可.
}

void xWGraph::add_edge(size_t u, size_t v, double weight)
{
	// 增添{u, v}相当于增加边(u, v)和(v, u). 
	xWDigraph::add_edge(u, v, weight);
	xWDigraph::add_edge(v, u, weight);
	// 注意这只能算增加一条边, E必须减1.
	E--;
}

void xWGraph::remove_edge(size_t u, size_t v)
{
	// 删除边{u, v}, 前提是该边在图中.
	// 删除{u, v}相当于删除边(u, v)和(v, u).
	xWDigraph::remove_edge(u, v);
	xWDigraph::remove_edge(v, u);
	// 注意这只能算删除一条边, E必须加1.
	E++;
}
