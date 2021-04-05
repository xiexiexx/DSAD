#include <vector>
#include <list>

#ifndef DIGRAPH
#define DIGRAPH

class digraph {
public:
  // 构造函数, V为预设顶点数.
  digraph(size_t V = 0);
  // 顶点数.
  size_t num_vertices() const;
  // 边数.
  size_t num_edges() const;
  // 测试边(u, v)是否在图中.
  bool edge(size_t u, size_t v) const;
  // 增添边(u, v).
  void add_edge(size_t u, size_t v);
  // 删除边(u, v).
  void remove_edge(size_t u, size_t v);
  // 增添一个顶点, 编号为当前最大编号加1.
  void add_vertex();
  // 深度优先搜索.
  void DFS(size_t v);
  // 广度优先搜索.
  void BFS(size_t v);
  // 访问顶点函数.
  void visit(size_t v);
protected:
  std::vector<std::list<size_t>> AL;  // 邻接表.
  std::vector<bool> marked;           // 顶点标记向量.
  size_t E;                           // 边数.
  void DepthFirstSearch(size_t v);    // 私有递归DFS访问函数.
};

# endif // DIGRAPH
