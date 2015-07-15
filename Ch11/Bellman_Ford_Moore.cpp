#include "xWDigraph.h"

#include <queue>
using std::queue;

#include <utility>
using std::pair;
using std::make_pair;

using std::vector;

bool xWDigraph::BFM(size_t s, vector<size_t>& path, vector<double>& length)
{
	// 设顶点数为V, 我们需要保证path和length都是长为V的向量.
	size_t V = num_vertices();
	// 初始化path向量, 其中所有元素初值为s.
	path = vector<size_t>(V, s);
	// 初始化length向量.
	// 暂时设所有length向量中的元素为正无穷大. 
	length = vector<double>(V, POSITIVE_INFINITY);
	// s位置路径长度初值为0.
	length[s] = 0;
	// 队列存放顶点与该顶点所在的迭代层次.
	queue<pair<size_t, size_t>> Q;
	// 初始存入顶点s, 其迭代层次为0. 
	Q.push( make_pair(s, 0) );
	// 为避免重复入队, 以marked向量标记顶点是否在队列中, 初始只有s在Q中. 
	for (size_t i = 0; i < V; i++)
		marked[i] = false;
	marked[s] = true;
	// 逐步迭代求最短路径长度, 至多V - 1次.
	while (!Q.empty())
	{
		// 迭代层次超过V, 必然存在负环.
		if (Q.front().second > V)
			return false;
		// 队首元素对应顶点为u, 迭代层次为level. 
		size_t u = Q.front().first;
		size_t level = Q.front().second;
		Q.pop();
		marked[u] = false;	// 顶点u已经不在队列中
		for (auto c_iter = WL[u].cbegin(); c_iter != WL[u].cend(); ++c_iter)
			if (length[u] + c_iter->weight < length[c_iter->v])
			{
				// 为方便表述, 将当前所处理顶点为c_iter->v简记为v. 
				size_t v = c_iter->v;
				// 若lenght[u] + w(u, v) < length[v]则更新path[v]和length[v].
				path[v] = u;
				length[v] = length[u] + c_iter->weight;
				// 由于length[v]减少, 若v不在队列中则入队, 注意迭代层次加1.
				if (!marked[v])
				{
					Q.push( make_pair(v, level + 1) );
					marked[v] = true;	// 顶点v已在队列中.
				}
			}
	}
	return true;
}