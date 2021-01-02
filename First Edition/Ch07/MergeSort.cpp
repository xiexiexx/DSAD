#include "book.h"

// 将有序单链R归并到有序单链L中, 保持L的有序性.
template <typename T>
void Merge(forward_list<T>& L, forward_list<T>& R)
{
	// 定位归并目标位置的迭代器.
	auto iter_dest = L.before_begin();
	// 单链L的迭代器, 初始位置为L.begin().
	auto iter_L = L.begin();
	// 单链R的迭代器, 初始位置为R.begin().
	auto iter_R = R.begin();
	// L和R都有元素可用于归并.
	while (iter_L != L.end() && iter_R != R.end())
	{
		if (*iter_L < *iter_R)
			++iter_L;	// L的迭代器前进, 不需插入.
		else
		{
			// 将R中元素插入目标位置.
			L.insert_after(iter_dest, *iter_R);
			++iter_R;	// R的迭代器前进.
		}
		++iter_dest;	// 目标位置迭代器前进.
	}
	// 将R中剩余部分[iter_R, R.end())范围元素插入, 若无元素则不会插入.
	L.insert_after(iter_dest, iter_R, R.end());
}

// 对单链data中元素进行归并排序.
template <typename T>
void MergeSort(forward_list<T>& data)
{
	// 包含若干有序单链的单链L_in_L.
	forward_list<forward_list<T>> L_in_L;
	size_t n = 0;		// 记录数据个数.
	// 建立若干单链, 每个单链只含一个data中的元素.
	// 注意iter在插入之后被赋值为新插入元素所在的位置.
	auto iter = L_in_L.before_begin();
	for (auto iter_d = data.begin(); iter_d != data.end(); ++iter_d)
	{
		iter = L_in_L.insert_after(iter, forward_list<T>(1, *iter_d));
		n++;
	}
	// 若链中至少剩余两个元素则持续归并.
	while (n > 1)
	{
		// 若L_in_L中不止一个有序单链, 则进行一趟归并.
		size_t L = n;
		auto iter_L = L_in_L.begin();
		// 一趟归并中每次将两个有序单链归并成一个, 如果还可归并则不断进行.
		while (L > 1)
		{
			auto iter_R = iter_L;
			++iter_R;
			// 将iter_L和iter_R指示的单链归并.
			Merge(*iter_L, *iter_R);
			// 当前迭代器位置依次为iter_L, iter_R, iter_N.
			// 删除iter_R所指示的单链, 并让iter_L变为iter_N.
			iter_L = L_in_L.erase_after(iter_L);
			// 本趟归并所剩余的有序单链数减少2.
			L -= 2;
			// L_in_L中有序单链数减少1.
			n--;
		}
	}
	// 最后只剩下一个有序单链, 则排序成功.
	if (n == 1)
		data = L_in_L.front();
}
