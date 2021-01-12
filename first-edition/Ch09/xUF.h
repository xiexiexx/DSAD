#include <vector>

#ifndef X_UF
#define X_UF

class xUF {
public:
	xUF(size_t n);				// 构造函数
	void Union(int x, int y);	// 合并
	int Find(int x);			// 寻找代表元
	size_t size() const;		// 元素总数
	size_t count() const;		// 不相交集的个数
private:
	std::vector<int> PR;		// 存储父亲结点或存储负秩
	size_t countUF;				// 维护不相交集个数的计数器
};

# endif	// X_UF
