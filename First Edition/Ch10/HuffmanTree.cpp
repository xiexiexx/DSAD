#include "HuffmanTree.h"

#include <queue>
using std::priority_queue;

using std::vector;
using std::string;

HuffmanTree::HuffmanTree(HuffmanNode* p)
	: root(p)
{
	// 以指针p对根结点进行构造
}

void HuffmanTree::CodingAll(HuffmanNode* p, const string& prefix)
{
	// 若p不为NULL则递归对以p为根的子树所有结点进行编码
	if (p != NULL)
	{
		// 结点p的左子树所有前缀是prefix配0
		CodingAll(p->lChild, prefix + "0");
		// 结点p的右子树所有前缀是prefix配1
		CodingAll(p->rChild, prefix + "1");
		// 叶子结点编号为自然数, 以此对编码向量相应位置赋码字prefix.
		if (p->number < HC.size())
			HC[p->number] = prefix;
	}
}

void HuffmanTree::HuffmanCoding(const vector<double>& P, vector<string>& C)
{
	// 编码向量HC的长度设置为概率向量的长度.
	HC.resize(P.size());
	// 存储Huffman树的最小优先级队列PQ, 优先级为树的权值, 
	// 实际存储的是树的根结点指针. 
	priority_queue<HuffmanNode*,
		vector<HuffmanNode*>, greater_HuffmanNodePointer> PQ;
	// 一次性给出所有在编码中会出现的结点
	vector<HuffmanNode> data (2 * P.size() - 1);
	// index作为编号, 指示当前会使用data[index]处的结点.
	size_t index;		// 注意其作用域不仅限于下面的for循环.
	// 初始放入n个仅有根结点的树
	for (index = 0; index < P.size(); index++)
	{
		// 对应需编码的符号, 编号为自然数.
		data[index].number = index;
		// 结点权值按照概率向量赋值
		data[index].weight = P[index];
		data[index].lChild = NULL;
		data[index].rChild = NULL;
		// 放入优先级队列中
		PQ.push(&data[index]);
	}
	// 循环处理以构建Huffman树
	while (PQ.size() > 1)
	{
		// 取新结点数据
		HuffmanNode* p = &data[index];
		// 新出现的结点编号统一为HC.size()
		p->number = HC.size();
		// 将优先级队列中的最小元作为p的左孩子
		p->weight = PQ.top()->weight;
		p->lChild = PQ.top();
		// 取出最小元
		PQ.pop();
		// 将优先级队列中的最小元作为p的右孩子
		p->weight += PQ.top()->weight;
		p->rChild = PQ.top();
		// 取出最小元
		PQ.pop();
		// 将新的树放入优先级队列
		PQ.push(p);
		// 编号更新, 下次使用新结点.
		index++;
	}
	// 若PQ不空则可根据起中所剩的唯一Huffman树进行编码
	if (!PQ.empty())
	{
		CodingAll(PQ.top(), "");
		C = HC;		// 将最终编码复制给C
	}
}