int LinearSearch(int k, const int data[], int N)
{
	// 输入: k - 待查值; data - 数据集; N - 数据集长度.
	// 输出: 利用return语句返回.
	for (int pos = 0; pos < N; pos++)
		if (data[pos] == k)
			return pos;		// 找到k, 返回位置信息.
	return N;				// 未找到k, 返回N.
}