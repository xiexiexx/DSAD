#include <vector>
#include <algorithm>

#ifndef SORTEDVECTOR_CLASS
#define SORTEDVECTOR_CLASS

template <typename T>
class sorted_vector_with_large_capacity {
public:
  // 构造函数.
  sorted_vector_with_large_capacity();
  // 将key放入集合中.
  void insert(const T& key);
  // 将pos位置所在的元素删除, 前提是集合非空且pos在[0, size())区间内.
  void erase(size_t pos);
  // 若key在集合中则返回其位置, 否则返回size().
  size_t find(const T& key) const;
  // 返回集合中最大元素的位置, 若集合为空则返回size().
  size_t maximum_at() const;
  // 返回集合中最小元素的位置, 若集合为空则返回size().
  size_t minimum_at() const;
  // 返回pos位置元素的常量引用, 注意未提供非常量版本.
  const T& operator()(size_t pos) const;
  // 返回集合中元素的个数.
  size_t size() const;
private:
  std::vector<T> data;
};

// 简记为SV.
template <typename T>
using SV = sorted_vector_with_large_capacity<T>;

template <typename T>
sorted_vector_with_large_capacity<T>::
  sorted_vector_with_large_capacity()
{
  // 为其设置较大容量, 初始向量容量定为3142, 元素个数为0.
  data.reserve(3142);
}

template <typename T>
void sorted_vector_with_large_capacity<T>::
  insert(const T& key)
{
  // 请注意: 也可以用线性查找获取合适的迭代器插入位置,
  // 若是找不到合适的位置则意味应插入末尾.
  // 这里采用更好的方案也即二分查找, 注意调用的是upper_bound.
  auto iter = upper_bound(data.begin(), data.end(), key);
  // 直接使用向量的插入功能.
  data.insert(iter, key);
}

template <typename T>
void sorted_vector_with_large_capacity<T>::
  erase(size_t pos)
{
  // 执行erase的前提是pos位置有元素可删. 另外, 也可使用向量的erase操作.
  for (size_t i = pos + 1; i < data.size(); ++i)
    data[i - 1] = data[i];  // 也可使用移动语义.
  data.pop_back();
}

template <typename T>
size_t sorted_vector_with_large_capacity<T>::
  find(const T& key) const
{
  // 使用二分查找, 注意这里调用的是lower_bound.
  auto iter = lower_bound(data.begin(), data.end(), key);
  // 注意我们没有用==运算符来判定, 而是用<运算符构造的相等关系,
  // 主要原因是STL中的二分查找仅使用<运算符, ==运算符可能只是等价关系.
  // 此外, 由于向量连续存储元素, 可用迭代器减法得到下标的偏移值.
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
  operator()(size_t pos) const
{
  return data[pos];
}

template <typename T>
size_t sorted_vector_with_large_capacity<T>::
  size() const
{
  return data.size();
}

#endif  // SORTEDVECTOR_CLASS
