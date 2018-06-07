// 包含std::swap.
#include <utility>

#ifndef xLIST_CLASS
#define xLIST_CLASS

// 为友元和其他使用提前声明所有类.
template <typename T>
class xList_iterator;
template <typename T>
class xList_const_iterator;
template <typename T>
class xDLnode;
template <typename T>
class xList;

// 迭代器类的定义与实现.
template <typename T>
class xList_iterator {
public:
	friend class xList<T>;
	friend class xList_const_iterator<T>;
	xList_iterator()
		: nodePtr(NULL)
	{
		// 使用xList_iterator<T>类所需的默认构造函数,
		// 但使用后面的list<T>::iterator类不需要这个.
	}
	// ==运算符.
	bool operator== (const xList_iterator& rhs) const
	{
		return (nodePtr == rhs.nodePtr);
	}
	// !=运算符.
	bool operator!= (const xList_iterator& rhs) const
	{
		return (nodePtr != rhs.nodePtr);
	}
	// *运算符, 注意此处的T&使得有些情况下只能使用常量迭代器.
	T& operator* ()
	{
		return nodePtr->data;
	}
	// 作为前缀使用的++运算符.
	xList_iterator& operator++ ()
	{
		nodePtr = nodePtr->next;
		return *this;  // 返回新值.
	}
	// 作为后缀使用的++运算符, 用(int)来标志.
	xList_iterator operator++ (int)
	{
		xList_iterator temp = *this;
		nodePtr = nodePtr->next;
		return temp;  // 返回原值.
	}
	// 作为前缀使用的--运算符.
	xList_iterator& operator-- ()
	{
		nodePtr = nodePtr->prev;
		return *this;  // 返回新值.
	}
	// 作为后缀使用的--运算符, 用(int)来标志.
	xList_iterator operator-- (int)
	{
		xList_iterator temp = *this;
		nodePtr = nodePtr->prev;
		return temp;  // 返回原值.
	}

private:
	// 关键数据, 指向双向结点的指针.
	xDLnode<T>* nodePtr;
	xList_iterator(xDLnode<T>* p)
		: nodePtr(p)
	{
		// 私有构造函数, 给xList<T>用.
	}
};

// 常量迭代器类的定义与实现.
template <typename T>
class xList_const_iterator {
public:
	friend class xList<T>;
	xList_const_iterator()
		: nodePtr(NULL)
	{
		// 使用xList_const_iterator<T>类所需的默认构造函数,
		// 但使用后面的list<T>::const_iterator类不需要这个.
	}

	// 从迭代器类到常量迭代器的复制构造函数.
	xList_const_iterator(const xList_iterator<T>& obj)
	{
		nodePtr = obj.nodePtr;
	}
	bool operator== (const xList_const_iterator& rhs) const
	{
		return (nodePtr == rhs.nodePtr);
	}

	bool operator!= (const xList_const_iterator& rhs) const
	{
		return (nodePtr != rhs.nodePtr);
	}
	const T& operator* () const
	{
		return nodePtr->data;
	}
	// 作为前缀使用的++运算符.
	const xList_const_iterator& operator++ ()
	{
		nodePtr = nodePtr->next;
		return *this;  // 返回新值.
	}
	// 作为后缀使用的++运算符, 用(int)来标志.
	const xList_const_iterator operator++ (int)
	{
		xList_const_iterator temp = *this;
		nodePtr = nodePtr->next;
		return temp;  // 返回原值.
	}
	// 作为前缀使用的--运算符.
	const xList_const_iterator& operator-- ()
	{
		nodePtr = nodePtr->prev;
		return *this;  // 返回新值.
	}
	// 作为后缀使用的--运算符, 用(int)来标志.
	const xList_const_iterator operator-- (int)
	{
		xList_const_iterator temp = *this;
		nodePtr = nodePtr->prev;
		return temp;  // 返回原值.
	}

private:
	xDLnode<T>* nodePtr;
	xList_const_iterator(xDLnode<T>* p)
		: nodePtr(p)
	{
		// 私有构造函数, 给xList<T>用.
	}
};

// xDLnode类的定义与实现.
template <typename T>
class xDLnode {
	friend class xList<T>;
	friend class xList_iterator<T>;
	friend class xList_const_iterator<T>;
private:
	T data;
	xDLnode<T>* prev;	// 指向前一个结点的指针.
	xDLnode<T>* next;	// 指向后一个结点的指针.
	xDLnode(const T& value = T())
		: data(value)
	{
		// 默认指向自身.
		prev = next = this;
	}
};

template <typename T>
class xList {
public:
	// 将迭代器xList_iterator<T>作为嵌套类型,
	// 使用xList<T>::iterator实为xList_iterator<T>.
	typedef xList_iterator<T> iterator;
	// 将常量迭代器xList_const_iterator<T>作为嵌套类型,
	// 使用xList<T>::const_iterator实为xList_const_iterator<T>.
	typedef xList_const_iterator<T> const_iterator;
	explicit xList(size_t n = 0, const T& item = T());
	xList(const xList<T>& obj);
	~xList();
	void swap(xList<T>& rhs);
	xList<T>& operator= (const xList<T>& rhs);
	size_t size() const;
	bool empty() const;
	void push_front(const T& item);
	void push_back(const T& item);
	iterator insert(iterator iter, const T& item);
	void pop_front();
	void pop_back();
	iterator erase(iterator iter);
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
private:
	xDLnode<T>* header;		// 哑结点指针.
	size_t lSize;			// 双循环链的长度.
};

// 构造函数.
template <typename T>
xList<T>::xList(size_t n, const T& value)
	: lSize(0)
{
	header = new xDLnode<T>;
	// insert会修改lSize, 因此lSize之前构造为0.
	for(size_t i = 0; i < n; i++)
		insert(begin(), value);
}

// 复制构造函数.
template <typename T>
xList<T>::xList(const xList<T>& obj)
	: lSize(0)
{
	xDLnode<T>* curr = obj.header->next;
	header = new xDLnode<T>;
	// 将obj中元素在需复制构造的双循环链尾部逐个插入, 注意insert会修改lSize.
	while (curr != obj.header)
	{
		insert(end(), curr->data);
		curr = curr->next;
	}
}

// 析构函数.
template <typename T>
xList<T>::~xList()
{
	// 删除所有数据结点并释放内存.
	while (!empty())
		erase(begin());
	// 释放哑结点所占内存.
	delete header;
}

// 数据交换函数.
template <typename T>
void xList<T>::swap(xList<T>& rhs)
{
	std::swap(this->header, rhs.header);
	std::swap(this->lSize, rhs.lSize);
}

// 运算符=的重载实现.
template <typename T>
xList<T>& xList<T>::operator=(const xList<T>& rhs)
{
	// 惯用法: copy and swap.
	xList<T> temp(rhs);
	// 交换this和temp的数据部分.
	swap(temp);
	return *this;
}

// 返回元素个数.
template <typename T>
size_t xList<T>::size() const
{
	return lSize;
}

// 判断是否为空.
template <typename T>
bool xList<T>::empty() const
{
	return (lSize == 0);
}

// 在链首添加新元素.
template <typename T>
void xList<T>::push_front(const T& item)
{
	insert(begin(), item);
}

// 在链尾添加新元素.
template <typename T>
void xList<T>::push_back(const T& item)
{
	insert(end(), item);
}

// 统一和谐的插入元素函数.
// 在迭代器iter前插入元素item.
template <typename T>
typename xList<T>::iterator xList<T>::insert(iterator iter, const T& item)
{
	xDLnode<T>* curr = iter.nodePtr;
	// 新申请结点, 指针为p.
	xDLnode<T>* p = new xDLnode<T>(item);
	p->prev = curr->prev;
	p->next = curr;
	curr->prev->next = p;
	curr->prev = p;
	lSize++;
	return iterator(p);		// 返回新结点所在位置的迭代器.
}

// 删除链首元素.
template <typename T>
void xList<T>::pop_front()
{
	erase(begin());
}

// 删除链尾元素.
template <typename T>
void xList<T>::pop_back()
{
	erase(--end());
}

// 统一和谐的删除元素函数.
// 删除迭代器iter指向的元素, 注意删除后此迭代器空悬, 
// 可用erase函数所返回的位置重新初始化iter, 此外注意typename关键字的使用.
template <typename T>
typename xList<T>::iterator xList<T>::erase(iterator iter)
{
	xDLnode<T>* curr = iter.nodePtr;
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	iterator iter_next(curr->next);	// 保存curr的下一结点迭代器作为返回值.
	delete curr;
	lSize--;
	return iter_next;
}

// 返回链首元素的引用.
template <typename T>
T& xList<T>::front()
{
	return *begin();
}

// 返回链首元素的常量引用.
template <typename T>
const T& xList<T>::front() const
{
	return *begin();
}

// 返回链尾元素的引用.
template <typename T>
T& xList<T>::back()
{
	return *(--end());
}

// 返回链尾元素的常量引用.
template <typename T>
const T& xList<T>::back() const
{
	return *(--end());
}

// 注意下列函数返回的迭代器类型.

// 双循环链的初始位置begin(), 用于迭代器.
template <typename T>
typename xList<T>::iterator xList<T>::begin()
{
	return iterator(header->next);
}

// 双循环链的初始位置begin(), 用于常量迭代器.
template <typename T>
typename xList<T>::const_iterator xList<T>::begin() const
{
	return const_iterator(header->next);
}

// 双循环链的终结位置end(), 用于迭代器.
template <typename T>
typename xList<T>::iterator xList<T>::end()
{
	return iterator(header);
}

// 双循环链的终结位置end(), 用于常量迭代器.
template <typename T>
typename xList<T>::const_iterator xList<T>::end() const
{
	return const_iterator(header);
}

#endif   // xLIST_CLASS