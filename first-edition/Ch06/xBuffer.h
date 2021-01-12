#include <vector>

#ifndef xBUFFER_H
#define xBUFFER_H

template <typename T>
class xBuffer {
public:
	// 声明友元模板类xQueue, 注意得用非绑定形式
	template <typename U>
		friend class xQueue;
	xBuffer(size_t n);
	T& front();
	const T& front() const;
	void push(const T& item);
	void pop();
	size_t size() const;
	bool empty() const;
	bool full() const;
	size_t capacity() const;
private:
	std::vector<T> buffer;
	size_t count;
	size_t bFront;
	size_t bRear;
};

// 构造函数的实现
template <typename T>
xBuffer<T>::xBuffer(size_t n)
	: buffer(n), count(0), bFront(0), bRear(n - 1)
{
}

// 返回队首
template <typename T>
T& xBuffer<T>::front()
{
	return buffer[bFront];
}

// 返回队首的常量版本
template <typename T>
const T& xBuffer<T>::front() const
{
	return buffer[bFront];
}

// 入队操作
template <typename T>
void xBuffer<T>::push(const T& item)
{
	// 由用户判断是否缓冲区已满, 此处只实现入队
	bRear = (bRear + 1) % buffer.size();
	buffer[bRear] = item;
	count++;
}

// 出队操作
template <typename T>
void xBuffer<T>::pop()
{
	bFront = (bFront + 1) % buffer.size();
	count--;
}

// 返回缓冲区实有元素个数
template <typename T>
size_t xBuffer<T>::size() const
{
	return count;
}

// 判断缓冲区是否为空
template <typename T>
bool xBuffer<T>::empty() const
{
	return (count == 0);
}

// 判断缓冲区是否已满
template <typename T>
bool xBuffer<T>::full() const
{
	return (count == buffer.size());
}

// 返回缓冲区最大容量
template <typename T>
size_t xBuffer<T>::capacity() const
{
	return buffer.size();
}

#endif  // xBUFFER_H
