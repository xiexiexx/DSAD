#include "digraph.h"
#include <algorithm>
#include <iostream>

digraph::digraph(size_t V)
  : AL(V), marked(V), E(0)
{
  // 邻接表初始长度为V, 它也是顶点数.
  // 顶点标记向量初始长度为V.
  // 边数初始为0.
}

size_t digraph::num_vertices() const
{
  return AL.size();
}

size_t digraph::num_edges() const
{
  return E;
}

bool digraph::edge(size_t u, size_t v) const
{
  // 在AL[u]中查找v, 返回迭代器若为AL[u].end()则表明未找到.
  return (std::find(AL[u].begin(), AL[u].end(), v) != AL[u].end());
}

void digraph::add_edge(size_t u, size_t v)
{
  // 增添边是在对应的链中增加顶点.
  AL[u].push_back(v); // 增添(u, v).
  ++E;                // 边数加1.
}

void digraph::remove_edge(size_t u, size_t v)
{
  // 删除边(u, v), 前提是该边在图中.
  AL[u].remove(v);    // 删除(u, v).
  --E;                // 边数减1.
}

void digraph::add_vertex()
{
  // 当前顶点编号为0, 1, ... , V - 1.
  // 增加一个新顶点, 编号设为V, 邻接表和其他信息相应更新.
  AL.push_back(std::list<size_t>());
  marked.push_back(false);
}

void digraph::visit(size_t v)
{
  // 此处访问v是直接在屏幕上输出. 
  // 读者可自行修改这个访问顶点函数的功能, 也可令其无任何动作.
  std::cout << v << " ";
}