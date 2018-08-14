#include "xWDigraph.h"

#include <set>
using std::set;

#include <utility>
using std::pair;

using std::vector;

void xWDigraph::Dijkstra(size_t s, 
	vector<size_t>& path, vector<double>& length)
{
	// 设顶点数为V, 我们需要保证path和length都是长为V的向量.
	size_t V = num_vertices();
	// 初始化path向量, 其中所有元素初值均为s. 
	path = vector<size_t>(V, s);
	// 初始化length向量. 
	// 暂时设所有length向量中的元素为正无穷大. 
	length = vector<double>(V, POSITIVE_INFINITY);
	// s位置路径长度初值为0, 这样还可让s最先被找到.
	length[s] = 0;
	// 尚未寻找到的顶点集合为NS.
	set<pair<double, size_t>> NS;
	// 顶点在集合NS中的位置存于vertex_iter中.
	vector<set<pair<double, size_t>>::iterator> vertex_iter(V);
	for (size_t u = 0; u < V; u++)
		vertex_iter[u] = NS.insert({length[u], u}).first;
	for (size_t i = 0; i < V; i++)
	{
		// 每次在未找到的顶点集合中, 寻找以s为起点的路径长度最短的顶点. 
		// 设本次所找到的顶点为u, 对应路径长度为min.
		double min = NS.begin()->first;
		size_t u = NS.begin()->second;
		// u已找到, 将其从NS中删除.
		NS.erase(NS.begin());
		// 以u的邻接表为依据更新相关数据.
		for (auto c_iter = WL[u].cbegin(); c_iter != WL[u].cend(); 
			++c_iter)
			if (length[u] + c_iter->weight < length[c_iter->v])
			{
				// 为方便表述, 将当前所处理顶点为c_iter->v简记为v. 
				size_t v = c_iter->v;
				// 若lenght[u] + w(u, v) < length[v], 
				// 则更新path[v]和length[v].
				path[v] = u;
				length[v] = length[u] + c_iter->weight;
				// 通过删除和重新插入改变NS中的相应取值并保存位置.
				NS.erase(vertex_iter[v]);
				vertex_iter[v] = 
					NS.insert({length[v], v}).first;
			}
	}
}