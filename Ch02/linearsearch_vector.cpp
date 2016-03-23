size_t LinearSearch(int k, const vector<int>& vdata)
{
	// 输入: k - 待查值; vdata - 数据集.
	// 输出: 利用return语句返回.
	// vdata是一个存放int型数据的向量, 注意它已内蕴数据集长度vdata.size().
	// 在for循环中用向量长度替代N以表示实有元素个数.
	for (size_t pos = 0; pos < vdata.size(); pos++)
		if (vdata[pos] == k)
			return pos;		// 找到k, 返回位置信息.
	return vdata.size();	// 未找到k, 返回vdata.size().
}