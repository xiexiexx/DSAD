#include "book.h"

void InputandPreprocess(list<int>& L, int& MAX)
{
	L.clear();		// 清空L中所有数据.
	int data;
	cin >> data;
	MAX = data;		// 注意空序列时MAX为负整数.
	while (data >= 0)
	{
		// 使用push_back可以保留数据的输入次序.
		L.push_back(data);
		// 同时统计最大值.
		if (data > MAX)
			MAX = data;
		cin >> data;	// 读入数据.
	}
}

void Output(const list<int>& L)
{
	// 由于此次遍历不改变链的状态, 所以使用常量迭代器c_iter.
	// 常量迭代器可以保证对L的常量引用, 特别以cbegin和cend区别于begin和end.
	// 此外要特别注意for语句中使用常量迭代器遍历的惯用法.
	for (auto c_iter = L.cbegin(); c_iter != L.cend(); ++c_iter)
		cout << *c_iter << ' ';
}

void MeanofLarger(list<int>& L, int d, int MAX)
{
	// 注意空序列时不能调用本函数, 其他情况下的自然数序列均有正确返回值.
	// 计算阈值, 由于MAX最大, 只需大于等于阈值即可.
	int threshold = MAX - d;
	// 满足要求的数之总和, 以double型存储便于后续计算.
	double sum = 0;
	int n = 0;					// 满足要求的自然数个数.
	// 使用auto定义迭代器iter, 注意可能利用它删除元素,
	// 因为删除会改变容器状态, 所以iter是list<int>::iterator型的迭代器.
	auto iter = L.begin();
	while (iter != L.end())
	{
		if (*iter >= threshold)
		{
			sum += *iter;
			n++;
			++iter;		// 迭代器向前.
		}
		else
			iter = L.erase(iter);	// 删除后iter会被赋值到下一元素位置.
	}
	cout << "The mean of the larger numbers is " << sum / n << endl;
	cout << "Larger numbers: ";
	// 要求最后输出被保留的那些自然数, 所以需要再次遍历.
	Output(L);
}