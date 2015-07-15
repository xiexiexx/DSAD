#include "xUF.h"
#include <stack>

xUF::xUF(size_t n)
	: PR(n, -1), countUF(n)
{
	// 构造函数对PR中n个元素全赋值为-1
}

void xUF::Union(int x, int y)
{
	int r_x = Find(x);	// 寻找x所在集合的代表元r_x
	int r_y = Find(y);	// 寻找y所在集合的代表元r_y
	// x和y不在一个集合中则进行合并
	if (r_x != r_y)
	{
		countUF--;
		// 挑选负秩较小(秩较大)的树之根结点作为新的代表元
		if (PR[r_x] > PR[r_y])
			PR[r_x] = r_y;			// r_y为新代表元
		else if (PR[r_x] < PR[r_y])
			PR[r_y] = r_x;			// r_x为新代表元
		else
		{
			// 秩相等则任选一个根结点, 这里选r_x
			PR[r_y] = r_x;			// r_x为新代表元
			PR[r_x]--;				// 负秩减1(即秩加1)
		}
	}
}

int xUF::Find(int x)
{
	std::stack<int> S;
	// 在查找代表元过程中以栈保存路径中所有结点
	while (PR[x] >= 0)
	{
		S.push(x);
		x = PR[x];
	}
	// 随后进行路径压缩
	while (!S.empty())
	{
		PR[S.top()] = x;
		S.pop();
	}
	return x;
}

size_t xUF::size() const
{
	return PR.size();
}

size_t xUF::count() const
{
	return countUF;
}
