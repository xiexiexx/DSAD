#include "digraph.h"
#include <algorithm>
#include <iostream>

digraph::digraph(size_t V)
  : AL(V), marked(V), E(0)
{
  // 邻接表和顶点标记向量的初始长度均设为顶点数V, 边数初值为0.
}

size_t digraph::vertices_count() const
{
  return AL.size();
}

size_t digraph::edges_count() const
{
  return E;
}

bool digraph::is_edge(size_t u, size_t v) const
{
  // 在AL[u]中查找v, 返回迭代器若为AL[u].end()则表明未找到.
  return (std::find(AL[u].begin(), AL[u].end(), v) != AL[u].end());
}

void digraph::add_edge(size_t u, size_t v)
{
  // 增添边(u, v)是在链AL[u]中加入顶点v并修改边数, 前提是该边不在图中.
  AL[u].push_back(v);
  ++E;
}

void digraph::remove_edge(size_t u, size_t v)
{
  // 删除边(u, v)并修改边数, 前提是该边在图中.
  AL[u].remove(v);
  --E;
}

void digraph::add_vertices(size_t n)
{
  // 当前顶点编号为0, 1, ... , V - 1.
  // 增加n个新顶点, 编号从V开始, 邻接表和其他信息也会相应更新.
  AL.resize(AL.size() + n);
  marked.resize(marked.size() + n, false);
}

void digraph::visit(size_t v)
{
  // 此处访问v是直接打印.
  // 读者可自行修改顶点访问函数的功能, 也可令其无任何动作.
  std::cout << v << ' ';
}

void digraph::reset_marks()
{
  // 搜素图之前得调用此函数.
  for (size_t i = 0; i < marked.size(); ++i)
    marked[i] = false;
}

bool digraph::is_marked(size_t v)
{
  return marked[v];
}
