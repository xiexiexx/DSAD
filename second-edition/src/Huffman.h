#include <string>
#include <vector>

#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

// Huffman树结点定义.
struct hnode {
  double weight;      // 权值.
  size_t number;      // 编号.
  // 设原始符号共n个,我们以编号区分原始符号结点和编码过程中出现的新结点,
  // 原始符号结点编号为0到n - 1, 新结点统一编号(大于n).
  hnode* left;        // 左孩子.
  hnode* right;       // 右孩子.
};

// greater_hnode_pointer为hnode型指针定义的函数对象,
// 用于比较该型指针所指向对象之间的大于关系.
struct greater_hnode_pointer {
  bool operator()(const hnode* a, const hnode* b) const
  {
    return (a->weight > b->weight);
  }
};

class Huffman {
public:
  // 构造函数.
  Huffman(hnode* p = NULL);
  // 编码函数.
  void coding(const std::vector<double>& P,
              std::vector<std::string>& C);
private:
  // 根结点.
  hnode* root;
  // 递归编码函数.
  void tree_coding(hnode* p, const std::string& prefix);
  // 保存编码的向量HC.
  std::vector<std::string> HC;
};

# endif // HUFFMAN_TREE
