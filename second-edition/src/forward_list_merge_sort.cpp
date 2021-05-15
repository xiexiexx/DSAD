#include <forward_list>
#include <iostream>

// 将有序单链S归并到有序单链F中, 保持F的有序性.
template <typename T>
void merge_forward_list(std::forward_list<T>& F,
  std::forward_list<T>& S)
{
  // 定位归并目标位置的迭代器position.
  auto position = F.before_begin();
  // 单链F的迭代器first(也即position的后一位置), 初始位置为F.begin().
  auto first = F.begin();
  // 注意S中结点只会并入, 所以只需要取链首位置S.begin()即可.
  // 如果F和S都有元素可用于归并则循环继续.
  while (first != F.end() && S.begin() != S.end())
  {
    // 若果F中当前元素较小, 那么F的迭代器前进, 元素不需要变动;
    // 否则将S的链首元素并入目标位置position之后,
    // 注意splice_after用的是S.before_begin().
    if (*first < S.front())
      ++first;
    else
      F.splice_after(position, S, S.before_begin());
    ++position;   // 目标位置迭代器前进.
  }
  // 将S的剩余部分也即(S.before_begin(), S.end())区间中的元素并入,
  // 注意两个迭代器都是开区间的端点. 若S已无元素则F不变.
  F.splice_after(position, S, S.before_begin(), S.end());
}

// 对单链data中的元素进行归并排序.
template <typename T>
void forward_list_merge_sort(std::forward_list<T>& data)
{
  // 包含若干有序单链的单链L.
  std::forward_list<std::forward_list<T>> L;
  size_t n = 0;   // 记录数据个数.
  // 建立若干单链, 每个单链只含一个data中的元素.
  // 注意position在插入之后被赋值为新插入元素所在的位置.
  auto position = L.before_begin();
  for (auto iter = data.begin(); iter != data.end(); ++iter)
  {
    // 注意*iter与{*iter}的区别, 后者是仅包含*iter这个元素的单链.
    position = L.insert_after(position, {*iter});
    ++n;
  }
  // 若链L中至少剩余两个有序单链则持续归并.
  while (n > 1)
  {
    // 以m标记本趟尚剩余的有序单链数.
    size_t m = n;
    auto first_list = L.begin();
    // 一趟归并中每次将两个有序单链归并成一个, 如果还可归并则不断循环.
    while (m > 1)
    {
      auto second_list = first_list;
      ++second_list;
      // 将first_list和second_list所对应的单链归并.
      merge_forward_list(*first_list, *second_list);
      // 假设当前迭代器位置依次为first_list, second_list, next_list.
      // 删除second_list所对应的单链, 并让first_list变为next_list.
      first_list = L.erase_after(first_list);
      // 本趟归并所剩余的有序单链数减少2.
      m -= 2;
      // L中有序单链数减少1.
      --n;
    }
  }
  // 最后只剩下一个有序单链, 则排序成功, 使用移动语义放回data.
  if (n == 1)
    data = std::move(L.front());
}

int main()
{
  std::forward_list<int> L {3, 1, 2, 4, 5};
  forward_list_merge_sort(L);
  for (const auto& x : L)
    std::cout << x << ' ';
  std::cout << std::endl;
  return 0;
}
