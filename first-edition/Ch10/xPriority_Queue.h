#include <vector>

#ifndef xPRIORITY_QUEUE_H
#define xPRIORITY_QUEUE_H

// 默认内部使用vector作为存储.
template <typename T, typename Sequence = std::vector<T>>
class xPriority_Queue {
public:
	xPriority_Queue();
	const T& top() const;
	void push(const T& item);
	void pop();
	size_t size() const;
	bool empty() const;
private:
	// 关键操作: 上浮函数.
	void swim(size_t i);
	// 关键操作: 下沉函数.
	void sink(size_t i);
	Sequence c;
};

// 构造函数的实现.
template <typename T, typename Sequence>
xPriority_Queue<T, Sequence>::xPriority_Queue()
	: c(1)
{
	// 初始让c的长度为1, c[0]作为哨兵不存放真实元素.
}

// 返回最大元的常量版本.
template <typename T, typename Sequence>
const T& xPriority_Queue<T, Sequence>::top() const
{
	// 注意不可返回引用, 且执行本函数得要求优先级队列非空.
	return c[1];
}

// 将新元素放入优先级队列.
template <typename T, typename Sequence>
void xPriority_Queue<T, Sequence>::push(const T& item)
{
	// 将元素先插入c的末尾.
	c.push_back(item);
	// 随后在插入点进行上浮操作.
	swim(c.size() - 1);
}

// 删除最大元.
template <typename T, typename Sequence>
void xPriority_Queue<T, Sequence>::pop()
{
	// 前提是优先级队列非空, 于是c[1]必有元素.
	c[1] = c[ c.size() - 1 ];
	// 在1位置执行下沉操作, 注意此时c中最后一个元素无效.
	sink(1);
	// 下沉完毕再来调整c的大小, 如果提前调整可能c[1]会不存在.
	c.pop_back();
}

// 返回优先级队列的大小.
template <typename T, typename Sequence>
size_t xPriority_Queue<T, Sequence>::size() const
{
	// 实有元素为c.size() - 1.
	return c.size() - 1;
}

// 判断优先级队列是否为空.
template <typename T, typename Sequence>
bool xPriority_Queue<T, Sequence>::empty() const
{
	// c长度为1时则优先级队列为空.
	return (c.size() == 1);
}

// 在结点i处执行上浮操作.
template <typename T, typename Sequence>
void xPriority_Queue<T, Sequence>::swim(size_t i)
{
	// 在c[0]处设置哨兵以终止循环, 并保存初始结点i处的数据.
	c[0] = c[i];
	// 如果c[0]大于i位置的父亲结点值c[i / 2]则不断让i位置上浮,
	// 但初始结点处的数据暂不处理, 其值仍存于c[0].
	while (c[i / 2] < c[0])
	{
		c[i] = c[i / 2];
		i = i / 2;
	}
	// 将初始结点处的数据存于上浮操作最终停留的位置.
	c[i] = c[0];
}

// 在结点i处执行下沉操作.
template <typename T, typename Sequence>
void xPriority_Queue<T, Sequence>::sink(size_t i)
{
	// 当前c中最后一个元素已无效, 真实长度为c.size() - 1.
	size_t c_size = c.size() - 1;
	// 暂存c[i]数据, 注意后续操作是和c[0]比较.
	c[0] = c[i];
	// 结点的右孩子编号.
	size_t rChildNo = 2 * i + 1;
	// 右孩子存在(即左右孩子均存在)时的下沉.
	while (rChildNo < c_size)
	{
		// MAX为较大结点的编号, 注意其初值为0.
		size_t MAX = 0;
		// 右孩子较大则MAX换为右孩子编号.
		if (c[MAX] < c[rChildNo])
			MAX = rChildNo;
		// 左孩子较大则MAX换为左孩子编号.
		if (c[MAX] < c[rChildNo - 1])
			MAX = rChildNo - 1;
		// 断言: 不需要交换则下沉结束.
		if (MAX == 0)
			break;
		// 需要交换时先将较大的孩子存于i位置.
		c[i] = c[MAX];
		// 继续向下判断.
		i = MAX;
		rChildNo = 2 * i + 1;
	}
	// 处理特殊情况: 最后仅存在左孩子且需要继续下沉.
	if (rChildNo == c_size && c[0] < c[rChildNo - 1])
	{
		// 需要交换时先将左孩子存于i位置.
		c[i] = c[rChildNo - 1];
		// 获得最终停留位置.
		i = rChildNo - 1;
	}
	// 将初始结点处的数据存于下沉操作最终停留的位置.
	c[i] = c[0];
}

#endif  // xPRIORITY_QUEUE_H

