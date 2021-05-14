#include <list>
#include <iostream>

using std::list;
using std::cin;
using std::cout;
using std::endl;

void input_preprocess(list<int>& L, int& m)
{
  L.clear();      // 清空L中所有数据.
  int data;
  cin >> data;
  m = data;       // 注意空序列时m为负整数.
  while (data >= 0)
  {
    // 使用push_back可以保留数据的输入次序.
    L.push_back(data);
    // 同时统计最大值.
    if (data > m)
      m = data;
    cin >> data;  // 读入数据.
  }
}

void print(const list<int>& L)
{
  // 由于此次遍历不改变链的状态, 所以使用常量迭代器citer.
  // 常量迭代器可保证对L的常量引用, 特别以cbegin和cend区别于begin和end.
  // 也可使用基于范围的for循环完成.
  for (auto citer = L.cbegin(); citer != L.cend(); ++citer)
    cout << *citer << ' ';
}

void mean_of_larger(list<int>& L, int d, int m)
{
  // 注意空序列时不能调用本函数, 其他情况下的自然数序列均有正确返回值.
  // 计算阈值, 由于m最大, 只需大于等于阈值即可.
  int threshold = m - d;
  // 满足要求的数之总和, 以double型存储便于后续计算.
  double sum = 0;
  // 满足要求的自然数个数, 实际上等于最终的L.size()值.
  size_t n = 0;
  // 使用auto定义迭代器iter, 注意可能利用它删除元素,
  // 而删除会改变容器状态, 所以iter是list<int>::iterator型迭代器.
  auto iter = L.begin();
  while (iter != L.end())
  {
    if (*iter >= threshold)
    {
      sum += *iter;
      ++n;
      ++iter;               // 注意后续删除分支不能这样操作.
    }
    else
      iter = L.erase(iter); // 删除后iter会被赋值到后一元素位置.
  }
  cout << "The mean of the larger numbers is " << sum / n
       << endl << "Larger numbers: ";
  // 要求最后打印所保留的那些自然数, 所以需要再次遍历.
  print(L);
}
