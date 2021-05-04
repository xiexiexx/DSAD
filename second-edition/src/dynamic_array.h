// 包含std::swap.
#include <utility>

#ifndef DYNAMIC_ARRAY_CLASS
#define DYNAMIC_ARRAY_CLASS

template <typename T>
class dynamic_array {
public:
  explicit dynamic_array(size_t n = 0, const T& value = T());
  dynamic_array(const dynamic_array<T>& obj);
  ~dynamic_array();
  void swap(dynamic_array<T>& rhs);
  dynamic_array& operator=(const dynamic_array<T>& rhs);
  T& front();
  const T& front() const;
  T& back();
  const T& back() const;
  T& operator[](size_t i);
  const T& operator[](size_t i) const;
  void push_back(const T& item);
  void pop_back();
  size_t size() const;
  bool empty() const;
  size_t capacity() const;
  void reserve(size_t n);

  // 迭代器实为T*指针.
  using iterator = T*;
  using const_iterator = const T*;

  inline iterator begin();
  inline const_iterator cbegin() const;
  inline iterator end();
  inline const_iterator cend() const;
private:
  size_t array_capacity;
  size_t array_size;
  T* A;
  void initialize(size_t n);
  // 为了后续加倍方便, 有时需要初始设置一个恒定的正容量, 此处取16.
  static const size_t POSITIVE_CAPACITY = 16;
};

// 申请新空间并调整容量.
template <typename T>
void dynamic_array<T>::initialize(size_t n)
{
  // 为A新申请内存空间, 注意未考虑异常处理.
  A = new T[n];
  array_capacity = n;
}

// 为了满足后续需求, 提前调整数组容量.
template <typename T>
void dynamic_array<T>::reserve(size_t n)
{
  // n大于现有的array_capacity才生效.
  if (n > array_capacity)
  {
    // 新申请内存空间.
    T* X = new T[n];
    for(size_t i = 0; i < array_size; ++i)
      X[i] = A[i];
    // 释放原有空间, 并让A获得X指向的空间.
    delete[] A;
    A = X;
    array_capacity = n;
  }
}

// 构造函数的实现.
template <typename T>
dynamic_array<T>::dynamic_array(size_t n, const T& value)
  : array_size(0), A(NULL)
{
  // 构造函数只需一次, 因此关于n的判断无关乎性能.
  // 如果n为0, 则设定容量为POSITIVE_CAPACITY. 注意n不会为负.
  if (n > 0)
  {
    // 留出哨兵位置. 假设后续够用, 所以未将初始容量设成2 * n.
    initialize(n + 1);
    array_size = n;
    // 以构造函数的初值参数value对动态数组中所有元素赋值.
    for (size_t i = 0; i < array_size; ++i)
      A[i] = value;
  }
  else
    initialize(POSITIVE_CAPACITY);
}

// 复制构造函数的实现.
template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& obj)
  : array_size(obj.array_size)
{
  // 按照obj的容量申请新内存空间, 再逐个复制.
  initialize(obj.array_capacity);
  for (size_t i = 0; i < array_size; ++i)
    A[i] = obj.A[i];
}

// 析构函数的实现.
template <typename T>
dynamic_array<T>::~dynamic_array()
{
  delete[] A;
}

// 数据交换函数.
template <typename T>
void dynamic_array<T>::swap(dynamic_array<T>& rhs)
{
  std::swap(this->A, rhs.A);
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

// 返回动态数组首元素的引用.
template <typename T>
T& dynamic_array<T>::front()
{
  return A[0];
}

// 返回动态数组首元素的常量引用.
template <typename T>
const T& dynamic_array<T>::front() const
{
  return A[0];
}

// 返回动态数组尾元素的引用.
template <typename T>
T& dynamic_array<T>::back()
{
  return A[array_size - 1];
}

// 返回动态数组尾元素的常量引用.
template <typename T>
const T& dynamic_array<T>::back() const
{
  return A[array_size - 1];
}

// 运算符[]的重载实现.
template <typename T>
T& dynamic_array<T>::operator[](size_t i)
{
  return A[i];
}

// 运算符[]的重载实现的常量版本.
template <typename T>
const T& dynamic_array<T>::operator[](size_t i) const
{
  return A[i];
}

// 在动态数组末尾添加新元素.
template <typename T>
void dynamic_array<T>::push_back(const T& item)
{
  // 如果容量不够用, 则扩容至现有容量的两倍, 注意留有哨兵位置.
  if (array_size + 1 < array_capacity)
    A[array_size++] = item;
  else
  {
    // 防止item为A中的元素, 提前保存副本.
    T temp = item;
    reserve(2 * array_capacity);
    A[array_size++] = temp;
  }
}

// 删除动态数组的尾元素.
template <typename T>
void dynamic_array<T>::pop_back()
{
  --array_size;
}

// 返回动态数组的大小.
template <typename T>
size_t dynamic_array<T>::size() const
{
  return array_size;
}

// 判断动态数组是否为空.
template <typename T>
bool dynamic_array<T>::empty() const
{
  return (array_size == 0);
}

// 返回动态数组的当前容量.
template <typename T>
size_t dynamic_array<T>::capacity() const
{
  return array_capacity;
}

// 动态数组的起始位置begin(), 用于迭代器.
template <typename T>
inline typename dynamic_array<T>::iterator
  dynamic_array<T>::begin()
{
  return A;
}

// 动态数组的起始位置cbegin(), 用于常量迭代器.
template <typename T>
inline typename dynamic_array<T>::const_iterator
  dynamic_array<T>::cbegin() const
{
  return A;
}

// 动态数组的终结位置end(), 用于迭代器.
template <typename T>
inline typename dynamic_array<T>::iterator
  dynamic_array<T>::end()
{
  return (A + array_size);
}

// 动态数组的终结位置cend(), 用于常量迭代器.
template <typename T>
inline typename dynamic_array<T>::const_iterator
  dynamic_array<T>::cend() const
{
  return (A + array_size);
}

#endif  // DYNAMIC_ARRAY_CLASS
