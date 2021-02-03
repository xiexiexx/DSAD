#include <forward_list>
#include <iostream>

// 将有序单链S归并到有序单链F中, 保持F的有序性.
template <typename T>
void merge_forward_list(std::forward_list<T>& F,
  std::forward_list<T>& S)
{
  // 定位归并目标位置的迭代器.
  auto position = F.before_begin();
  // 单链F的迭代器first_iter, 初始位置为F.begin().
  auto first_iter = F.begin();
  // 单链S的迭代器second_iter, 初始位置为S.begin().
  auto second_iter = S.begin();
  // second_iter之前的迭代器位置before_second_iter.
  auto before_second_iter = S.before_begin();
  // F和S都有元素可用于归并则循环继续.
  while (first_iter != F.end() && second_iter != S.end())
  {
    if (*first_iter < *second_iter)
      ++first_iter;   // F的迭代器前进, 元素不需要变动.
    else
    {
      // 将S中元素*second_iter并入目标位置,
      // 注意使用的迭代器位置是before_second_iter.
      F.splice_after(position, S, before_second_iter);
      second_iter = before_second_iter;
      ++second_iter;
    }
    ++position;       // 目标位置迭代器前进.
  }
  // 将S中剩余部分(before_second_iter, S.end())范围元素并入,
  // 若无元素则F无变化, 注意两端都是开区间的端点.
  F.splice_after(position, S, before_second_iter, S.end());
}

// 对单链data中元素进行归并排序.
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
    position = L.insert_after(position, {*iter});
    ++n;
  }
  // 若链中至少剩余两个元素则持续归并.
  while (n > 1)
  {
    // 若L中不止一个有序单链, 则进行一趟归并.
    size_t m = n;
    auto first_list = L.begin();
    // 一趟归并中每次将两个有序单链归并成一个, 如果还可归并则不断进行.
    while (m > 1)
    {
      auto second_list = first_list;
      ++second_list;
      // 将first_list和second_list指示的单链归并.
      merge_forward_list(*first_list, *second_list);
      // 设当前迭代器位置依次为first_list, second_list, next.
      // 删除second_list所指示的单链, 并让first_list变为next.
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
    std::cout << x << std::endl;
  return 0;
}
