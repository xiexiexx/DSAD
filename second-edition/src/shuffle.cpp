#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// 标准库提供了std::shuffle函数, 也可直接调用.
// 注意还有shuffle_order_engine, 例如knuth_b.

template <typename T>
void shuffle(vector<T>& V)
{
  // 随机种子为当前时间(已转换成size_t型), 基于均匀分布产生随机数,
  // 下界为0, 上界为默认的numeric_limits<size_t>::max().
  std::default_random_engine generator(time(NULL));
  std::uniform_int_distribution<size_t> distribution(0);
  // 从V.size() - 1到1, 每次作随机交换,
  // 不到0是因为那一次肯定无交换.
  // 此外对于size_t型做减法并判断边界特别要注意避开负数!
  size_t i = V.size();
  // 注意此处的技巧, 也可直接写成while (i-- > 1)的语句.
  while (i > 1)
  {
    i--;
    // 产生[0, i]内的随机整数.
    size_t j = distribution(generator) % (i + 1);
    // 交换V[i]和V[j].
    std::swap(V[i], V[j]);
  }
}
