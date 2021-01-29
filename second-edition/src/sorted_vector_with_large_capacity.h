#include <vector>
#include <algorithm>

#ifndef SORTEDVECTOR_H
#define SORTEDVECTOR_H

template <typename T>
class sorted_vector_with_large_capacity {
public:
  // 构造函数.
  sorted_vector_with_large_capacity();
  // 将key放入集合中.
  void insert(const T& key);
  // 将pos位置所在的元素删除, 前提是集合非空且pos在0到size() - 1之间.
  void erase(size_t pos);
  // 若key在集合中则返回其位置, 否则返回size().
  size_t find(const T& key) const;
  // 返回集合中最大元素的位置, 若集合为空则返回size().
  size_t maximum_at() const;
  // 返回集合中最小元素的位置, 若集合为空则返回size().
  size_t minimum_at() const;
  // 返回pos位置元素的常量引用, 注意未提供非常量版本.
  const T& operator()(int pos) const;
  // 返回集合中元素的个数.
  size_t size() const;
private:
  std::vector<T> data;
};

// 简记为S1.
template <typename T>
using S1 = sorted_vector_with_large_capacity<T>;

template <typename T>
sorted_vector_with_large_capacity<T>::
  sorted_vector_with_large_capacity()
{
  // 为其设置较大容量, 初始向量长度定为3142, 元素个数定为0.
  data.reserve(3142);
}

template <typename T>
void sorted_vector_with_large_capacity<T>::
  insert(const T& key)
{
  // 可以线性查找找出合适的迭代器插入位置,
  // 若找不到合适的位置则意味应插入末尾.
  // 更好的方案是基于二分查找完成, 注意我们调用的是upper_bound.
  auto iter = upper_bound(data.begin(), data.end(), key);
  data.insert(iter, key);
}

template <typename T>
void sorted_vector_with_large_capacity<T>::
  erase(size_t pos)
{
  // 也可以使用向量的erase操作.
  for (size_t i = pos; i < data.size() - 1; ++i)
    data[i] = data[i + 1];
  data.pop_back();
}

template <typename T>
size_t sorted_vector_with_large_capacity<T>::
  find(const T& key) const
{
  auto iter = lower_bound(data.begin(), data.end(), key);
  // 注意我们没有用==运算符来判定, 而是用<运算符构造的等价关系.
  if (iter != data.end() && !(*iter < key) && !(key < *iter))
    return iter - data.begin();   // 找到.
  return data.size();             // 未找到.
}

template <typename T>
size_t sorted_vector_with_large_capacity<T>::
  maximum_at() const
{
  // 注意集合为空时仍然返回0.
  return data.size() > 0 ? data.size() - 1 : 0;
}

template <typename T>
size_t sorted_vector_with_large_capacity<T>::
  minimum_at() const
{
  // 注意集合为空时仍然返回0.
  return 0;
}

template <typename T>
const T& sorted_vector_with_large_capacity<T>::
  operator()(int pos) const
{
  return data[pos];
}

template <typename T>
size_t sorted_vector_with_large_capacity<T>::
  size() const
{
  return data.size();
}

#endif  // SORTEDVECTOR_H
