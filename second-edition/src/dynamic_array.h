#include <utility>  // 包含std::swap.

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template <typename T>
class dynamic_array {
public:
  explicit dynamic_array(size_t size = 0, const T& value = T());
  dynamic_array(const dynamic_array<T>& obj);
  ~dynamic_array();
  void swap(dynamic_array<T>& rhs);
  dynamic_array& operator= (const dynamic_array<T>& rhs);
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

  using iterator = T*;
  using const_iterator = const T*;
  inline iterator begin();
  inline const_iterator cbegin() const;
  inline iterator end();
  inline const_iterator cend() const;
private:
  size_t array_capacity;
  size_t array_size;
  T* V;
  void initialize(size_t n);
  // 有时需要在初始给向量一个恒定正容量, 此处取16.
  static const size_t POSITIVE_CAPACITY = 16;
};

// 申请新空间并调整容量.
template <typename T>
void dynamic_array<T>::initialize(size_t n)
{
  // 为V新申请内存空间.
  V = new T[n];
  array_capacity = n;
}

// 为满足更大的需求调整向量大小, 但初学者不建议使用.
template <typename T>
void dynamic_array<T>::reserve(size_t n)
{
  // n大于现有的array_capacity才生效.
  if (n > array_capacity)
  {
    T* X = new T[n];  // 新申请内存空间.
    for(size_t i = 0; i < array_size; ++i)
      X[i] = V[i];
    delete[] V;       // 释放原有空间.
    V = X;            // 让V获得X指向的空间.
    array_capacity = n;
  }
}

// 构造函数的实现.
template <typename T>
dynamic_array<T>::dynamic_array(size_t size, const T& value)
  : array_size(0), V(NULL)
{
  // 构造函数只需一次, 因此这种判断无关乎性能. 此外, 注意size不会为负.
  if (size > 0)
  {
    initialize(2 * size);
    array_size = size;
    // 以构造函数的初值参数value对向量中所有元素赋值.
    for (size_t i = 0; i < array_size; ++i)
      V[i] = value;
  }
  else  // 为后续加倍方便, 初始给向量一个恒定正容量.
    initialize(POSITIVE_CAPACITY);
}

// 复制构造函数的实现.
template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& obj)
  : array_size(obj.array_size)
{
  initialize(obj.array_capacity); // 按照obj的容量申请新内存空间.
  for (size_t i = 0; i < array_size; ++i)
    V[i] = obj.V[i];              // 逐个复制.
}

// 析构函数的实现.
template <typename T>
dynamic_array<T>::~dynamic_array()
{
  delete[] V;
}

// 数据交换函数.
template <typename T>
void dynamic_array<T>::swap(dynamic_array<T>& rhs)
{
  std::swap(this->V, rhs.V);
  std::swap(this->array_capacity, rhs.array_capacity);
  std::swap(this->array_size, rhs.array_size);
}

// 运算符=的重载实现.
template <typename T>
dynamic_array<T>& dynamic_array<T>::
  operator=(const dynamic_array<T>& rhs)
{
  // 惯用法: copy and swap.
  dynamic_array<T> temp(rhs);
  // 交换this和temp的数据部分.
  swap(temp);
  return *this;
}

// 返回向量首部.
template <typename T>
T& dynamic_array<T>::front()
{
  return V[0];
}

// 返回向量首部的常量版本.
template <typename T>
const T& dynamic_array<T>::front() const
{
  return V[0];
}

// 返回向量末尾.
template <typename T>
T& dynamic_array<T>::back()
{
  return V[array_size - 1];
}

// 返回向量末尾的常量版本.
template <typename T>
const T& dynamic_array<T>::back() const
{
  return V[array_size - 1];
}

// 运算符[]的重载实现.
template <typename T>
T& dynamic_array<T>::operator[] (size_t i)
{
  return V[i];
}

// 运算符[]的重载实现的常量版本.
template <typename T>
const T& dynamic_array<T>::operator[] (size_t i) const
{
  return V[i];
}

// 在向量末尾添加新元素.
template <typename T>
void dynamic_array<T>::push_back(const T& item)
{
  // 如果容量不够用, 则扩容至现有容量的两倍.
  if (array_size == array_capacity)
  {
    // 防止item为V中的元素, 提前保存副本.
    T item_copy = item;
    reserve(2 * array_capacity);
    V[array_size++] = item_copy;
  }
  else
    V[array_size++] = item;
}

// 去除向量的末尾元素.
template <typename T>
void dynamic_array<T>::pop_back()
{
  --array_size;
}

// 返回向量的大小.
template <typename T>
size_t dynamic_array<T>::size() const
{
  return array_size;
}

// 判断向量是否为空.
template <typename T>
bool dynamic_array<T>::empty() const
{
  return (array_size == 0);
}

// 返回向量的当前容量.
template <typename T>
size_t dynamic_array<T>::capacity() const
{
  return array_capacity;
}

// 向量的初始位置begin(), 用于迭代器.
template <typename T>
inline typename dynamic_array<T>::iterator
  dynamic_array<T>::begin()
{
	return V;
}

// 向量的初始位置cbegin(), 用于常量迭代器.
template <typename T>
inline typename dynamic_array<T>::const_iterator
  dynamic_array<T>::cbegin() const
{
	return V;
}

// 向量的初始位置end(), 用于迭代器.
template <typename T>
inline typename dynamic_array<T>::iterator
  dynamic_array<T>::end()
{
	return (V + array_size);
}

// 向量的初始位置cend(), 用于常量迭代器.
template <typename T>
inline typename dynamic_array<T>::const_iterator
  dynamic_array<T>::cend() const
{
	return (V + array_size);
}

#endif  // DYNAMIC_ARRAY_H
