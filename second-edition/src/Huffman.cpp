#include "Huffman.h"

#include <queue>
using std::priority_queue;

using std::vector;
using std::string;

Huffman::Huffman()
  : root(NULL)
{
  // 初始为空树.
}

void Huffman::tree_coding(hnode* p, const string& prefix)
{
  // 若p不为NULL则递归对以p为根的子树所有结点进行编码.
  // 读者可思考利用层次遍历对结点编码.
  if (p == NULL)
    return;
  // 叶子结点编号对应待编码符号, 以此在编码向量相应位置赋码字prefix,
  // 否则继续递归编码.
  if (p->number < C.size())
    C[p->number] = prefix;
  else
  {
    // 结点p的左子树所有前缀是prefix配0.
    tree_coding(p->left, prefix + "0");
    // 结点p的右子树所有前缀是prefix配1.
    tree_coding(p->right, prefix + "1");
  }
}

void Huffman::coding(const vector<double>& P)
{
  if (P.size() == 0)
    return;
  // 编码向量C的长度设置为概率向量的长度.
  C.resize(P.size());
  // 存储Huffman树的最小优先级队列PQ, 优先级为树的权值,
  // 实际上存储的是树的根结点指针.
  priority_queue<hnode*, vector<hnode*>, greater_hnode_pointer> PQ;
  // 一次性给出所有在编码中会出现的结点.
  tree.resize(2 * P.size() - 1);
  // index作为编号, 指示当前会使用tree[index]处的结点.
  // 注意index的作用域不仅限于下面的for循环.
  size_t index;
  // 初始放入n个仅有根结点的树.
  for (index = 0; index < P.size(); ++index)
  {
    // 以下赋值部分还可以写得更简洁.
    // 对应需编码的符号, 编号为自然数.
    tree[index].number = index;
    // 结点权值按照概率向量赋值.
    tree[index].weight = P[index];
    tree[index].left = NULL;
    tree[index].right = NULL;
    // 放入优先级队列中.
    PQ.push(&tree[index]);
  }
  // 循环处理以构建Huffman树.
  while (PQ.size() > 1)
  {
    // 取新结点数据.
    hnode* p = &tree[index];
    // 新出现的结点编号统一为C.size().
    p->number = C.size();
    // 将优先级队列中的最小元作为p所指向结点的左孩子.
    p->weight = PQ.top()->weight;
    p->left = PQ.top();
    // 取出最小元.
    PQ.pop();
    // 将优先级队列中的最小元作为p所指向结点的右孩子.
    p->weight += PQ.top()->weight;
    p->right = PQ.top();
    // 取出最小元.
    PQ.pop();
    // 将新的树放入优先级队列.
    PQ.push(p);
    // 编号更新, 下次使用新结点.
    ++index;
  }
  // 若PQ不空则可根据其中所剩的唯一Huffman树进行编码.
  if (!PQ.empty())
  {
    tree_coding(PQ.top(), "");
    // 设定根结点指针.
    root = PQ.top();
  }
}

size_t Huffman::symbol(const string& code)
{
  // 如果出错则返回不存在的位置C.size().
  // 以指针p访问树, 对编码code[i]分情况处理:
  // 为'0'则向左, 为'1'则向右, 其他情况报错.
  hnode* p = root;
  for (size_t i = 0; i < code.size(); ++i)
  {
    // 无法访问树的结点则退出.
    if (p == NULL)
      return C.size();
    if (code[i] == '0')
      p = p->left;
    else if (code[i] == '1')
      p = p->right;
    else
      return C.size();
  }
  // 若能正确译码则返回符号的编号.
  return (p != NULL) ? p->number : C.size();
}

const string& Huffman::codeword(size_t i)
{
  return C[i];
}

size_t Huffman::size()
{
  return C.size();
}
