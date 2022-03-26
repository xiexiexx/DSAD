export module shuffling;

import <vector>;
import <random>;
import <chrono>;

export
template <typename T>
void shuffling(std::vector<T>& V)
{
  // 随机种子为当前时间(已转换成unsigned int型), 也可用chrono的now函数.
  // 基于均匀分布uniform_int_distribution产生随机数,
  // 下界为0, 上界为默认的numeric_limits<size_t>::max().
  auto ct = std::chrono::system_clock::now();
  auto seed = static_cast<unsigned int>(ct.time_since_epoch().count());
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<size_t> distribution(0);
  // 从V.size() - 1到1, 每次进行随机交换,
  // 未取到0是因为那一次肯定没有交换.
  // 此外对于size_t型做减法并判断边界特别要注意避开负数!
  size_t i = V.size();
  // 注意此处的技巧, 也可直接写成while (i-- > 1)的语句.
  while (i > 1)
  {
    --i;
    // 产生[0, i]内的随机整数.
    size_t j = distribution(generator) % (i + 1);
    // 交换V[i]和V[j].
    std::swap(V[i], V[j]);
  }
}
