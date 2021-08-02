// 包含std::swap.
#include <utility>

#ifndef DOUBLY_LINKED_LIST_CLASS
#define DOUBLY_LINKED_LIST_CLASS

// 为友元和其他使用提前声明所有模板类.
template <typename T>
class list_iterator;
template <typename T>
class list_const_iterator;
template <typename T>
class dnode;
template <typename T>
class doubly_linked_list;

// 迭代器模板类的定义与实现.
template <typename T>
class list_iterator {
public:
  friend class doubly_linked_list<T>;
  friend class list_const_iterator<T>;

  list_iterator()
    : pointer(NULL)
  {
    // 使用list_iterator<T>模板类所需的默认构造函数,
    // 不过在doubly_linked_list<T>::iterator中基本用不上.
  }
  // ==运算符.
  bool operator==(const list_iterator& rhs) const
  {
    return (pointer == rhs.pointer);
  }
  // !=运算符.
  bool operator!=(const list_iterator& rhs) const
  {
    return (pointer != rhs.pointer);
  }
  // *运算符, 注意此处的T&使得有些情况下只能使用常量迭代器.
  T& operator*()
  {
    return pointer->data;
  }
  // 作为前缀使用的++运算符.
  list_iterator& operator++()
  {
    pointer = pointer->next;
    // 注意是返回新值.
    return *this;
  }
  // 作为后缀使用的++运算符, 以(int)区分.
  list_iterator operator++(int)
  {
    list_iterator temp = *this;
    pointer = pointer->next;
    // 注意是返回原值.
    return temp;
  }
  // 作为前缀使用的--运算符.
  list_iterator& operator--()
  {
    pointer = pointer->prev;
    // 注意是返回新值.
    return *this;
  }
  // 作为后缀使用的--运算符, 以(int)区分.
  list_iterator operator--(int)
  {
    list_iterator temp = *this;
    pointer = pointer->prev;
    // 注意是返回原值.
    return temp;
  }

private:
  // 关键数据, 指向双向结点的指针.
  dnode<T>* pointer;
  list_iterator(dnode<T>* p)
    : pointer(p)
  {
    // 私有构造函数, 主要提供给doubly_linked_list<T>使用.
  }
};

// 常量迭代器模板类的定义与实现.
template <typename T>
class list_const_iterator {
public:
  friend class doubly_linked_list<T>;

  list_const_iterator()
    : pointer(NULL)
  {
    // 类似list_iterator<T>模板类的默认构造函数,
  }
  // 从迭代器到常量迭代器的复制构造函数.
  list_const_iterator(const list_iterator<T>& obj)
  {
    pointer = obj.pointer;
  }
  // ==运算符.
  bool operator==(const list_const_iterator& rhs) const
  {
    return (pointer == rhs.pointer);
  }
  // !=运算符.
  bool operator!=(const list_const_iterator& rhs) const
  {
    return (pointer != rhs.pointer);
  }
  // *运算符, 常量版本.
  const T& operator*() const
  {
    return pointer->data;
  }
  // 作为前缀使用的++运算符.
  const list_const_iterator& operator++()
  {
    pointer = pointer->next;
    return *this;
  }
  // 作为后缀使用的++运算符, 以(int)区分.
  const list_const_iterator operator++(int)
  {
    list_const_iterator temp = *this;
    pointer = pointer->next;
    return temp;
  }
  // 作为前缀使用的--运算符.
  const list_const_iterator& operator--()
  {
    pointer = pointer->prev;
    return *this;
  }
  // 作为后缀使用的--运算符, 以(int)区分.
  const list_const_iterator operator--(int)
  {
    list_const_iterator temp = *this;
    pointer = pointer->prev;
    return temp;
  }

private:
  dnode<T>* pointer;
  list_const_iterator(dnode<T>* p)
    : pointer(p)
  {
    // 私有构造函数, 主要提供给doubly_linked_list<T>使用.
  }
};

// 以逆向转换方式给出逆向迭代器和常量逆向迭代器.
template <typename T, typename IR>
class general_reverse {
public:

  // 从迭代器/常量迭代器到逆向迭代器/常量逆向迭代器的复制构造函数.
  general_reverse(const IR& obj)
    : position(obj)
  {
    // 直接使用.
  }
  // ==运算符.
  bool operator==(const general_reverse& rhs) const
  {
    return (position == rhs.position);
  }
  // !=运算符.
  bool operator!=(const general_reverse& rhs) const
  {
    return (position != rhs.position);
  }
  // *运算符.
  T& operator*()
  {
    // 得用position的前一位置来获取逆向迭代器的实际位置.
    IR temp = position;
    return *--temp;
  }
  // *运算符, 常量版本.
  const T& operator*() const
  {
    IR temp = position;
    return *--temp;
  }
  // 作为前缀使用的++运算符.
  const general_reverse& operator++()
  {
    --position;
    return *this;
  }
  // 作为后缀使用的++运算符, 以(int)区分.
  const general_reverse operator++(int)
  {
    general_reverse temp = *this;
    --position;
    return temp;
  }
  // 作为前缀使用的--运算符.
  const general_reverse& operator--()
  {
    ++position;
    return *this;
  }
  // 作为后缀使用的--运算符, 以(int)区分.
  const general_reverse operator--(int)
  {
    general_reverse temp = *this;
    ++position;
    return temp;
  }

private:
  IR position;
};

// 结点模板类的定义与实现.
template <typename T>
class dnode {
  friend class doubly_linked_list<T>;
  friend class list_iterator<T>;
  friend class list_const_iterator<T>;
private:
  T data;
  // 指向前一结点的指针.
  dnode<T>* prev;
  // 指向后一结点的指针.
  dnode<T>* next;
  dnode(const T& value = T())
    : data(value)
  {
    // 默认指向自身.
    prev = next = this;
  }
};

template <typename T>
class doubly_linked_list {
public:
  // doubly_linked_list<T>::iterator实为list_iterator<T>.
  using iterator = list_iterator<T> ;
  // doubly_linked_list<T>::const_iterator实为list_const_iterator<T>.
  using const_iterator = list_const_iterator<T>;
  // 逆向迭代器和常量逆向迭代器是逆向转换而得.
  using reverse_iterator =
    general_reverse<T, list_iterator<T>>;
  using const_reverse_iterator =
    general_reverse<T, list_const_iterator<T>>;
  explicit doubly_linked_list(size_t n = 0, const T& item = T());
  doubly_linked_list(const doubly_linked_list<T>& obj);
  ~doubly_linked_list();
  void swap(doubly_linked_list<T>& rhs);
  doubly_linked_list<T>& operator=(const doubly_linked_list<T>& rhs);
  size_t size() const;
  bool empty() const;
  iterator find(const T& item);
  const_iterator find(const T& item) const;
  void reverse();
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
  const_iterator cbegin() const;
  iterator end();
  const_iterator cend() const;
  reverse_iterator rbegin();
  const_reverse_iterator crbegin() const;
  reverse_iterator rend();
  const_reverse_iterator crend() const;
private:
  // 哑结点指针.
  dnode<T>* header;
  // 双循环链的长度.
  size_t list_size;
};

// 构造函数.
template <typename T>
doubly_linked_list<T>::doubly_linked_list(size_t n, const T& value)
  : list_size(0)
{
  header = new dnode<T>;
  // insert会自行修改list_size, 因此list_size之前构造为0.
  for(size_t i = 0; i < n; ++i)
    insert(end(), value);
}

// 复制构造函数.
template <typename T>
doubly_linked_list<T>::
  doubly_linked_list(const doubly_linked_list<T>& obj)
    : list_size(0)
{
  dnode<T>* curr = obj.header->next;
  header = new dnode<T>;
  // 将obj中元素在待复制构造的双循环链尾部逐个插入,
  while (curr != obj.header)
  {
    insert(end(), curr->data);
    curr = curr->next;
  }
}

// 析构函数.
template <typename T>
doubly_linked_list<T>::~doubly_linked_list()
{
  // 删除所有数据结点并释放内存.
  while (!empty())
    erase(begin());
  // 释放哑结点所占内存.
  delete header;
}

// 数据交换函数.
template <typename T>
void doubly_linked_list<T>::swap(doubly_linked_list<T>& rhs)
{
  std::swap(this->header, rhs.header);
  std::swap(this->list_size, rhs.list_size);
}

// 运算符=的重载实现.
template <typename T>
doubly_linked_list<T>& doubly_linked_list<T>::
  operator=(const doubly_linked_list<T>& rhs)
{
  // 惯用法: copy and swap.
  doubly_linked_list<T> temp(rhs);
  // 交换this和temp的数据部分.
  swap(temp);
  return *this;
}

// 返回元素个数.
template <typename T>
size_t doubly_linked_list<T>::size() const
{
  // 如果需要加入splice操作, 且对任意区间都能保证常数时间,
  // 那么此处必须遍历计数而获得链长, 于是变为线性时间的操作.
  // 当然也可以限定splice操作的性能, 从而取得较好的平衡.
  return list_size;
}

// 判断是否为空.
template <typename T>
bool doubly_linked_list<T>::empty() const
{
  return (list_size == 0);
}

// 查找.
template <typename T>
typename doubly_linked_list<T>::iterator doubly_linked_list<T>::
  find(const T& item)
{
  // 在哑元素处放置哨兵.
  header->data = item;
  dnode<T>* curr = header->next;
  while (curr->data != item)
    curr = curr->next;
  // 返回迭代器位置.
  return iterator(curr);
}

// 查找的常量版本.
template <typename T>
typename doubly_linked_list<T>::const_iterator doubly_linked_list<T>::
  find(const T& item) const
{
  // 在哑元素处放置哨兵.
  header->data = item;
  dnode<T>* curr = header->next;
  while (curr->data != item)
    curr = curr->next;
  // 返回常量迭代器位置.
  return const_iterator(curr);
}

// 链的逆转.
template <typename T>
void doubly_linked_list<T>::reverse()
{
  // curr初值设定.
  dnode<T>* curr = header->next;
  // 依next指针域正向处理所有结点.
  while (curr != header)
  {
    std::swap(curr->prev, curr->next);
    // 注意原先的下一结点位置现已换到curr->prev处.
    curr = curr->prev;
  }
  // 交换哑结点的指针数据.
  std::swap(header->prev, header->next);
}

// 在链首添加新元素.
template <typename T>
void doubly_linked_list<T>::push_front(const T& item)
{
  insert(begin(), item);
}

// 在链尾添加新元素.
template <typename T>
void doubly_linked_list<T>::push_back(const T& item)
{
  insert(end(), item);
}

// 统一和谐的插入函数.
// 在迭代器iter前插入元素item.
template <typename T>
typename doubly_linked_list<T>::iterator doubly_linked_list<T>::
  insert(iterator iter, const T& item)
{
  dnode<T>* curr = iter.pointer;
  // 新申请结点, 指针为p.
  dnode<T>* p = new dnode<T>(item);
  p->prev = curr->prev;
  p->next = curr;
  curr->prev->next = p;
  curr->prev = p;
  ++list_size;
  // 返回新结点所在位置的迭代器.
  return iterator(p);
}

// 删除链首元素.
template <typename T>
void doubly_linked_list<T>::pop_front()
{
  erase(begin());
}

// 删除链尾元素.
template <typename T>
void doubly_linked_list<T>::pop_back()
{
  erase(--end());
}

// 统一和谐的删除函数.
// 删除迭代器iter对应的元素, 注意删除后此迭代器空悬,
// 可用erase函数所返回位置重设iter, 此外注意typename关键字的使用.
template <typename T>
typename doubly_linked_list<T>::iterator doubly_linked_list<T>::
  erase(iterator iter)
{
  dnode<T>* curr = iter.pointer;
  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;
  // 保存curr下一结点迭代器作为返回值.
  iterator p(curr->next);
  delete curr;
  --list_size;
  return p;
}

// 返回链首元素的引用.
template <typename T>
T& doubly_linked_list<T>::front()
{
  return *begin();
}

// 返回链首元素的常量引用.
template <typename T>
const T& doubly_linked_list<T>::front() const
{
  return *begin();
}

// 返回链尾元素的引用.
template <typename T>
T& doubly_linked_list<T>::back()
{
  return *(--end());
}

// 返回链尾元素的常量引用.
template <typename T>
const T& doubly_linked_list<T>::back() const
{
  return *(--end());
}

// 注意下列函数返回的迭代器类型.

// 双循环链的起始位置begin(), 用于迭代器.
template <typename T>
typename doubly_linked_list<T>::iterator
  doubly_linked_list<T>::begin()
{
  return iterator(header->next);
}

// 双循环链的起始位置cbegin(), 用于常量迭代器.
template <typename T>
typename doubly_linked_list<T>::const_iterator
  doubly_linked_list<T>::cbegin() const
{
  return const_iterator(header->next);
}

// 双循环链的终结位置end(), 用于迭代器.
template <typename T>
typename doubly_linked_list<T>::iterator
  doubly_linked_list<T>::end()
{
  return iterator(header);
}

// 双循环链的终结位置cend(), 用于常量迭代器.
template <typename T>
typename doubly_linked_list<T>::const_iterator
  doubly_linked_list<T>::cend() const
{
  return const_iterator(header);
}

// 双循环链的逆向起始位置rbegin(), 用于逆向迭代器.
template <typename T>
typename doubly_linked_list<T>::reverse_iterator
  doubly_linked_list<T>::rbegin()
{
  return reverse_iterator(iterator(header));
}

// 双循环链的逆向起始位置crbegin(), 用于常量逆向迭代器.
template <typename T>
typename doubly_linked_list<T>::const_reverse_iterator
  doubly_linked_list<T>::crbegin() const
{
  return const_reverse_iterator(const_iterator(header));
}

// 双循环链的逆向终结位置rend(), 用于逆向迭代器.
template <typename T>
typename doubly_linked_list<T>::reverse_iterator
  doubly_linked_list<T>::rend()
{
  return reverse_iterator(iterator(header->next));
}

// 双循环链的逆向终结位置crend(), 用于常量逆向迭代器.
template <typename T>
typename doubly_linked_list<T>::const_reverse_iterator
  doubly_linked_list<T>::crend() const
{
  return const_reverse_iterator(const_iterator(header->next));
}

#endif  // DOUBLY_LINKED_LIST_CLASS
