template <typename T>
void BinarySearch(const T& key, const T data[], int N, bool& found, int& pos)
{
	// 输入: key - 待查元素; data - 有序数据集(从小到大排列); N - 数据集长度.
	// 输出: found - 标记key是否找到; pos - 所找到的位置.
	found = false;
	pos = N;
	int low = 0;
	int high = N - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (key < data[mid])		// 小则去前半部分继续查找
			high = mid - 1;
		else if (data[mid] < key)	// 大则去后半部分继续查找
			low = mid + 1;
		else
		{
			pos = mid;
			found = true;
			break;					// 找到则跳出循环
		}
	}
} 
