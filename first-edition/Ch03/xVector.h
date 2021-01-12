// 包含std::swap
#include <utility>

#ifndef xVECTOR_H
#define xVECTOR_H

template <typename T>
class xVector {
public:
	explicit xVector(size_t size = 0, const T& initVal = T());
	xVector(const xVector<T>& obj);
	~xVector();
	void swap(xVector<T>& rhs);
	xVector& operator= (const xVector<T>& rhs);
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	T& operator[] (size_t i);
	const T& operator[] (size_t i) const;
	void push_back(const T& item);
	void pop_back();
	size_t size() const;
	bool empty() const;
	size_t capacity() const;
	void reserve(size_t n);
private:
	size_t vCapacity;	
	size_t vSize;		
	T* V;
	void vAllocate(size_t n);
	// 有时需要在初始给向量一个非零容量, 此处取16
	static const size_t positive_capacity = 16;
};

// 申请新空间并调整容量
template <typename T>
void xVector<T>::vAllocate(size_t n)
{
	V = new T[n];		// 让V获得新申请内存空间
	vCapacity = n;
}

// 为满足更大的需求调整向量大小, 但初学者不建议使用.
template <typename T>
void xVector<T>::reserve(size_t n)
{
	// n大于现有的vCapacity才生效
	if (n > vCapacity)
	{
		T* Vx = new T[n];	// 新申请内存空间
		for(size_t i = 0; i < vSize; i++)
			Vx[i] = V[i];
		delete[] V;			// 释放原有空间
		V = Vx;				// 让V获得Vx指向的空间
		vCapacity = n;
	}
}

// 构造函数的实现
template <typename T>
xVector<T>::xVector(size_t size, const T& initVal)
	: vSize(0), V(NULL)
{
	// 构造函数只需要做一次, 因此这种判断无关乎性能. 此外, 注意size不会为负.
	if (size > 0)
	{
		vAllocate(2 * size);
		vSize = size;
		// 以构造函数的初值参数initVal对向量中所有元素赋值
		for (size_t i = 0; i < vSize; i++)
			V[i] = initVal;
	}
	else	// 为后续加倍方便, 初始给向量一个非零容量
		vAllocate(positive_capacity);
}

// 复制构造函数的实现
template <typename T>
xVector<T>::xVector(const xVector<T>& obj)
	: vSize(obj.vSize)
{
	vAllocate(obj.vCapacity);	// 按照obj的容量申请新内存空间
	for (size_t i = 0; i < vSize; i++)
		V[i] = obj.V[i];		// 逐个复制
}

// 析构函数的实现
template <typename T>
xVector<T>::~xVector()
{
	delete[] V;
}

// 数据交换函数
template <typename T>
void xVector<T>::swap(xVector<T>& rhs)
{
	std::swap(this->V, rhs.V);
	std::swap(this->vCapacity, rhs.vCapacity);
	std::swap(this->vSize, rhs.vSize);
}

// 运算符=的重载实现
template <typename T>
xVector<T>& xVector<T>::operator=(const xVector<T>& rhs)
{
	// 惯用法: copy and swap
	xVector<T> temp(rhs);
	// 交换this和temp的数据部分
	swap(temp);
	return *this;
}

// 返回向量首部
template <typename T>
T& xVector<T>::front()
{
	return V[0];
}

// 返回向量首部的常量版本
template <typename T>
const T& xVector<T>::front() const
{
	return V[0];
}

// 返回向量末尾
template <typename T>
T& xVector<T>::back()
{
	return V[vSize - 1];
}

// 返回向量末尾的常量版本
template <typename T>
const T& xVector<T>::back() const
{
	return V[vSize - 1];
}

// 运算符[]的重载实现
template <typename T>
T& xVector<T>::operator[] (size_t i)
{
	return V[i];
}

// 运算符[]的重载实现的常量版本
template <typename T>
const T& xVector<T>::operator[] (size_t i) const
{
	return V[i];
}

// 在向量末尾添加新元素
template <typename T>
void xVector<T>::push_back(const T& item)
{
	// 如果容量不够用, 则扩容至现有容量的两倍.
	if (vSize == vCapacity)
	{
		// 防止item为V中的元素, 提前保存副本.
		T item_copy = item;
		reserve(2 * vCapacity);
		V[vSize] = item_copy;
	}
	else
		V[vSize] = item;
	vSize++;
}

// 去除向量的末尾元素
template <typename T>
void xVector<T>::pop_back()
{
	vSize--;
}

// 返回向量的大小
template <typename T>
size_t xVector<T>::size() const
{
	return vSize;
}

// 判断向量是否为空
template <typename T>
bool xVector<T>::empty() const
{
	return (vSize == 0);
}

// 返回向量的当前容量
template <typename T>
size_t xVector<T>::capacity() const
{
	return vCapacity;
}

#endif  // xVECTOR_H
