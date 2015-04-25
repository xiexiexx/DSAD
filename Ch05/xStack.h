#include <deque>

#ifndef xSTACK_H
#define xSTACK_H

// 默认内部使用deque作为存储
template <typename T, typename Sequence = std::deque<T>>
class xStack {
public:
	// 将迭代器Sequence::const_iterator作为嵌套类型
	// 使用xStack<T>::const_iterator实为Sequence::const_iterator
	typedef typename Sequence::const_iterator const_iterator;
	xStack();
	T& top();
	const T& top() const;
	void push(const T& item);
	void pop();
	size_t size() const;
	bool empty() const;
	const_iterator begin() const;
	const_iterator end() const;
private:
	Sequence c;
};

// 构造函数的实现
template <typename T, typename Sequence>
xStack<T, Sequence>::xStack()
{
}

// 返回栈顶元素
template <typename T, typename Sequence>
T& xStack<T, Sequence>::top()
{
	return c.back();
}

// 返回栈顶元素的常量版本
template <typename T, typename Sequence>
const T& xStack<T, Sequence>::top() const
{
	return c.back();
}

// 将新元素入栈
template <typename T, typename Sequence>
void xStack<T, Sequence>::push(const T& item)
{
	c.push_back(item);
}

// 栈顶元素出栈
template <typename T, typename Sequence>
void xStack<T, Sequence>::pop()
{
	c.pop_back();
}

// 返回栈的大小
template <typename T, typename Sequence>
size_t xStack<T, Sequence>::size() const
{
	return c.size();
}

// 判断栈是否为空
template <typename T, typename Sequence>
bool xStack<T, Sequence>::empty() const
{
	return (c.size() == 0);
}

template <typename T, typename Sequence>
inline typename xStack<T, Sequence>::const_iterator
	xStack<T, Sequence>::begin() const
{
	return c.begin();
}

template <typename T, typename Sequence>
inline typename xStack<T, Sequence>::const_iterator
	xStack<T, Sequence>::end() const
{
	return c.end();
}

#endif  // xSTACK_H
