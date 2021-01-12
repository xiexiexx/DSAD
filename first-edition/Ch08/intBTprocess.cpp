#include "book.h"

// 前序遍历二叉树, 并在屏幕上输出遍历结果.
void preorderTraverse(intBTnode* p)
{
	if (p != NULL)
	{
		cout << p->data << ' ';			// 在屏幕上输出当前树根
		preorderTraverse(p->lChild);	// 前序遍历左子树
		preorderTraverse(p->rChild);	// 前序遍历右子树
	}
}

// 中序遍历二叉树, 并在屏幕上输出遍历结果.
void inorderTraverse(intBTnode* p)
{
	if (p != NULL)
	{
		inorderTraverse(p->lChild);		// 中序遍历左子树
		cout << p->data << ' ';			// 在屏幕上输出当前树根
		inorderTraverse(p->rChild);		// 中序遍历右子树
	}
}

// 后序遍历二叉树, 并在屏幕上输出遍历结果.
void postorderTraverse(intBTnode* p)
{
	if (p != NULL)
	{
		postorderTraverse(p->lChild);	// 后序遍历左子树
		postorderTraverse(p->rChild);	// 后序遍历右子树
		cout << p->data << ' ';			// 在屏幕上输出当前树根
	}
}

// 按层次遍历二叉树, 并在屏幕上输出遍历结果.
void levelorderTraverse(intBTnode* p)
{
	queue<intBTnode*> Q;
	if (p != NULL)
		Q.push(p);
	while (!Q.empty())
	{
		// 在屏幕上输出队首元素数据
		cout << Q.front()->data << ' ';
		// 队首对应结点左孩子不为NULL则入队
		if (Q.front()->lChild != NULL)
			Q.push(Q.front()->lChild);
		// 队首对应结点右孩子不为NULL则入队
		if (Q.front()->rChild != NULL)
			Q.push(Q.front()->rChild);
		Q.pop();	// 队首元素出队
	}
}

void simpleBTexample()
{
	int h;			// 二叉树的树高h
	cin >> h;
	if (h < 0)		// 树高为负则不处理
		return;
	// 高为h的完美二叉树中的结点总数
	int N = static_cast<int>(pow(2.0, h + 1) - 1);
	// 为方便起见, 一次性申请所有结点所需空间
	intBTnode* nodes = new intBTnode[N];
	int start = 0;	// 起始点
	int gap = 2;	// 间隔
	for (int i = start; i < N; i += gap)
	{
		nodes[i].data = i;
		nodes[i].lChild = NULL;
		nodes[i].rChild = NULL;
	}
	// 执行h次循环逐层向上建立树
	for (int L = 0; L < h; L++)
	{
		start = 2 * start + 1;	// 新层起始点
		gap *= 2;				// 新层间隔
		for (int i = start; i < N; i += gap)
		{
			nodes[i].data = i;
			nodes[i].lChild = nodes + i - gap / 4;
			nodes[i].rChild = nodes + i + gap / 4;
		}
	}
	// 树根结点指针为nodes + N / 2
	intBTnode* root = nodes + N / 2;
	preorderTraverse(root);
	cout << endl;
	inorderTraverse(root);
	cout << endl;
	postorderTraverse(root);
	cout << endl;
	levelorderTraverse(root);
	cout << endl;
	delete[] nodes;	// 释放所有结点
}
