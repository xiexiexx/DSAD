#include <vector>

#ifndef DISJOINT_SETS
#define DISJOINT_SETS

// 存储父亲结点以及秩的信息.
struct information {
  size_t parent;
  size_t rank;
};

class disjoint_sets {
public:
  disjoint_sets(size_t n);        // 构造函数.
  void merge(size_t x, size_t y); // 合并.
  size_t find(size_t x);          // 寻找代表元.
  size_t size() const;            // 元素总数.
  size_t count() const;           // 不相交集的个数.
  void print() const;             // 打印当前结构信息.
  void clear();                   // 重置结构信息.
private:
  std::vector<information> D;     // 所有元素的信息.
  size_t disjoint_count;          // 维护不相交集个数的计数器.
};

# endif // DISJOINT_SETS
