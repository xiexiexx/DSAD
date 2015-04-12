#include <vector>

#ifndef xORDEREDVECTOR_H
#define xORDEREDVECTOR_H

template <typename T>
class S1 {
public:
	// 构造函数.
	S1();
	// 将key放入集合中.
	void insert(const T& key);
	// 将pos位置所在的元素删除, 前提是pos在0到size() - 1之间.
	void erase(int pos);
	// 若key在集合中则返回其位置, 否则返回size().
	int search(const T& key) const;
	// 返回集合中最大元素的位置, 若集合为空则返回size().
	int maximum_at() const;
	// 返回集合中最小元素的位置, 若集合为空则返回size().
	int minimum_at() const;
	// 返回pos位置元素的常量引用, 注意未提供非常量版本
	const T& operator()(int pos) const;
	// 返回集合中元素的个数.
	int size() const;
private:
	std::vector<T> data;
	int count;					// 实有数据个数
};

template <typename T>
S1<T>::S1()
	: data(1024), count(0)
{
	// 为其设置较大容量, 初始向量长度定为1024, 元素个数定为0.
}

template <typename T>
void S1<T>::insert(const T& key)
{
	int i = 0;
	// 利用类似线性查找的方法先找出合适的插入位置pos.
	// 若找不到合适的位置则意味应插入末尾, 因此注意pos的初值.
	// 更好的方案是基于二分查找快速找到pos.
	int pos = count;
	while (i < count)
	{
		if (key < data[i])
		{
			pos = i;
			i = count;
		}
		else
			i++;
	}
	if (count == data.size())
	{
		// 防止key为data中的元素, 提前保存副本.
		T key_copy = key;
		data.resize( 2 * data.size() );
		for (i = count; i > pos; i--)
			data[i] = data[i - 1];
		data[pos] = key_copy;
	}
	else
	{
		for (i = count; i > pos; i--)
			data[i] = data[i - 1];
		data[pos] = key;
	}
	count++;
}

template <typename T>
void S1<T>::erase(int pos)
{
	// 技巧: 先减少count, 后面可直接使用i < count
	count--;
	for (int i = pos; i < count; i++)
		data[i] = data[i + 1];
}

template <typename T>
int S1<T>::search(const T& key) const
{
	int low = 0;
	int high = count - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (key < data[mid])
			high = mid - 1;
		else if (data[mid] < key)
			low = mid + 1;
		else
			return mid;		// 找到
	}
	return count;			// 未找到
}

template <typename T>
int S1<T>::maximum_at() const
{
	// 采用循环式设计, 总长为count + 1, 
	// 循环是(count - 1 + count + 1) % (count + 1),
	// 如此可保证集合为空时所返回的位置信息.
	return (count + count) % (count + 1);
	// 或采用 return count > 0 ? count - 1 : 0;
}

template <typename T>
int S1<T>::minimum_at() const
{
	// 注意集合为空时仍然返回0.
	return 0;
}

template <typename T>
const T& S1<T>::operator()(int pos) const
{
	return data[pos];
}

template <typename T>
int S1<T>::size() const
{
	return count;
}

#endif  // xORDEREDVECTOR_H
