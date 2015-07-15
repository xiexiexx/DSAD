#include "xWDigraph.h"

void xWDigraph::FW(matrix<size_t>& path, matrix<double>& length)
{
	// 设顶点数为V, 我们需要保证path和length都是V * V的矩阵.
	size_t V = num_vertices();
	// 初始化path矩阵数据. 
	// 更改path矩阵大小以满足要求. 
	path = matrix<size_t>(V, V);
	// 令所有path(u, v)的值为u.
	for (size_t u = 0; u < V; u++)
		for (size_t v = 0; v < V; v++)
			path(u, v) = u;
	// 初始化length矩阵数据.
	// 暂时设所有length矩阵中的元素为正无穷大. 
	length = matrix<double>(V, V, POSITIVE_INFINITY);
	for (size_t v = 0; v < V; v++)
		length(v, v) = 0;	// 对角线赋0, 自圈.
	// 导入邻接表中的边数据, 每次所找顶点为c_iter->v, 权为c_iter->weight. 
	for (size_t u = 0; u < V; u++)
		for(auto c_iter = WL[u].cbegin(); c_iter != WL[u].cend(); ++c_iter)
			length(u, c_iter->v) = c_iter->weight;
	// 依次计算k-最短路径, 每次计算更新path矩阵和length矩阵.
	for (size_t k = 0; k < V; k++)
		for (size_t u = 0; u < V; u++)
			for (size_t v = 0; v < V; v++)
				if (length(u, k) + length(k, v) < length(u, v))
				{
					// 这种情况下从u到v的路径后半段变为从k到v的路径, 
					// 故而这里需要更新path(u, v)为path(k, v).
					path(u, v) = path(k, v);
					length(u, v) = length(u, k) + length(k, v);
				}
}