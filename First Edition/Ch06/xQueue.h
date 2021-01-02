#include "xBuffer.h"

#ifndef xQUEUE_H
#define xQUEUE_H

template <typename T>
class xQueue {
public:
	xQueue();
	~xQueue();
	T& front();
	const T& front() const;
	void push(const T& item);
	void pop();
	size_t size() const;
	bool empty() const;
private:
	void MapReserve(size_t n);			// 为映射缓冲区储备空间
	static const int blockSize = 16;	// 数据块长度
	xBuffer<xBuffer<T>*> qMap;		// 由数据块指针形成的队列
	size_t qCount;						// 队列中实有元素个数
};

// 构造函数的实现
template <typename T>
xQueue<T>::xQueue()
	: qMap(blockSize * blockSize), qCount(0)
{
	// 初始均为空数据块
	for (size_t i = 0; i < qMap.capacity(); i++)
		qMap.buffer[i] = NULL;
}

// 析构函数的实现
template <typename T>
xQueue<T>::~xQueue()
{
	// 释放所有数据块
	for (size_t i = 0; i < qMap.capacity(); i++)
		delete qMap.buffer[i];
}

// 返回队首
template <typename T>
T& xQueue<T>::front()
{
	return qMap.front()->front();
}

// 返回队首的常量版本
template <typename T>
const T& xQueue<T>::front() const
{
	return qMap.front()->front();
}

template <typename T>
void xQueue<T>::MapReserve(size_t n)
{
	// n必须大于目前缓冲区的容量
	size_t pos = qMap.capacity();	// 记录原有容量
	qMap.buffer.resize(n);
	size_t i;
	for (i = pos; i < qMap.capacity(); i++)
		qMap.buffer[i] = NULL;		// 令其不指向数据块
	// 注意需要处理连续性问题
	if (qMap.count > 0 && qMap.bFront > qMap.bRear)
	{
		// 不连续时将映射缓冲区内容重新安置以保证循环意义上的连续
		for (i = 0; i <= qMap.bRear; i++)
		{
			qMap.buffer[pos] = qMap.buffer[i];		// 移动数据块指针
			qMap.buffer[i] = NULL;					// 原有位置不指向数据块
			pos = (pos + 1) % qMap.capacity();
		}
		qMap.bRear = (pos + qMap.capacity() - 1) % qMap.capacity();
	}
}

// 入队操作
template <typename T>
void xQueue<T>::push(const T& item)
{
	// 队列中所有数据块已满, 应增加映射缓冲区容量
	if (qCount == qMap.capacity() * blockSize)
		MapReserve(2 * qMap.size());	// 加倍
	// 考虑需要处理数据块的情况, 注意不可直接对qMap使用push操作.
	// 队列中无任何元素或队尾数据块已满都应处理, 判断语句使用短路求值.
	if (qCount == 0 || qMap.buffer[qMap.bRear]->full())
	{
		// 数据块位置循环后移一格
		qMap.bRear = (qMap.bRear + 1) % qMap.capacity();
		// 数据块个数增加
		qMap.count++;
	}
	// 数据块为空, 则为其分配存储空间. 
	if (qMap.buffer[qMap.bRear] == NULL)
		qMap.buffer[qMap.bRear] = new xBuffer<T>(blockSize);
	qMap.buffer[qMap.bRear]->push(item);
	qCount++;
}

// 出队操作
template <typename T>
void xQueue<T>::pop()
{
	qMap.front()->pop();
	// 若队首数据块中已无数据, 应将其出队, 注意实际指针和相应数据块仍在.
	if (qMap.front()->empty())
		qMap.pop();	// 此处不必自行编写出队操作
	qCount--;
}

// 返回队列实有元素个数
template <typename T>
size_t xQueue<T>::size() const
{
	return qCount;
}

// 判断队列是否为空
template <typename T>
bool xQueue<T>::empty() const
{
	return (qCount == 0);
}

#endif  // xQUEUE_H
