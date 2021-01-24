#include <vector>
#include <iostream>
#include "timer.h"

// 记V.size()为n, 固定V[0]到V[k - 1], 生成V[k]到V[n - 1]的所有排列,
// 并对每种排列情况打印V[0]到V[n - 1].
template <typename T>
void permute(std::vector<T>& V, size_t k = 0)
{
  if (k == V.size())	// 到终止条件, 则打印该排列.
  {
    // 读者可以改写为基于范围的for循环.
    for(size_t i = 0; i < V.size(); ++i)
      std::cout << V[i] << ' ';
    std::cout << std::endl;
  }
  else // 未到终止条件, 用轮换首元素的方式继续递归.
    for(size_t i = k; i < V.size(); ++i)
    {
      // 先将首元素V[k]与后面的元素交换.
      std::swap(V[k], V[i]);
      // 用递归产生此情况下的排列.
      permute(V, k + 1);
      // 再将首元素换回来以进行下次交换.
      std::swap(V[i], V[k]);
    }
}

// 生成{1, 2, 3, 4, 5}的所有排列并在屏幕上输出.
int main()
{
  std::vector<int> A {1, 2, 3, 4, 5};
  timer t;
  t.start();
  // 默认从向量首元素A[0]开始.
  permute(A);
  std::cout << std::endl;
  t.stop();
  std::cout << "Elapsed time is " << t.time()
            << " seconds" << std::endl;
  return 0;
}
