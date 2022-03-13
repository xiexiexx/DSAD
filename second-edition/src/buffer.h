#include <vector>

#ifndef BUFFER_CLASS
#define BUFFER_CLASS

template <typename T>
class buffer {
public:
  buffer(size_t n);
  T& front();
  const T& front() const;
  void push(const T& item);
  void pop();
  size_t size() const;
  bool empty() const;
  bool full() const;
  size_t capacity() const;
private:
  std::vector<T> Q;
  // 缓冲区容量实为Q.size(), 单独设置length是为了避免频繁调用.
  size_t length;
  // 缓冲区元素个数.
  size_t count;
  // 缓冲区循环意义下的区间[left, right).
  size_t left;
  size_t right;
};

// 构造函数的实现.
template <typename T>
buffer<T>::buffer(size_t n)
  : Q(n), length(n), count(0), left(0), right(0)
{
}

// 返回队首.
template <typename T>
T& buffer<T>::front()
{
  return Q[left];
}

// 返回队首的常量版本.
template <typename T>
const T& buffer<T>::front() const
{
  return Q[left];
}

// 入队操作.
template <typename T>
void buffer<T>::push(const T& item)
{
  // 由用户判断是否缓冲区已满, 此处只实现入队.
  Q[right++] = item;
  if (right == length)
    right = 0;
  ++count;
}

// 出队操作.
template <typename T>
void buffer<T>::pop()
{
  if (++left == length)
    left = 0;
  --count;
}

// 返回缓冲区实有元素个数.
template <typename T>
size_t buffer<T>::size() const
{
  return count;
}

// 判断缓冲区是否为空.
template <typename T>
bool buffer<T>::empty() const
{
  return (count == 0);
}

// 判断缓冲区是否已满.
template <typename T>
bool buffer<T>::full() const
{
  return (count == length);
}

// 返回缓冲区最大容量.
template <typename T>
size_t buffer<T>::capacity() const
{
  return length;
}

#endif  // BUFFER_CLASS
