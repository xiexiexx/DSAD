#include <vector>
#include <list>

#ifndef DIGRAPH_CLASS
#define DIGRAPH_CLASS

class digraph {
public:
  // 构造函数, V为预设顶点数.
  digraph(size_t V = 0);
  // 顶点数.
  size_t vertices_count() const;
  // 边数.
  size_t edges_count() const;
  // 测试边(u, v)是否在图中.
  bool is_edge(size_t u, size_t v) const;
  // 增添边(u, v).
  void add_edge(size_t u, size_t v);
  // 删除边(u, v).
  void remove_edge(size_t u, size_t v);
  // 增添n个顶点, 默认值为1.
  void add_vertices(size_t n = 1);
  // 从起点s开始进行深度优先搜索.
  void DFS(size_t s);
  // 从起点s开始进行广度优先搜索.
  void BFS(size_t s);
  // 访问顶点函数.
  void visit(size_t v);
  // 重置所有顶点的标记.
  void reset_marks();
  // 顶点v是否被标记.
  bool is_marked(size_t v);
protected:
  std::vector<std::list<size_t>> AL;  // 邻接表.
  std::vector<bool> marked;           // 顶点标记向量.
  size_t E;                           // 边数.
};

#endif  // DIGRAPH_CLASS
