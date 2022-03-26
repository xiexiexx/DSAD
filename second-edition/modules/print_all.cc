export module print_all;

import <iostream>;

// 打印容器S中的所有元素.
export
template <typename C>
void print_all(const C& S)
{
  for (const auto& x : S)
    std::cout << x << ' ';
  std::cout << std::endl;
}

// 以迭代器区间[left, right)作为参数打印该区间对应的所有元素.
export
template <typename IR>
void print_all(IR left, IR right)
{
  while (left != right)
    std::cout << *left++ << ' ';
  std::cout << std::endl;
}